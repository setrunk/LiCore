#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "licore_global.h"
#include "juliandate.h"
#include "matrix3.h"
#include "matrix4.h"
#include "cartesian3.h"
#include "ellipsoid.h"

class TransformsPrivate;

/**
 * @brief
 * 提供一系列函数，在各种参考坐标系之间相互转换。
 */
class LICORE_EXPORT Transforms
{
public:
    /**
     * @brief
     * 轴方向定义
     */
    enum Axis {
        UP = 0,
        DOWN,
        SOUTH,
        NORTH,
        WEST,
        EAST
    };

    /**
     * @brief
     * 在X方向为东，Y方向为北，Z方向为向上，原点在origin点上的坐标系，计算变换矩阵
     * @param origin
     * @param ellipsoid
     * @return Matrix4
     */
    static Matrix4 eastNorthUpToFixedFrame(const Cartesian3 &origin, Ellipsoid *ellipsoid = Ellipsoid::WGS84());

    /**
     * @brief
     * 在X方向为北，Y方向为东，Z方向为向下，原点在origin点上的坐标系，计算变换矩阵
     * @param origin
     * @param ellipsoid
     * @return Matrix4
     */
    static Matrix4 northEastDownToFixedFrame(const Cartesian3 &origin, Ellipsoid *ellipsoid = Ellipsoid::WGS84());

    /**
     * @brief
     * 在X方向为北，Y方向为向上，Z方向为向东，原点在origin点上的坐标系，计算变换矩阵
     * @param origin
     * @param ellipsoid
     * @return Matrix4
     */
    static Matrix4 northUpEastToFixedFrame(const Cartesian3 &origin, Ellipsoid *ellipsoid = Ellipsoid::WGS84());

    /**
     * @brief
     * 在X方向为北，Y方向为西，Z方向为向上，原点在origin点上的坐标系，计算变换矩阵
     * @param origin
     * @param ellipsoid
     * @return Matrix4
     */
    static Matrix4 northWestUpToFixedFrame(const Cartesian3 &origin, Ellipsoid *ellipsoid = Ellipsoid::WGS84());

    /**
     * @brief
     *
     * @param firstAxis
     * @param secondAxis
     * @param origin
     * @param ellipsoid
     * @return Matrix4
     */
    static Matrix4 localFrameToFixedFrameGenerator(Axis firstAxis, Axis secondAxis, const Cartesian3 &origin, Ellipsoid *ellipsoid);

    /**
     * @brief
     *
     * @param date
     * @return Matrix3
     */
    static Matrix3 computeFixedToIcrfMatrix(const JulianDate &date);
    /**
     * @brief
     *
     * @param date
     * @return Matrix3
     */
    static Matrix3 computeIcrfToFixedMatrix(const JulianDate &date);
    /**
     * @brief
     *
     * @param date
     * @return Matrix3
     */
    static Matrix3 computeTemeToPseudoFixedMatrix(const JulianDate &date);

private:
    static TransformsPrivate *d; /**< TODO: describe */
};

#endif // TRANSFORMS_H
