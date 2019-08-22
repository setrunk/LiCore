#include "liheatmaplayer.h"
#include "transformhelper.h"
#include "livectorlayer.h"
#include <qgsgeometry.h>
#include <qgspointxy.h>

LiHeatmapLayer::LiHeatmapLayer(LiNode *parent)
    : LiHeatmap(parent)
    , m_maxValue(0)
{
}

void LiHeatmapLayer::load(QgsVectorLayer *vectorLayer)
{
    if (!vectorLayer)
        return;

    m_vectorLayer = new LiVectorLayer(vectorLayer, this);
    m_rectangle = m_vectorLayer->rectangle();
    m_center = m_rectangle.center();

    QgsFields fields = vectorLayer->fields();
    m_valueAttrIndex = fields.indexFromName("h");

    connect(m_vectorLayer, &LiVectorLayer::featureLoaded, this, &LiHeatmapLayer::processFeature, Qt::DirectConnection);
    connect(m_vectorLayer, &LiVectorLayer::completed, this, &LiHeatmapLayer::completed);

    m_vectorLayer->setAttributeList(QStringList() << "h");
    m_vectorLayer->startStreaming();
}

void LiHeatmapLayer::processFeature(const QgsFeature &feature)
{
    QgsPointXY *point = (QgsPointXY*)feature.geometry().get();
    double x = point->x();
    double y = point->y();
    Cartographic cart = TransformHelper::instance()->toWgs84(x, y, m_vectorLayer->crs());

    const auto attrs = feature.attributes();
    double value = attrs[m_valueAttrIndex].toDouble();
    m_maxValue = std::max(value, m_maxValue);

    m_data.append(Vector4(cart.longitude, cart.latitude, cart.height, value));
}

void LiHeatmapLayer::completed()
{
    if (m_data.size())
    {
        setMaxValue(m_maxValue);
        setRadius(50);
        setCellSize(51);
        setRectangle(m_rectangle);
        setColor(Qt::red);
        setData(m_data);
    }
}
