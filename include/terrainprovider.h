#ifndef TERRAINPROVIDER_H
#define TERRAINPROVIDER_H

#include "licore_global.h"
#include "rectangle.h"

class QuadtreeTile;
class TilingScheme;
class TileTerrain;
class TerrainLayer;
class TerrainData;
class Ellipsoid;
class TileAvailability;
class TerrainProviderPrivate;

class LICORE_EXPORT TerrainProvider : public QObject
{
    Q_OBJECT
public:
    explicit TerrainProvider(QObject *parent = 0);
    virtual ~TerrainProvider();

    virtual bool ready() const = 0;
    virtual int tileWidth() const = 0;
    virtual int tileHeight() const = 0;
    virtual TilingScheme *tilingScheme() const = 0;
    virtual void requestTileGeometry(QuadtreeTile *tile, TileTerrain *tileTerrain) = 0;
    virtual bool getTileDataAvailable(int x, int y, int level) = 0;
    virtual double getLevelMaximumGeometricError(int level) = 0;
    virtual TileAvailability *availability() const { return nullptr; }
    virtual bool requestVertexNormals() const { return false; }
    virtual bool requestWaterMask() const { return false; }
    virtual bool hasWaterMask() const { return false; }
    virtual void addTerrainLayer(TerrainLayer *layer) = 0;
    virtual LiRectangle bounds() const { return LiRectangle(); }

    static double getEstimatedLevelZeroGeometricErrorForAHeightmap(Ellipsoid *ellipsoid,
                                                                   int tileImageWidth,
                                                                   int numberOfTilesAtLevelZero);

protected:
    TerrainProvider(TerrainProviderPrivate &dd, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(TerrainProvider)
};

#endif // TERRAINPROVIDER_H
