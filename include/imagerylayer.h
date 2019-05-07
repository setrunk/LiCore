#ifndef IMAGERYLAYER_H
#define IMAGERYLAYER_H

#include <QtCore>
#include "rectangle.h"
#include "cartesian4.h"
#include "lirequest.h"

class Imagery;
class ImageryProvider;
class ImageryLayerCollection;
class TileImagery;
class QuadtreeTile;
class TerrainProvider;
class FrameState;

/**
 * @brief
 * ImageryLayer代表一个影像图层，地球可以叠加多个影像图层
 * 图层可以随时隐藏或显示。
 */
class LICORE_EXPORT ImageryLayer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     * 影像剖切方向
     */
    enum SplitDirection
    {
        LEFT = -1,
        NONE = 0,
        RIGHT = 1
    };

    /**
     * @brief
     * 构造函数
     * @param provider
     * 影像切片服务
     * @param minimumTerrainLevel
     * 指定该影像图层显示的最低LOD级别
     * @param maximumTerrainLevel
     * 指定该影像图层显示的最高LOD级别
     * @param rect
     * 指定该影像图层的坐标范围，如果不指定，内部会自动计算范围
     * @param parent
     */
    ImageryLayer(ImageryProvider *provider,
                 int minimumTerrainLevel = 0,
                 int maximumTerrainLevel = 100,
                 const LiRectangle &rect = LiRectangle::MAX_VALUE,
                 QObject *parent = 0);

    /**
     * @brief
     * 返回影像图层所用的影像切片服务
     * @return ImageryProvider
     */
    ImageryProvider *imageryProvider() const { return _imageryProvider; }

    /**
     * @brief
     * 返回影像图层的坐标范围
     * @return LiRectangle
     */
    LiRectangle rectangle() const;

    /**
     * @brief
     * 查询该影像图层是否第一个图层
     * @return bool
     */
    bool isBaseLayer() const { return _isBaseLayer; }

    /**
     * @brief
     * 返回影像图层的图片是否带Alpha通道
     * @return float
     */
    float alpha() const { return _alpha; }

    /**
     * @brief
     * 请求影像切片操作，由于优先级的关系，请求不一定会成功
     * @param imagery
     * 保存请求影像切片数据的对象
     * @param priorityFunc
     * 计算请求优先级的函数
     */
    virtual void requestImagery(Imagery *imagery, PriorityFunction priorityFunc);

    /**
     * @brief
     * 返回该影像图层在地球所有的图层合集中的序号
     * @return int
     */
    int layerIndex() const;

    /**
     * @brief
     * 设置该影像图层在地球所有的图层合集中的序号
     * @param layerIndex
     */
    void setLayerIndex(int layerIndex);

    /**
     * @brief
     * 查询影像图层是否显示
     * @return bool
     */
    bool show() const { return _show; }

    /**
     * @brief
     * 设置影像图层是否显示
     * @param show
     */
    void setShow(bool show);

    /**
     * @brief
     * 查询该影像图层是否第一个图层
     * @return bool
     */
    bool baseLayer() const;

    /**
     * @brief
     * 设置该影像图层是否第一个图层
     * @param baseLayer
     */
    void setBaseLayer(bool baseLayer);

    /**
     * @brief
     * 从内部缓存中查找特定的影像切片数据，如果查询不到，则返回空对象
     * @param x
     * X方向的序号
     * @param y
     * Y方向的序号
     * @param level
     * LOD层级
     * @param imageryRectangle
     * 指定影像切片的坐标范围
     * @return Imagery 如果查询成功则返回有效对象，否则返回空对象（nullptr）
     */
    Imagery *getImageryFromCache(int x, int y, int level, const LiRectangle &imageryRectangle = LiRectangle());

    /**
     * @brief
     * 从内部缓存中移除特定的影像切片数据
     * @param imagery
     */
    void removeImageryFromCache(Imagery *imagery);

    /**
     * @brief
     * 查询影像图层可见部分的坐标范围
     * @return LiRectangle
     */
    LiRectangle getViewableRectangle();

    /**
     * @brief
     * 在影像切片服务没有初始化完成前，创建空白的切片对象
     * @param tile
     * 需要创建影像切片的瓦片节点
     * @param terrainProvider
     * 地形数据服务对象
     * @param insertionPoint
     * 在瓦片节点的切片合集中的插入点
     * @return bool
     */
    bool createTileImagerySkeletons(QuadtreeTile *tile, TerrainProvider *terrainProvider, int insertionPoint = -1);

    /**
     * @brief
     * 计算瓦片节点向上采用时的纹理坐标缩放和偏移量
     * @param tile
     * 需要计算的瓦片节点
     * @param tileImagery
     * 向上采样的影像切片数据
     * @return Cartesian4 xy分量表示偏移量，zw分量表示缩放值
     */
    Cartesian4 calculateTextureTranslationAndScale(QuadtreeTile *tile, TileImagery *tileImagery);

signals:
    void layerShownOrHidden(ImageryLayer *layer, int index, bool show);

private:
    QString getImageryCacheKey(int x, int y, int level);
    int getLevelWithMaximumTexelSpacing(double texelSpacing, double latitudeClosestToEquator);

    ImageryProvider *_imageryProvider; /**< TODO: describe */
    int _layerIndex; /**< TODO: describe */
    bool _show; /**< TODO: describe */
    bool _lastShow; /**< TODO: describe */
    bool _isBaseLayer; /**< TODO: describe */
    int _minimumTerrainLevel; /**< TODO: describe */
    int _maximumTerrainLevel; /**< TODO: describe */
    LiRectangle _rectangle; /**< TODO: describe */
    float _alpha; /**< TODO: describe */
    float _brightness; /**< TODO: describe */
    float _contrast; /**< TODO: describe */
    float _hue; /**< TODO: describe */
    float _saturation; /**< TODO: describe */
    float _gamma; /**< TODO: describe */
    SplitDirection _splitDirection; /**< TODO: describe */
    TileImagery *_skeletonPlaceholder; /**< TODO: describe */
    QHash<QString, Imagery *> _imageryCache; /**< TODO: describe */

    friend class ImageryLayerCollection;
};

#endif // IMAGERYLAYER_H
