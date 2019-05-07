#ifndef QUADTREEPRIMITIVE_H
#define QUADTREEPRIMITIVE_H

#include <QtCore>
#include "cartographic.h"
#include "rectangle.h"
#include "tilereplacementqueue.h"

class FrameState;
class QuadtreeTile;
class GlobeSurfaceTileProvider;
class TilingScheme;
class QuadtreeOccluders;
class ClampedObject;

typedef QVector<QuadtreeTile *> QuadtreeTileList;

class LICORE_EXPORT QuadtreePrimitive : public QObject
{
    Q_OBJECT
public:
    explicit QuadtreePrimitive(GlobeSurfaceTileProvider *tileProvider, QObject *parent = 0);
    virtual ~QuadtreePrimitive();

    GlobeSurfaceTileProvider *tileProvider() const { return _tileProvider; }

    QuadtreeTileList levelZeroTiles() const { return _levelZeroTiles; }
    void invalidateAllTiles();
    void createLevelZeroTiles();

    QuadtreeTileList tilesLoaded() const;
    QuadtreeTileList tilesToRender() const;

    void beginFrame(FrameState *frameState);
    void update(FrameState *frameState);
    void endFrame(FrameState *frameState);

    void destroy();

    struct Debug
    {
        bool enableDebugOutput;
        bool suspendLodUpdate;

        int maxDepth;
        int tilesVisited;
        int tilesCulled;
        int tilesRendered;
        int tilesWaitingForChildren;

        int lastMaxDepth;
        int lastTilesVisited;
        int lastTilesCulled;
        int lastTilesRendered;
        int lastTilesWaitingForChildren;
    };
    Debug _debug;

signals:
    void tileRendered(QuadtreeTile *tile);
    void tileLoaded(QuadtreeTile *tile);
    void tileDeleted(QuadtreeTile *tile);

private:
    static bool compareDistanceToPoint(QuadtreeTile *a, QuadtreeTile *b);
    void selectTilesForRendering(FrameState *frameState);
    void createRenderCommandsForSelectedTiles(FrameState *frameState);
    void visitTile(FrameState *frameState, QuadtreeTile *tile);
    void queueChildLoadNearToFar(const Cartographic &cameraPosition,
                                 QuadtreeTile *southwest,
                                 QuadtreeTile *southeast,
                                 QuadtreeTile *northwest,
                                 QuadtreeTile *northeast);
    void queueChildTileLoad(QuadtreeTile *tile);
    void visitVisibleChildrenNearToFar(QuadtreeTile *southwest,
                                       QuadtreeTile *southeast,
                                       QuadtreeTile *northwest,
                                       QuadtreeTile *northeast,
                                       FrameState *frameState);
    void visitIfVisible(QuadtreeTile *tile, FrameState *frameState);
    double screenSpaceError(FrameState *frameState, QuadtreeTile *tile);
    void addTileToRenderList(QuadtreeTile *tile);
    void processTileLoadQueue(FrameState *frameState);
    void processSinglePriorityLoadQueue(FrameState *frameState, quint64 endTime, const QuadtreeTileList &loadQueue);

    void updateHeights();

    GlobeSurfaceTileProvider *_tileProvider;
    QuadtreeTileList _tilesToRender;
    QuadtreeTileList _tilesToUpdateHeight;
    QuadtreeTileList _tileLoadQueueHigh;
    QuadtreeTileList _tileLoadQueueMedium;
    QuadtreeTileList _tileLoadQueueLow;
    QuadtreeTileList _levelZeroTiles;
    TileReplacementQueue _tileReplacementQueue;
    QuadtreeOccluders *_occluders;
    QVector<ClampedObject*> _clampedObjects;
    int _tileCacheSize;
    bool _levelZeroTilesReady;
    quint64 _loadQueueTimeSlice;
    quint64 _updateHeightsTimeSlice;
    double _maximumScreenSpaceError;
    int _lastTileIndex;
    int _lastTileLoadQueueLength;
};

#endif // QUADTREEPRIMITIVE_H
