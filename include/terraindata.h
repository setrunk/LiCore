#ifndef TERRAINDATA_H
#define TERRAINDATA_H

#include "licore_global.h"
#include "terrainmesh.h"
#include "rectangle.h"
#include "future.h"

class TileTerrain;
class TilingScheme;

class LICORE_EXPORT TerrainData
{
public:
    TerrainData();
    virtual ~TerrainData();

    virtual QSharedPointer<TerrainMesh> terrainMesh() const = 0;
    virtual Future createMesh(TilingScheme *tilingScheme, int x, int y, int level, double exaggeration = 1.0) = 0;

    virtual QByteArray waterMask() const { return QByteArray(); }

    virtual bool wasCreatedByUpsampling() const = 0;
    virtual bool isChildAvailable(int thisX, int thisY, int childX, int childY) const = 0;

    virtual double interpolateHeight(const LiRectangle &rectangle, double longitude, double latitude) const = 0;
    virtual QFuture<TerrainData*> upsample(TilingScheme *tilingScheme,
                                           int sourceX, int sourceY, int sourceLevel,
                                           int descendantX, int descendantY, int descendantLevel) = 0;

};

typedef QSharedPointer<TerrainData> TerrainDataPtr;

#endif // TERRAINDATA_H
