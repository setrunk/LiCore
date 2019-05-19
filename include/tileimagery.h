#ifndef TILEIMAGERY_H
#define TILEIMAGERY_H

#include "licore_global.h"
#include "rectangle.h"
#include "cartesian4.h"

class Imagery;
class QuadtreeTile;
class FrameState;

/**
 * @brief
 * 描述了地形切片（TileTerrain）和影像切片（Imagery）之间是如何叠加的一些信息。
 */
class LICORE_EXPORT TileImagery
{
public:
    /**
     * @brief
     *
     * @param imagery
     */
    explicit TileImagery(Imagery *imagery);
    /**
     * @brief
     *
     * @param imagery
     * @param textureCoordinateRectangle
     * @param useWebMercatorT
     */
    TileImagery(Imagery *imagery, const Cartesian4 &textureCoordinateRectangle, bool useWebMercatorT);
    /**
     * @brief
     *
     */
    ~TileImagery();

    /**
     * @brief
     *
     * @return Imagery
     */
    Imagery *loadingImagery() const { return _loadingImagery; }

    /**
     * @brief
     *
     * @return Imagery
     */
    Imagery *readyImagery() const { return _readyImagery; }

    /**
     * @brief
     *
     * @return Cartesian4
     */
    Cartesian4 textureTranslationAndScale() const { return _textureTranslationAndScale; }

    /**
     * @brief
     *
     * @return Cartesian4
     */
    Cartesian4 textureCoordinateRectangle() const { return _textureCoordinateRectangle; }
    /**
     * @brief
     *
     * @return bool
     */
    bool useWebMercatorT() const { return _useWebMercatorT; }

    /**
     * @brief
     *
     */
    void freeResources();

    /**
     * @brief
     *
     * @param tile
     * @param frameState
     * @return bool
     */
    bool processStateMachine(QuadtreeTile *tile, FrameState *frameState);

private:
    Imagery *_readyImagery; /**< TODO: describe */
    Imagery *_loadingImagery; /**< TODO: describe */
    Cartesian4 _textureCoordinateRectangle; /**< TODO: describe */
    Cartesian4 _textureTranslationAndScale; /**< TODO: describe */
    bool _useWebMercatorT; /**< TODO: describe */
};

#endif // TILEIMAGERY_H
