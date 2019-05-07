#include "livectorlayer.h"
#include "asyncfuture.h"
#include "transformhelper.h"

LiVectorLayer::LiVectorLayer(QgsVectorLayer *layer, QObject *parent)
    : QObject(parent)
    , _vectorLayer(layer)
    , _state(UNLOADED)
{
    if (layer)
    {
        _extent = layer->extent();
        qDebug() << layer->crs().authid();
        _rectangle = TransformHelper::instance()->transform(_extent, &layer->crs());
    }
}

LiVectorLayer::~LiVectorLayer()
{
    stopStreaming();
}

bool LiVectorLayer::startStreaming()
{
    if (!_vectorLayer)
    {
        qDebug() << Q_FUNC_INFO << "no vector layer.";
        return false;
    }

    _state = LOADING;
    _streaming.fetchAndStoreOrdered(1);
    _running.fetchAndStoreOrdered(1);

    auto p = QtConcurrent::run([=]() {

        QgsFeatureRequest request;

        const QStringList attrs = attributeList();
        if (attrs.size())
        {
            QgsFields fields = _vectorLayer->fields();
            QgsAttributeList attrList;
            for (const QString &name : attrs)
            {
                int attr = fields.indexFromName(name);
                if (attr < 0)
                {
                    qDebug() << Q_FUNC_INFO << "not found attribute" << name;
                }
                else
                {
                    attrList << attr;
                }
            }

            request.setSubsetOfAttributes(attrList);
        }

        QgsFeature feat;
        QgsFeatureIterator featIt = _vectorLayer->getFeatures(request);

        while (_streaming.load() && featIt.nextFeature(feat))
        {
            emit featureLoaded(feat);
        }

        _streaming.fetchAndStoreOrdered(0);
        _running.fetchAndStoreOrdered(0);
    });

    observe(p).subscribe([this] {
        emit completed();
        _state = LOADED;
    });

    return true;
}

void LiVectorLayer::stopStreaming()
{
    if (_running.load())
    {
        _streaming.fetchAndStoreOrdered(0);

        while (_running.load())
        {
            QThread::usleep(1);
        }
    }
}
