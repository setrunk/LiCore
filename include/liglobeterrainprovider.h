#ifndef LIGLOBETERRAINPROVIDER_H
#define LIGLOBETERRAINPROVIDER_H

#include "terrainprovider.h"
#include "rectangle.h"

class LiGlobeTerrainProviderPrivate;

class LICORE_EXPORT LiGlobeTerrainProvider : public TerrainProvider
{
    Q_OBJECT
public:
    explicit LiGlobeTerrainProvider(QObject *parent = nullptr);
    explicit LiGlobeTerrainProvider(QString url, QObject *parent = nullptr);
    ~LiGlobeTerrainProvider();

    QFuture<void> readyPromise() const;
    bool ready() const;
    int tileWidth() const;
    int tileHeight() const;
    TilingScheme *tilingScheme() const;
    void requestTileGeometry(QuadtreeTile *tile, TileTerrain *tileTerrain);
    bool getTileDataAvailable(int x, int y, int level);
    double getLevelMaximumGeometricError(int level);
    TileAvailability *availability() const;
    bool hasWaterMask() const;
    void addTerrainLayer(TerrainLayer *layer);

    bool requestVertexNormals() const;
    void setRequestVertexNormals(bool value);

    bool requestWaterMask() const;
    void setRequestWaterMask(bool value);

    LiRectangle bounds() const;

private:
    QVariantMap getRequestHeader(const QStringList &extensionsList);
    Q_DECLARE_PRIVATE(LiGlobeTerrainProvider)
};

#endif // LIGLOBETERRAINPROVIDER_H
