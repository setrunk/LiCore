#ifndef CESIUM3DTILESET_H
#define CESIUM3DTILESET_H

#include "licore_global.h"
#include "libehavior.h"
#include "matrix4.h"
#include "cartographic.h"
#include "cullingvolume.h"
#include "doublylinkedlist.h"
#include "asyncfuture.h"

class Li3DTile;
class Li3DTileData;
class Li3DTileContent;
class LiBuffer;
class LiGeometry;
class LiGeometryAttribute;
class LiInstanceAttributes;
class QuadtreeTile;
class TilesetTraversal;
class TilesetCache;
class LiFlattenMask;

class LICORE_EXPORT Li3DTileset : public LiBehavior
{
    Q_OBJECT
public:
    explicit Li3DTileset(LiNode *parent = nullptr);
    explicit Li3DTileset(const QString &url, LiNode *parent = nullptr);
    virtual ~Li3DTileset();

    void update();

    QFuture<void> readyPrimose() const;

    quint64 maximumMemoryUsage() const { return _maximumMemoryUsage; }
    void setMaximumMemoryUsage(quint64 value) { _maximumMemoryUsage = value; }

    Matrix4 modelMatrix() const;
    void setModelMatrix(const Matrix4 matrix);

    bool forceTwoSided() const { return _forceTwoSided; }
    void setForceTwoSided(bool twoSided) { _forceTwoSided = twoSided; }

    bool textureFlip() const { return _textureFlip; }
    void setTextureFlip(bool flip) { _textureFlip = flip; }

    bool genMeshNormals() const { return _genMeshNormals; }
    void setGenMeshNormals(bool genMeshNormals) { _genMeshNormals = genMeshNormals; }

    double altitude() const;
    void setAltitude(double altitude);

    bool clampedTerrain() const;
    void setClampedTerrain(bool clamped);

    bool terrainSurface() const;
    void setTerrainSurface(bool terrainSurface);

    bool streamingMode() const;
    void setStreamingMode(bool mode);

    void addFlattenMask(LiFlattenMask *mask);
    void removeFlattenMask(LiFlattenMask *mask);
    QVector<LiFlattenMask *> flattenMasks() const;
    void flattenModel(LiEntity *model);

    double geometricErrorScale() const { return _geometricErrorScale; }
    void setGeometricErrorScale(double scale) { _geometricErrorScale = scale; }

    bool skipLevelOfDetail() const { return _skipLevelOfDetail; }
    void setSkipLevelOfDetail(bool skip) { _skipLevelOfDetail = skip; }

    bool debugBoundingVolume() const { return _debugBoundingVolume; }
    void setDebugBoundingVolume(bool b) { _debugBoundingVolume = b; }

    LiRectangle rectangle() const;
    Qt::Axis gltfUpAxis() const { return _gltfUpAxis; }
    quint64 frameNumber() const { return _frameNumber; }
    const CullingVolume &cullingVolume() const { return _cullingVolume; }

    Li3DTile *root() const { return _root; }

    double geometricError() const { return _geometricError * _geometricErrorScale; }
    double baseScreenSpaceError() const { return _baseScreenSpaceError; }
    double maximumScreenSpaceError() const { return _maximumScreenSpaceError; }
    double getScreenSpaceError(double geometricError, Li3DTile *tile);

    bool ready() const { return _root != nullptr; }
    bool loadSiblings() const { return _loadSiblings; }
    bool immediatelyLoadDesiredLevelOfDetail() const { return _immediatelyLoadDesiredLevelOfDetail; }

    void selectTile(Li3DTile *tile);
    void touchTile(Li3DTile *tile);
    void visitTile(Li3DTile *tile);
    void loadTile(Li3DTile *tile);
    void updateTile(Li3DTile *tile);
    void unloadTile(Li3DTile *tile);
    void destroyTile(Li3DTile *tile);
    void addEmptyTile(Li3DTile *tile);

    void updateVisibility(Li3DTile *tile);
    void updateTileVisibility(Li3DTile *tile);
    bool anyChildrenVisible(Li3DTile *tile);
    bool meetsScreenSpaceErrorEarly(Li3DTile *tile);
    bool reachedSkippingThreshold(Li3DTile *tile);

    void selectTiles();
    void requestTiles();
    void updateTiles();
    void unloadTiles();

    void requestContent(Li3DTile *tile);
    void destroySubtree(Li3DTile *tile);
    void updateTileAltitude(Li3DTile *tile);
    void updateDynamicScreenSpaceError();

    void convertGLTFUpAxis(Matrix4 &matrix);
    quint64 totalMemoryUsageInBytes() const;

    bool allTilesAdditive() const { return _allTilesAdditive; }
    void setAllTilesAdditive(bool allTilesAdditive) { _allTilesAdditive = allTilesAdditive; }

    Li3DTile *loadTileset(const QUrl &tilesetUrl, const QJsonObject &tilesetJson, Li3DTile *parentTile = nullptr);
    QFuture<Li3DTile *> loadTilesetAsync(const QUrl &tilesetUrl, const QJsonObject &tilesetJson, Li3DTile *parentTile = nullptr);
    Li3DTileData *parseTilesetData(const QUrl &tilesetUrl, const QJsonObject &tilesetJson, Li3DTile *parentTile = nullptr);

    struct Statistics
    {
        // Rendering statistics
        int selected = 0;
        int visited = 0;
        // Loading statistics
        int numberOfCommands = 0;
        int numberOfFaileds = 0;
        int numberOfPendingRequests = 0;
        int numberOfTilesProcessing = 0;
        int numberOfTilesWithContentReady = 0; // Number of tiles with content loaded, does not include empty tiles
        int numberOfTilesTotal = 0; // Number of tiles in tileset.json (and other tileset.json files as they are loaded)
        // Features statistics
        int numberOfFeaturesSelected = 0; // Number of features rendered
        int numberOfFeaturesLoaded = 0; // Number of features in memory
        int numberOfPointsSelected = 0;
        int numberOfPointsLoaded = 0;
        int numberOfTrianglesSelected = 0;
        // Styling statistics
        int numberOfTilesStyled = 0;
        int numberOfFeaturesStyled = 0;
        // Optimization statistics
        int numberOfTilesCulledWithChildrenUnion = 0;
        // Memory statistics
        int64_t geometryByteLength = 0;
        int64_t texturesByteLength = 0;
        int64_t batchTableByteLength = 0;

        void clear();
        void updatePointAndFeatureCounts(Li3DTileContent *content, bool decrement, bool load);

        void incrementSelectionCounts(Li3DTileContent *content) { updatePointAndFeatureCounts(content, false, false); }
        void incrementLoadCounts(Li3DTileContent *content) { updatePointAndFeatureCounts(content, false, true); }
        void decrementLoadCounts(Li3DTileContent *content) { updatePointAndFeatureCounts(content, true, true); }
        void dump();
    };
    Statistics _statistics;
    Statistics _statisticsLast;

signals:
    void loaded();
    void contentLoaded(LiEntity *entity);

protected:
    void initialize(const QJsonObject &tilesetJson);

    QUrl _url;
    QUrl _baseUrl;
    QJsonObject _header;
    QJsonObject _asset;
    QJsonObject _properties;
    QJsonObject _extensionsUsed;
    QJsonObject _extras;

private:
    friend class TilesetTraversal;

    Deferred<void> _readyPromise;
    Li3DTile *_root = nullptr;
    Qt::Axis _gltfUpAxis = Qt::YAxis;
    Matrix4 _yUpToZUp;
    QSharedPointer<TilesetCache> _cache;
    quint64 _loadTimestamp = 0;
    quint64 _timeSinceLoad = 0;
    quint64 _maximumMemoryUsage = 512;

    QVector<Li3DTile*> _selectedTiles;
    QVector<Li3DTile*> _requestedTiles;
    QVector<Li3DTile*> _emptyTiles;
    QVector<Li3DTile*> _selectedTilesToStyle;
    QVector<Li3DTile*> _visibleModels;
    QSet<Li3DTile*> _tilesAlitudeDirty;

    QVector<LiFlattenMask *> _flattenMasks;

    // frame state
    quint64 _frameNumber = 0;
    Cartesian3 _cameraCartesianPosition;
    Cartographic _cameraCartographicPosition;
    Cartesian3 _cameraDirectionWC;
    CullingVolume _cullingVolume;

    bool _forceTwoSided = false;
    bool _terrainSurface = false;
    bool _clampedTerrain = true;
    bool _streamingMode = true;
    bool _textureFlip = false;
    bool _genMeshNormals = false;
    bool _debugBoundingVolume = false;
    bool _cullWithChildrenBounds = false;
    bool _hasMixedContent = false;
    bool _allTilesAdditive = true;
    bool _loadSiblings = false;
    bool _skipLevelOfDetail = false;
    bool _dynamicScreenSpaceError = false;
    bool _immediatelyLoadDesiredLevelOfDetail = false;

    double _altitude = 0.0;
    double _geometricError = 0;
    double _geometricErrorScale = 1.0;
    double _maximumScreenSpaceError = 16; // default 16
    double _dynamicScreenSpaceErrorDensity = 0.00278;
    double _dynamicScreenSpaceErrorFactor = 4.0;
    double _dynamicScreenSpaceErrorHeightFalloff = 0.25;
    double _dynamicScreenSpaceErrorComputedDensity = 0.0; // Updated based on the camera position and direction
    double _baseScreenSpaceError = 1024;
    double _skipScreenSpaceErrorFactor = 16;
    int _skipLevels = 1;
};

#endif // CESIUM3DTILESET_H
