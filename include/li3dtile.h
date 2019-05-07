#ifndef LI3DTILE_H
#define LI3DTILE_H

#include "linode.h"
#include "boundingvolume.h"
#include "cullingvolume.h"
#include "future.h"
#include "asyncfuture.h"
#include "doublylinkedlist.h"

#include <QJsonValue>

class LiEntity;
class Li3DTileset;
class Li3DTileContent;
class TilesetTraversal;
class TilesetCache;
class QuadtreeTile;
class Li3DTileData;

class LICORE_EXPORT Li3DTile : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    enum Refine
    {
        ADD,
        REPLACE
    };

    enum ContentState
    {
        UNLOADED = 0,   // Has never been requested
        LOADING = 1,    // Is waiting on a pending request
        PROCESSING = 2, // Request received.  Contents are being processed for rendering.  Depending on the content, it might make its own requests for external data.
        READY = 3,      // Ready to render.
        EXPIRED = 4,    // Is expired and will be unloaded once new content is loaded.
        FAILED = 5      // Request failed.
    };

    enum OptimizationHint
    {
        NOT_COMPUTED = -1,
        USE_OPTIMIZATION = 1,
        SKIP_OPTIMIZATION = 0
    };

    enum Visibility
    {
        NONE = 0,                         // No children visible
        VISIBLE = 1,                      // At least one child visible
        IN_REQUEST_VOLUME = 2,            // At least one child in viewer request volume
        VISIBLE_IN_REQUEST_VOLUME = 4,    // At least one child both visible and in viewer request volume
        VISIBLE_NOT_IN_REQUEST_VOLUME = 8 // At least one child visible but not in viewer request volume
    };

    Li3DTile(Li3DTileset *tileset,
             const QUrl &basePath,
             const QJsonObject &header,
             Li3DTile *parent = nullptr);
    explicit Li3DTile(Li3DTileset *tileset, Li3DTileData *data, Li3DTile *parent = nullptr);
    ~Li3DTile();

    Li3DTileset *tileset() const { return _tileset; }
    Li3DTileContent *content() const { return _content; }
    LiEntity *boundingVolumeOutline() const { return _boxOutline; }

    ContentState contentState() const { return _contentState; }
    void setContentState(ContentState state);

    int depth() const { return _depth; }
    LiRectangle rectangle() const { return _rectangle; }
    Deferred<void> contentReadyPromise() const { return _contentReadyPromise; }

    double geometricError() const;
    double screenSpaceError() const { return _screenSpaceError; }

    Matrix4 transform() const { return _transform; }
    void setTransform(const Matrix4 &transform);

    Matrix4 computedTransform() const { return _computedTransform; }
    Matrix4 initialTransform() const { return _initialTransform; }

    BoundingVolume boundingVolume() const { return _boundingVolume; }
    BoundingVolume contentBoundingVolume() const { return _contentBoundingVolume; }
    BoundingVolume viewerRequestVolume() const { return _viewerRequestVolume; }

    Li3DTile *parent() const { return _parent; }
    int childCount() const { return _children.size(); }
    Li3DTile *child(int i) const { return _children[i]; }
    void removeAllChildren();

    Li3DTile *ancestorWithContent() const { return _ancestorWithContent; }
    Li3DTile *ancestorWithLoadedContent() const { return _ancestorWithContentAvailable; }

    void getTileData(Li3DTileData *data) const;

    bool contentReady() const { return _contentState == READY; }
    bool contentLoading() const { return _contentState == LOADING; }
    bool contentUnloaded() const { return _contentState == UNLOADED; }
    bool contentExpired() const { return _contentState == EXPIRED; }
    bool contentFailed() const { return _contentState == FAILED; }
    bool contentAvailable() const;

    bool hasEmptyContent() const { return _hasEmptyContent; }
    bool hasRenderableContent() const { return _hasRenderableContent; }
    bool hasTilesetContent() const { return _hasTilesetContent; }
    bool hasUnloadedContent() const { return !_hasEmptyContent /*&& !_hasTilesetContent*/ && contentUnloaded(); }
    bool hasAdditiveContent() const { return _refine == ADD && _hasRenderableContent; }

    bool isVisible() const { return _visible && _inRequestVolume; }
    bool contentVisible() const;
    uint visibility(uint parentVisibilityPlaneMask);
    uint contentVisibility() const;
    double getPriority();

    int refine() const { return _refine; }
    bool isReplace() const { return _refine == REPLACE; }
    bool isAdd() const { return _refine == ADD; }

    double distanceToTile(const Cartesian3 &cameraCartesianPosition, const Cartographic &cameraCartographicPosition);
    double distanceToTileCenter(const Cartesian3 &cameraPositionWC, const Cartesian3 &cameraDirectionWC);

    /////////////////////////////////////////
    void update();
    void updateContent();
    void updateExpiration();
    void updateExpireDate();
    void updateTransform();
    void unloadContent();
    void destroy();

    bool requestContent();
    bool insideViewerRequestVolume();
    bool checkChildrenWithinParent();
    void markTransformChanged();
    void createBoxOutline();

    double altitude() const { return _altitude; }
    void updateAltitude();

    void markAltitudeChanged(const LiRectangle &rect);

    QColor color() const;
    void setColor(const QColor &color);

    static BoundingVolume createBox(const QJsonArray &box, const Matrix4 &transform);
    static BoundingVolume createBoxFromTransformedRegion(const QJsonArray &region, const Matrix4 &transform, const Matrix4 &initialTransform);
    static BoundingVolume createRegion(const QJsonArray &region, const Matrix4 &transform, const Matrix4 &initialTransform);
    static BoundingVolume createSphere(const QJsonArray &sphere, const Matrix4 &transform);
    static BoundingVolume createBoundingVolume(const QJsonObject &header, const Matrix4 &matrix, const Matrix4 &initialTransform);

signals:
    void contentStateChanged(Li3DTile *tile);
    void colorChanged(const QColor &color);

private:
    friend class Li3DTileset;
    friend class TilesetTraversal;
    friend class TilesetCache;

    QUrl _contentUrl;
    QString _serverKey;
    QJsonObject _boundingVolumeHeader;
    QJsonObject _contentBoundingVolumeHeader;
    QJsonObject _viewerRequestVolumeHeader;
    Li3DTileset *_tileset = nullptr;
    Li3DTile *_parent = nullptr;
    QVector<Li3DTile*> _children;

    Matrix4 _transform;
    Matrix4 _initialTransform;
    Matrix4 _computedTransform;
    bool _transformDirty = false;
    BoundingVolume _boundingVolume;
    BoundingVolume _contentBoundingVolume;
    BoundingVolume _viewerRequestVolume;

    ContentState _contentState = UNLOADED;
    Deferred<void> _contentReadyPromise;
    Li3DTileContent *_content = nullptr;
    Li3DTileContent *_expiredContent = nullptr;
    Li3DTile *_ancestorWithContent = nullptr;
    Li3DTile *_ancestorWithContentAvailable = nullptr;
    LiEntity *_boxOutline = nullptr;
    QColor _tileColor = Qt::white;

    bool _hasEmptyContent = false;
    bool _hasRenderableContent = false;
    bool _hasTilesetContent = false;

    double _geometricError = 0;
    double _expireDuration = 0;

    DoublyLinkedList<Li3DTile*>::Node *_cacheNode = nullptr;
    OptimizationHint _optimChildrenWithinParent = NOT_COMPUTED;
    uint _visibilityPlaneMask = CullingVolume::MASK_OUTSIDE;
    QDateTime _expireDate;
    Refine _refine = REPLACE;

    LiRectangle _rectangle;
    LiRectangle _contentRectangle;
    Cartographic _centerCartographic;
    QVector<Cartographic> _cornerPositions;

    // Members that are updated when terrain data changed
    double _altitude = 0.0;
    bool _altitudeDirty = false;

    // Members that are updated every frame for tree traversal and rendering optimizations:
    double _distanceToCamera = 0;
    double _centerZDepth = 0;
    double _screenSpaceError = 0;
    double _priority = 0;
    bool _visible = false;
    bool _lastVisible = false;
    bool _inRequestVolume = true;
    bool _finalResolution = true;
    bool _refines = false;
    bool _shouldSelect = false;

    int _depth = 0;
    int _stackLength = 0;
    int _selectionDepth = 0;

    quint64 _updatedFrame = 0;
    quint64 _updatedVisibilityFrame = 0;
    quint64 _updatedPriorityFrame = 0;
    quint64 _touchedFrame = 0;
    quint64 _visitedFrame = 0;
    quint64 _selectedFrame = 0;
    quint64 _requestedFrame = 0;
    quint64 _lastStyleTime = 0;
};

#endif // LI3DTILE_H
