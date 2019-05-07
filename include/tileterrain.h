#ifndef TILETERRAIN_H
#define TILETERRAIN_H

#include "licore_global.h"

class VertexArray;
class QuadtreeTile;
class FrameState;
class TerrainProvider;
class TerrainData;
class TerrainMesh;
class LiGeometryRenderer;

/**
 * @brief
 * 地形切片数据，保存了被加载的资源数据以及向上采样的地形模型数据。
 */
class LICORE_EXPORT TileTerrain
{
public:
    /**
     * @brief
     *
     */
    enum State
    {
        FAILED = 0,
        UNLOADED = 1,
        RECEIVING = 2,
        RECEIVED = 3,
        TRANSFORMING = 4,
        TRANSFORMED = 5,
        READY = 6
    };

    /**
     * @brief
     *
     */
    TileTerrain();
    /**
     * @brief
     *
     * @param parentX
     * @param parentY
     * @param parentLevel
     * @param parentData
     */
    TileTerrain(int parentX, int parentY, int parentLevel, QSharedPointer<TerrainData> parentData);
    /**
     * @brief
     *
     */
    ~TileTerrain();

    /**
     * @brief
     *
     */
    void addRef();
    /**
     * @brief
     *
     */
    void release();

    /**
     * @brief
     *
     * @return QSharedPointer<TerrainMesh>
     */
    QSharedPointer<TerrainMesh> terrainMesh() const;
    /**
     * @brief
     *
     * @return QSharedPointer<TerrainData>
     */
    QSharedPointer<TerrainData> terrainData() const { return _terrainData; }
    /**
     * @brief
     *
     * @return QSharedPointer<VertexArray>
     */
    QSharedPointer<VertexArray> vertexArray() const { return _vertexArray; }

    /**
     * @brief
     *
     * @return State
     */
    State state() const { return _state; }
    /**
     * @brief
     *
     * @param state
     */
    void setState(State state) { _state = state; }

    /**
     * @brief
     *
     * @param data
     */
    void setTerrainData(TerrainData *data) { _terrainData.reset(data); }

    /**
     * @brief
     *
     * @param tile
     */
    void publishToTile(QuadtreeTile *tile);
    /**
     * @brief
     *
     * @param frameState
     * @param terrainProvider
     * @param tile
     */
    void processLoadStateMachine(FrameState *frameState, TerrainProvider *terrainProvider, QuadtreeTile *tile);
    /**
     * @brief
     *
     * @param terrainProvider
     * @param tile
     */
    void requestTileGeometry(TerrainProvider *terrainProvider, QuadtreeTile *tile);
    /**
     * @brief
     *
     * @param frameState
     * @param terrainProvider
     * @param tile
     */
    void processUpsampleStateMachine(FrameState *frameState, TerrainProvider *terrainProvider, QuadtreeTile *tile);
    /**
     * @brief
     *
     * @param frameState
     * @param terrainProvider
     * @param x
     * @param y
     * @param level
     */
    void transform(FrameState *frameState, TerrainProvider *terrainProvider, int x, int y, int level);
    /**
     * @brief
     *
     */
    void createResources();

private:
    /**
     * @brief
     *
     */
    struct UpsampleDetails
    {
        int x; /**< TODO: describe */
        int y; /**< TODO: describe */
        int level; /**< TODO: describe */
        QSharedPointer<TerrainData> data; /**< TODO: describe */
    };

    State _state; /**< TODO: describe */
    int _ref = 1; /**< TODO: describe */
    QSharedPointer<TerrainData> _terrainData; /**< TODO: describe */
    QSharedPointer<VertexArray> _vertexArray; /**< TODO: describe */
    QSharedPointer<UpsampleDetails>_upsampleDetails; /**< TODO: describe */
};

/**
 * @brief
 *
 */
typedef QSharedPointer<TileTerrain> TileTerrainPtr;

#endif // TILETERRAIN_H
