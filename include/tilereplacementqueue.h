#ifndef TILEREPLACEMENTQUEUE_H
#define TILEREPLACEMENTQUEUE_H

#include "licore_global.h"

class QuadtreeTile;
class QuadtreePrimitive;

class LICORE_EXPORT TileReplacementQueue
{
public:
    TileReplacementQueue(QuadtreePrimitive *primitive);

    QuadtreeTile *head() const { return _head; }
    QuadtreeTile *tail() const { return _tail; }
    int count() const { return _count; }
    bool contains(QuadtreeTile *item) const;

    void clear();
    void markStartOfRenderFrame();
    void trimTiles(int maximumTiles);
    void remove(QuadtreeTile *item);
    void markTileRendered(QuadtreeTile *item);

private:
    int _count;
    QuadtreeTile *_head;
    QuadtreeTile *_tail;
    QuadtreeTile *_lastBeforeStartOfFrame;
    QuadtreePrimitive *_primitive;
};

#endif // TILEREPLACEMENTQUEUE_H
