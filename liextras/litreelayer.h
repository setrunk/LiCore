#ifndef LITREELAYER_H
#define LITREELAYER_H

#include "liextrasglobal.h"
#include "libehavior.h"
#include <liforest.h>
#include <vector3.h>
#include <cartographic.h>
#include <qgsvectorlayer.h>

class LiVectorLayer;

class LIEXTRAS_EXPORT LiTreeLayer : public LiForest
{
    Q_OBJECT
public:
    explicit LiTreeLayer(LiNode *parent = nullptr);

    Cartographic center() const { return m_center; }
    LiRectangle rectangle() const { return m_rectangle; }

    bool autoRotationAndScale() const { return m_autoRotationAndScale; }
    void setAutoRotationAndScale(bool value) { m_autoRotationAndScale = value; }

    void load(QgsVectorLayer *vectorLayer);

private:
    void processFeature(const QgsFeature &feature);
    void completed();

    struct Tree
    {
//        Vector3 position;
        Cartographic cart;
        double rotation;
        double scale;
    };
    typedef QVector<Tree> TreeInstances;

    LiVectorLayer *m_vectorLayer;
    LiRectangle m_rectangle;
    Cartographic m_center;
    bool m_autoRotationAndScale = false;
    QHash<QString, TreeInstances> m_instances;

    int m_nameIndex;
    int m_xIndex;
    int m_yIndex;
    int m_zIndex;
    int m_rotationIndex;
    int m_scaleIndex;
};

#endif // LITREELAYER_H
