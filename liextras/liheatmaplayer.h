#ifndef LIHEATMAPLAYER_H
#define LIHEATMAPLAYER_H

#include "liextrasglobal.h"
#include "liheatmap.h"
#include <qgsvectorlayer.h>

class LiVectorLayer;

class LIEXTRAS_EXPORT LiHeatmapLayer : public LiHeatmap
{
    Q_OBJECT
public:
    explicit LiHeatmapLayer(LiNode *parent = nullptr);

    void load(QgsVectorLayer *vectorLayer);

private:
    void processFeature(const QgsFeature &feature);
    void completed();

private:
    LiVectorLayer *m_vectorLayer;
    Cartographic m_center;
    LiRectangle m_rectangle;
    int m_valueAttrIndex;
    double m_maxValue;
    QVector<Vector4> m_data;
};

#endif // LIHEATMAPLAYER_H
