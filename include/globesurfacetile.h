#ifndef GLOBESURFACETILE_H
#define GLOBESURFACETILE_H

#include "licore_global.h"
#include "cartesian3.h"
#include "boundingsphere.h"
#include "orientedboundingbox.h"
#include "tileboundingbox.h"
#include "boundingvolume.h"
#include "nodeconnections.h"
#include "ray.h"

class FrameState;
class TerrainProvider;
class QuadtreeTile;
class TileTerrain;
class TerrainData;
class TileImagery;
class Imagery;
class ImageryLayerCollection;
class VertexArray;
class TerrainMesh;
class LiTexture;
class LiFlattenMask;
class GlobeSurfaceTileProvider;

class LICORE_EXPORT GlobeSurfaceTile
{
    friend class GlobeSurfaceTileProvider;
public:
    GlobeSurfaceTile();
    ~GlobeSurfaceTile();

    QSharedPointer<TerrainData> terrainData() const { return _terrainData; }
    QSharedPointer<VertexArray> vertexArray() const { return _vertexArray; }
    QSharedPointer<TerrainMesh> terrainMesh() const { return _terrainMesh; }

    void setTerrainMesh(const QSharedPointer<TerrainMesh> &terrainMesh);

    QVector<TileImagery *> imagery() const { return _imagery; }
    void insertImagery(int insertPoint, TileImagery *imagery);
    void removeImagery(TileImagery *imagery);

    void freeResources();

    Cartesian3 center() const;
    void setCenter(const Cartesian3 &center);

    double minimumHeight() const;
    void setMinimumHeight(double minimumHeight);

    double maximumHeight() const;
    void setMaximumHeight(double maximumHeight);

    BoundingVolume boundingVolume() const;
    void setBoundingVolume(const BoundingVolume &boundingVolume);

    Cartesian3 occludeePointInScaledSpace() const;
    void setOccludeePointInScaledSpace(const Cartesian3 &occludeePointInScaledSpace);

    bool eligibleForUnloading() const;
    bool hasWaterMaskTexture() const { return _waterMaskTexture.data() != nullptr; }
    QSharedPointer<LiTexture> waterMaskTexture() const { return _waterMaskTexture; }
    Cartesian4 waterMaskTranslationAndScale() const { return _waterMaskTranslationAndScale; }

    LiTexture *decalTexture() const { return _decalTexture; }
    void setDecalTexture(LiTexture *decal) { _decalTexture = decal; }

    bool isTerrainMeshReady() const;

    static void createWaterMaskTextureIfNeeded(GlobeSurfaceTile *surfaceTile);
    static void upsampleWaterMask(QuadtreeTile *tile);

    static void processStateMachine(QuadtreeTile *tile,
                                    FrameState *frameState,
                                    TerrainProvider *terrainProvider,
                                    ImageryLayerCollection *imageryLayerCollection);

    void processFlattenMasks(QuadtreeTile *tile);

    static void processTerrainStateMachine(QuadtreeTile *tile,
                                           FrameState *frameState,
                                           TerrainProvider *terrainProvider);

    static void prepareNewTile(QuadtreeTile *tile,
                               TerrainProvider *terrainProvider,
                               ImageryLayerCollection *imageryLayerCollection);

    static void propagateNewLoadedDataToChildren(QuadtreeTile *tile);
    static void propagateNewLoadedDataToChildTile(QuadtreeTile *tile,
                                                  GlobeSurfaceTile *surfaceTile,
                                                  QuadtreeTile *childTile);

    static void propagateNewUpsampledDataToChildren(QuadtreeTile *tile);
    static void propagateNewUpsampledDataToChild(QuadtreeTile *tile, QuadtreeTile *childTile);


    static TileTerrain *getUpsampleTileDetails(QuadtreeTile *tile);

    static bool isDataAvailable(QuadtreeTile *tile, TerrainProvider *terrainProvider);

    Cartesian3 getPosition(int index);
    bool pick(const Ray &ray, bool cullBackFaces, Cartesian3 *result);
    double getHeight(const Cartographic &position) const;

    void addFlattenMask(QuadtreeTile *tile, LiFlattenMask *mask);
    void removeFlattenMask(QuadtreeTile *tile, LiFlattenMask *mask);
    QVector<LiFlattenMask *> flattenMasks() const { return _flattenMasks; }
    int maskId() const { return _maskId; }

public slots:

private:
    Cartesian3 _center;
    double _minimumHeight;
    double _maximumHeight;
    BoundingVolume _boundingVolume;
    Cartesian3 _occludeePointInScaledSpace;
    TileTerrain *_loadedTerrain;
    TileTerrain *_upsampledTerrain;
    QSharedPointer<TerrainData> _terrainData;
    QSharedPointer<VertexArray> _vertexArray;
    QSharedPointer<TerrainMesh> _terrainMesh;
    QVector<TileImagery *> _imagery;
    LiTexture *_decalTexture = nullptr;
    Cartesian4 _waterMaskTranslationAndScale;
    QSharedPointer<LiTexture> _waterMaskTexture;
    static QSharedPointer<LiTexture> _allWaterTexture;

    int _maskId = 0;
    QVector<LiFlattenMask *> _flattenMasks;
    NodeConnections _connections;
};

#endif // GLOBESURFACETILE_H
