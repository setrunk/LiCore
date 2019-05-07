#ifndef TERRAINLAYER_H
#define TERRAINLAYER_H

#include "licore_global.h"
#include "rectangle.h"
#include "future.h"

class HeightmapTerrainData;

class LICORE_EXPORT TerrainLayer : public QObject
{
    Q_OBJECT
public:
    explicit TerrainLayer(QObject *parent = 0);
    virtual ~TerrainLayer() {}

    virtual Future requestTileGeometry(int x, int y, int level,
                                       const LiRectangle &destRectangle,
                                       HeightmapTerrainData *terrainData) = 0;

};

#endif // TERRAINLAYER_H
