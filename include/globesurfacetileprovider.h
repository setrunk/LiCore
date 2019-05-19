#ifndef GLOBESURFACETILEPROVIDER_H
#define GLOBESURFACETILEPROVIDER_H

#include "licore_global.h"
#include "linodeid.h"
#include "quadtreetileprovider.h"
#include "intersect.h"

class QuadtreePrimitive;
class TerrainProvider;
class ImageryLayer;
class ImageryLayerCollection;
class TilingScheme;
class QuadtreeTile;
class GlobeSurfaceTile;
class Imagery;
class TileImagery;
class QuadtreeOccluders;
class LiShaderProgram;
class LiBuffer;
class VertexArray;
class LiRenderState;
class RenderStateSet;
class LiTexture;
class LiFlattenMask;

/**
 * @brief
 * 地球瓦片节点服务，提供地球几何体的四叉树节点。
 */
class LICORE_EXPORT GlobeSurfaceTileProvider : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param terrainProvider
     * @param imageryLayers
     * @param parent
     */
    GlobeSurfaceTileProvider(TerrainProvider *terrainProvider,
                             ImageryLayerCollection *imageryLayers,
                             QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~GlobeSurfaceTileProvider();

    /**
     * @brief
     *
     * @return bool
     */
    bool ready() const;
    /**
     * @brief
     *
     * @return QColor
     */
    QColor baseColor() const { return _baseColor; }
    /**
     * @brief
     *
     * @return QuadtreePrimitive
     */
    QuadtreePrimitive *quadTree() const { return _quadtree; }
    /**
     * @brief
     *
     * @return TerrainProvider
     */
    TerrainProvider *terrainProvider() const { return _terrainProvider; }
    /**
     * @brief
     *
     * @return ImageryLayerCollection
     */
    ImageryLayerCollection *imageryLayers() const { return _imageryLayers; }
    /**
     * @brief
     *
     * @return TilingScheme
     */
    TilingScheme *tilingScheme() const;
    /**
     * @brief
     *
     * @param level
     * @return double
     */
    double getLevelMaximumGeometricError(int level) const;
    /**
     * @brief
     *
     */
    void cancelReprojections();
    /**
     * @brief
     *
     * @return double
     */
    double pick();

    /**
     * @brief
     *
     * @return bool
     */
    bool eligibleForUnloading() const;

    /**
     * @brief
     *
     * @param quadtree
     */
    void setQuadtree(QuadtreePrimitive *quadtree);
    /**
     * @brief
     *
     * @param imageryLayers
     */
    void setImageryLayers(ImageryLayerCollection *imageryLayers);
    /**
     * @brief
     *
     * @param terrainProvider
     */
    void setTerrainProvider(TerrainProvider *terrainProvider);

    /**
     * @brief
     *
     * @param frameState
     */
    void initialize(FrameState *frameState);
    /**
     * @brief
     *
     * @param frameState
     */
    void beginUpdate(FrameState *frameState);
    /**
     * @brief
     *
     * @param frameState
     */
    void endUpdate(FrameState *frameState);
    /**
     * @brief
     *
     * @param frameState
     */
    void addDrawCommands(FrameState *frameState);

    /**
     * @brief
     *
     * @param tile
     * @param frameState
     */
    void showTileThisFrame(QuadtreeTile *tile, FrameState *frameState);
    /**
     * @brief
     *
     * @param frameState
     * @param tile
     */
    void loadTile(FrameState *frameState, QuadtreeTile *tile);
    /**
     * @brief
     *
     * @param tile
     * @param frameState
     * @param occluders
     * @return Intersect::Result
     */
    Intersect::Result computeTileVisibility(QuadtreeTile *tile, FrameState *frameState, QuadtreeOccluders *occluders);
    /**
     * @brief
     *
     * @param tile
     * @param frameState
     * @return double
     */
    double computeDistanceToTile(QuadtreeTile *tile, FrameState *frameState);
    /**
     * @brief
     *
     * @param tile
     * @param frameState
     */
    void addDrawCommandsForTile(QuadtreeTile *tile, FrameState *frameState);

    /**
     */
    void flattenTerrain(LiFlattenMask *mask);

    /**
     * @brief
     *
     */
    struct Debug
    {
        bool wireframe; /**< TODO: describe */
        bool boundingSphereTile; /**< TODO: describe */
        int tilesRendered; /**< TODO: describe */
        int texturesRendered; /**< TODO: describe */
    };
    Debug _debug; /**< TODO: describe */

signals:
    /**
     * @brief
     *
     */
    void layerOrderChanged();

public slots:
    /**
     * @brief
     *
     * @param layer
     * @param index
     */
    void onLayerAdded(ImageryLayer *layer, int index);
    /**
     * @brief
     *
     * @param layer
     */
    void onLayerRemoved(ImageryLayer *layer);
    /**
     * @brief
     *
     * @param layer
     * @param index
     */
    void onLayerMoved(ImageryLayer *layer, int index);
    /**
     * @brief
     *
     * @param layer
     * @param index
     * @param show
     */
    void onLayerShownOrHidden(ImageryLayer *layer, int index, bool show);

    void onFlattenMaskAdded(LiFlattenMask *mask);

    void onFlattenMaskRemoved(LiFlattenMask *mask);

private:
    /**
     * @brief
     *
     * @param a
     * @param b
     * @return bool
     */
    static bool sortTileImageryByLayerIndex(TileImagery *a, TileImagery *b);
    /**
     * @brief
     *
     * @param textureLen
     * @param quantization
     * @param showReflectiveOcean
     * @param decal
     * @return LiShaderProgram
     */
    LiShaderProgram *getShaderProgramFromCache(int textureLen, bool quantization, bool showReflectiveOcean, bool decal);
    /**
     * @brief
     *
     * @param tile
     * @param viewMatrix
     * @return Matrix4
     */
    Matrix4 modifiedModelView(QuadtreeTile *tile, const Matrix4 &viewMatrix);

    QuadtreePrimitive *_quadtree; /**< TODO: describe */
    TerrainProvider *_terrainProvider; /**< TODO: describe */
    ImageryLayerCollection *_imageryLayers; /**< TODO: describe */
    bool _layerOrderChanged; /**< TODO: describe */
    TilingScheme *_tilingScheme; /**< TODO: describe */
    QSharedPointer<RenderStateSet> m_renderState; /**< TODO: describe */
    QSharedPointer<RenderStateSet> m_blendRenderState; /**< TODO: describe */

    QColor _baseColor; /**< TODO: describe */
    bool _ready; /**< TODO: describe */
    bool _hasWaterMask = false; /**< TODO: describe */

    typedef QVector<QuadtreeTile *> QuadtreeTileList;
    QVector<QuadtreeTileList> _tilesToRenderByTextureCount; /**< TODO: describe */
};

#endif // GLOBESURFACETILEPROVIDER_H
