#include "litreelayer.h"
#include "livectorlayer.h"
#include "transforms.h"
#include "transformhelper.h"
#include <litransform.h>
#include <lientity.h>

LiTreeLayer::LiTreeLayer(LiNode *parent)
    : LiForest(parent)
    , m_vectorLayer(nullptr)
{
}

void LiTreeLayer::load(QgsVectorLayer *vectorLayer)
{
    if (vectorLayer)
    {
        m_vectorLayer = new LiVectorLayer(vectorLayer, this);
        m_rectangle = TransformHelper::instance()->toWgs84(vectorLayer->extent(), &vectorLayer->crs());
        m_center = m_rectangle.center();

        QgsFields fields = vectorLayer->fields();
        m_nameIndex = fields.indexFromName("name");
        m_xIndex = fields.indexFromName("X");
        m_yIndex = fields.indexFromName("Y");
        m_rotationIndex = fields.indexFromName("rotation");
        m_scaleIndex = fields.indexFromName("scale");

        connect(m_vectorLayer, &LiVectorLayer::featureLoaded, this, &LiTreeLayer::processFeature, Qt::DirectConnection);
        connect(m_vectorLayer, &LiVectorLayer::completed, this, &LiTreeLayer::completed);

        QStringList attrs;
        attrs << "name" << "X" << "Y";
        if (!m_autoRotationAndScale)
            attrs << "rotation" << "scale";

        m_vectorLayer->setAttributeList(attrs);
        m_vectorLayer->startStreaming();
    }
}

void LiTreeLayer::processFeature(const QgsFeature &feature)
{
    int attrCount = m_autoRotationAndScale ? 3 : 5;
    const auto attrs = feature.attributes();
    if (attrs.size() >= attrCount)
    {
        QString name = attrs[m_nameIndex].toString();
        if (!name.endsWith(QLatin1String(".srt")))
        {
            name += QLatin1String(".srt");
        }

        double x = attrs[m_xIndex].toDouble();
        double y = attrs[m_yIndex].toDouble();
        double rotation;
        double scale;

        if (m_autoRotationAndScale)
        {
            rotation = qrand() / double(RAND_MAX) * Math::TWO_PI;
            scale = 1 + qrand() / double(RAND_MAX) * 0.2 - 0.1;
        }
        else
        {
            rotation = attrs[m_rotationIndex].toDouble() * Math::RADIANS_PER_DEGREE;
            scale = attrs[m_scaleIndex].toDouble();
        }

        Cartographic cart = TransformHelper::instance()->toWgs84(x, y, &m_vectorLayer->crs());

        if (m_instances.contains(name))
        {
            TreeInstances &insts = m_instances[name];
            insts.append({cart, rotation, scale});
        }
        else
        {
            TreeInstances insts;
            insts.append({cart, rotation, scale});
            m_instances.insert(name, insts);
        }
    }
}

void LiTreeLayer::completed()
{
    if (!m_instances.isEmpty())
    {
        if (transform())
        {
            transform()->setCartographic(m_center);
        }

        auto it = m_instances.cbegin();
        for (; it != m_instances.cend(); ++it)
        {
            const TreeInstances insts = it.value();
            const int count = insts.size();

            QVector<Cartographic> pos(count);
            QVector<double> rotation(count);
            QVector<double> scale(count);

            for (int i = 0; i < count; ++i)
            {
                pos[i] = insts[i].cart;
                rotation[i] = insts[i].rotation;
                scale[i] = insts[i].scale * LiForest::scale();
            }

            add(it.key(), count, pos.constData(), rotation.constData(), scale.constData());
        }
    }
}
