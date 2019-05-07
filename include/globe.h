#ifndef GLOBE_H
#define GLOBE_H

#include "ligeometryrenderer.h"
#include "cartographic.h"
#include "ray.h"

class QuadtreePrimitive;
class TerrainProvider;
class ImageryLayer;
class ImageryLayerCollection;
class TerrainSurfaceLayer;
class GlobePrivate;

/**
 * @brief
 * Globe提供了地球渲染的功能，可以自定义地形、多层影像叠加，拾取等功能。
 */
class LICORE_EXPORT Globe : public LiGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(Ellipsoid *ellipsoid READ ellipsoid)
    Q_PROPERTY(QuadtreePrimitive* surface READ surface)
    Q_PROPERTY(bool show READ show WRITE setShow NOTIFY showChanged)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit Globe(LiNode *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    ~Globe();

    /**
     * @brief
     * 返回椭球Ellipsoid对象，Ellipsoid描述了地球的形状和大小
     * @return Ellipsoid
     */
    Ellipsoid *ellipsoid() const;

    /**
     * @brief
     * 返回QuadtreePrimitive对象，
     * QuadtreePrimitive是地球的几何数据的合集，
     * 采用四叉树算法管理数据
     * @return QuadtreePrimitive
     */
    QuadtreePrimitive *surface() const;

    /**
     * @brief
     * 返回TerrainSurfaceLayer地表模型图层对象，
     * TerrainSurfaceLayer提供把三维模型作为地表层的一部分数据的功能
     * @return TerrainSurfaceLayer
     */
    TerrainSurfaceLayer *terrainSurfaceLayer() const;

    /**
     * @brief
     * 返回TerrainProvider对象，
     * TerrainProvider是DEM高程数据模型的基类接口，
     * TerrainProvider描述了瓦片的模型数据是如何获取的
     * @return TerrainProvider
     */
    TerrainProvider *terrainProvider() const;

    /**
     * @brief
     * 设置TerrainProvider对象，
     * 系统默认自带一个TerrainProvider，提供0高度的DEM数据，
     * 如果需要加载用户DEM数据，必须创建LiGlobeTerrainProvider
     *
     * @param terrainProvider
     *
     * @see LiGlobeTerrainProvider
     */
    void setTerrainProvider(TerrainProvider *terrainProvider);

    /**
     * @brief
     * 设置地形DEM瓦片数据的url路径，系统将会使用该url创建的LiGlobeTerrainProvider
     * 对象进行瓦片DEM数据获取
     * @param url
     */
    Q_INVOKABLE void setTerrainProviderUrl(const QString &url);

    /**
     * @brief
     * 返回ImageryLayerCollection对象，ImageryLayerCollection是ImageryLayer的合集
     * @return ImageryLayerCollection
     *
     * @see ImageryLayer
     */
    ImageryLayerCollection *imageryLayers() const;

    /**
     * @brief
     * 添加ImageryLayer影像图层
     * @param imageryLayer
     */
    void addImageryLayer(ImageryLayer *imageryLayer);

    /**
     * @brief
     * 返回是否显示瓦片之间的裙边，为了遮挡不同LOD级别的瓦片
     * 之间的缝隙，每个瓦片都会在四周生成一定高度的裙边
     * @return bool
     */
    Q_INVOKABLE bool showTerrainSkirts() const;

    /**
     * @brief
     * 设置是否显示瓦片之间的裙边
     * @param showSkirts
     */
    Q_INVOKABLE void setShowTerrainSkirts(bool showSkirts);

    /**
     * @brief
     * 返回是否显示地球
     * @return bool
     */
    Q_INVOKABLE bool show() const;

    /**
     * @brief
     * 设置是否显示地球
     * @param show
     */
    Q_INVOKABLE void setShow(bool show);

    /**
     * @brief
     * 返回地球渲染的背景颜色
     * @return QColor
     */
    Q_INVOKABLE QColor baseColor() const;

    /**
     * @brief
     * 设置地球渲染的背景颜色
     * @param baseColor
     */
    Q_INVOKABLE void setBaseColor(const QColor &baseColor);

    /**
     * @brief
     * 在js/qml中添加影像图层
     * @param imageryLayer
     */
    Q_INVOKABLE void addImageryLayer(const QJSValue &imageryLayer);

    /**
     * @brief
     * 在js/qml中添加ArcGis提供的全球影像图层
     * @param imageryLayer
     */
    Q_INVOKABLE void addArcGisMapServerImageryLayer(const QJSValue &imageryLayer);

    /**
     * @brief
     * 获取cartographic坐标点的地形海拔高度
     * @param cartographic
     * 需要获取海拔高度的经纬度坐标
     * @param includeTerrainSurface
     * 是否计算三维模型地表层的高度
     * @return double 海拔高度
     */
    double getHeight(const Cartographic &cartographic, bool includeTerrainSurface = false) const;

    /**
     * @brief
     * 在js/qml中获取cartographic坐标点的地形海拔高度
     * @param cartographic
     * 需要获取海拔高度的经纬度坐标
     * @param includeTerrainSurface
     * 是否计算三维模型地表层的高度
     * @return double 海拔高度
     */
    Q_INVOKABLE double getHeight(const QJSValue &cartographic, bool includeTerrainSurface = false) const;

    /**
     * @brief
     *
     * @param ray
     * @param result
     * @return bool
     */
    Q_INVOKABLE bool pick(const Ray &ray, Cartesian3 *result) const;

    /**
     * @brief
     *
     * @param ray
     * @param scene
     * @param result
     * @return QJSValue
     */
    Q_INVOKABLE QJSValue pick(const QJSValue &ray, const QJSValue &scene, QJSValue result) const;

signals:
    void showChanged();

private:
    Q_DECLARE_PRIVATE(Globe)
};

#endif // GLOBE_H
