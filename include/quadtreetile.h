#ifndef QUADTREETILE_H
#define QUADTREETILE_H

#include "licore_global.h"
#include "rectangle.h"

class TilingScheme;
class GlobeSurfaceTile;
class QuadtreePrimitive;

class LICORE_EXPORT QuadtreeTile
{
public:
    enum State
    {
        START,
        LOADING,
        DONE,
        FAILED
    };

    QuadtreeTile(TilingScheme *tilingScheme, int x, int y, int level, QuadtreeTile *parent = nullptr);
    ~QuadtreeTile();

    int x() const { return _x; }
    int y() const { return _y; }
    int level() const { return _level; }

    State state() const { return _state; }
    void setState(State state) { _state = state; }

    GlobeSurfaceTile *data() const { return _data; }
    void setData(GlobeSurfaceTile *data) { _data = data; }

    bool renderable() const { return _renderable; }
    void setRenderable(bool renderable) { _renderable = renderable; }

    bool upsampledFromParent() const { return _upsampledFromParent; }
    void setUpsampledFromParent(bool upsampledFromParent) { _upsampledFromParent = upsampledFromParent; }

    quint64 frameRendered() const { return _frameRendered; }
    void setFrameRendered(quint64 frame) { _frameRendered = frame; }

    bool needUpdateCustomData() const;
    void setNeedUpdateCustomData(bool updated);

    QuadtreeTile *child(int i, int j);
    void removeChild(QuadtreeTile *child);
    QuadtreeTile *parent() const { return _parent; }

    QuadtreeTile *northwestChild();
    QuadtreeTile *northeastChild();
    QuadtreeTile *southwestChild();
    QuadtreeTile *southeastChild();

    QuadtreeTile *findNorthwestChild() const { return _children[0]; }
    QuadtreeTile *findNortheastChild() const { return _children[1]; }
    QuadtreeTile *findSouthwestChild() const { return _children[2]; }
    QuadtreeTile *findSoutheastChild() const { return _children[3]; }

    const LiRectangle &rectangle() const { return _rectangle; }
    bool containsCartographic(const Cartographic &cartographic) const;

    double distance() const;

    bool needsLoading() const { return _state < DONE; }
    bool eligibleForUnloading() const;

    void freeResources();

    QuadtreeTile *replacementPrevious() const;
    void setReplacementPrevious(QuadtreeTile *replacementPrevious);

    QuadtreeTile *replacementNext() const;
    void setReplacementNext(QuadtreeTile *replacementNext);

private:
    friend class QuadtreePrimitive;

    int _x;
    int _y;
    int _level;
    State _state;
    QuadtreeTile *_parent;
    QuadtreeTile *_children[4];
    GlobeSurfaceTile *_data;
    LiRectangle _rectangle;
    bool _renderable;
    bool _upsampledFromParent;
    mutable double _distance;
    mutable quint64 _updatedDistanceFrame = 0;
    QuadtreeTile *_replacementPrevious;
    QuadtreeTile *_replacementNext;
    quint64 _frameRendered;
    TilingScheme *_tilingScheme;
    bool _needUpdateCustomData;
    int _lastIndex = 0;
};

#endif // QUADTREETILE_H
