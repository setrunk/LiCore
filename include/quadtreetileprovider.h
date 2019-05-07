#ifndef QUADTREETILEPROVIDER_H
#define QUADTREETILEPROVIDER_H

#include "licore_global.h"

class QuadtreePrimitive;
class QuadtreeTile;
class TilingScheme;
class FrameState;

class LICORE_EXPORT QuadtreeTileProvider : public QObject
{
    Q_OBJECT
public:
    virtual ~QuadtreeTileProvider() {}

    virtual bool ready() const = 0;

    virtual QuadtreePrimitive *quadtree() const = 0;
    virtual TilingScheme *tilingScheme() const = 0;

    virtual void beginUpdate(FrameState *frameState) = 0;
    virtual void endUpdate(FrameState *frameState) = 0;
    virtual void showTileThisFrame(FrameState *frameState) = 0;

    virtual bool loadTile(FrameState *frameState, QuadtreeTile *tile) = 0;

    double computeDefaultLevelZeroMaximumGeometricError(TilingScheme *tilingScheme);
    virtual void computeTileVisibility(QuadtreeTile *tile, FrameState *frameState) = 0;
    virtual double computeDistanceToTile(QuadtreeTile *tile, FrameState *frameState) = 0;
    virtual double getLevelMaximumGeometricError(int level) const = 0;
};

#endif // QUADTREETILEPROVIDER_H
