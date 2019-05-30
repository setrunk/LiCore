#ifndef TILINGSCHEME_H
#define TILINGSCHEME_H

#include "rectangle.h"
#include "cartographic.h"
#include "cartesian2.h"
#include "ellipsoid.h"
#include <QPoint>

class Ellipsoid;
class MapProjection;

/**
 * @brief
 * TilingScheme是地图切片方案，描述了地图服务的坐标系统、数据坐标范围、
 * 投影方法，以及坐标与切片序号的转换等方法。
 */
class LICORE_EXPORT TilingScheme
{
public:
    /**
     * @brief
     * 析构函数
     */
    virtual ~TilingScheme() {}

    /**
     * @brief
     * 查询地图服务是否采用经纬度坐标系统
     * @return bool
     */
    virtual bool isGeographic() const { return true; }

    /**
     * @brief
     * 返回地图服务采用的椭球对象
     * @return Ellipsoid
     */
    virtual Ellipsoid *ellipsoid() const { return Ellipsoid::WGS84(); }

    /**
     * @brief
     * 返回地图服务的坐标范围
     * @return LiRectangle
     */
    virtual LiRectangle rectangle() const = 0;

    /**
     * @brief
     * 返回地图服务的原点位置
     * @return LiRectangle
     */
    virtual Cartesian2 origin() const;

    /**
     * @brief
     * 返回地图服务采用的投影方法
     * @return MapProjection
     */
    virtual MapProjection *projection() const = 0;

    /**
     * @brief
     * 查询地图服务特定LOD级别的X方向的切片数量
     * @param level
     * @return int
     */
    virtual int getNumberOfXTilesAtLevel(int level) const = 0;

    /**
     * @brief
     * 查询地图服务特定LOD级别的Y方向的切片数量
     * @param level
     * @return int
     */
    virtual int getNumberOfYTilesAtLevel(int level) const = 0;

    /**
     * @brief
     * 从经纬度坐标到本地坐标的转换
     * @param rectangle
     * @return LiRectangle
     */
    virtual LiRectangle rectangleToNativeRectangle(const LiRectangle &rectangle) const = 0;

    /**
     * @brief
     * 计算特定切片的本地坐标范围
     * @param x
     * X方向的序号
     * @param y
     * Y方向的序号
     * @param level
     * LOD层级
     * @return LiRectangle
     */
    virtual LiRectangle tileXYToNativeRectangle(int x, int y, int level) const = 0;

    /**
     * @brief
     * 计算特定切片的经纬度坐标范围
     * @param x
     * X方向的序号
     * @param y
     * Y方向的序号
     * @param level
     * LOD层级
     * @return LiRectangle
     */
    virtual LiRectangle tileXYToRectangle(int x, int y, int level) const = 0;

    /**
     * @brief
     * 计算特定坐标点的在level级别的序号
     * @param position
     * 需要计算的Cartographic坐标点
     * @param level
     * LOD层级
     * @return Cartesian2
     * x分量表示X方向的序号，y分量表示Y方向的序号
     */
    virtual Cartesian2 positionToTileXY(const Cartographic &position, int level) const = 0;
};

#endif // TILINGSCHEME_H
