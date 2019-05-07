#ifndef TERRAINSURFACELAYER_H
#define TERRAINSURFACELAYER_H

#include "licore_global.h"
#include "cartographic.h"
#include "rectangle.h"
#include "ray.h"
#include "future.h"

class LiEntity;
class LiGeometryRenderer;
class TerrainSurfaceLayerPrivate;

class LICORE_EXPORT TerrainSurfaceLayer : public QObject
{
    Q_OBJECT
public:
    explicit TerrainSurfaceLayer(QObject *parent = nullptr);
    ~TerrainSurfaceLayer();

    void addEntity(LiEntity *entity);
    void removeEntity(LiEntity *entity);

    LiRectangle rectangle() const;
    double getHeight(const Cartographic &cartographic) const;

signals:
    void surfaceChanged(const LiRectangle &rectangle);

private:
    QSharedPointer<TerrainSurfaceLayerPrivate> d_ptr;
};

TerrainSurfaceLayer *globalTerrainSurface();

#endif // TERRAINSURFACELAYER_H
