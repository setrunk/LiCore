#ifndef ORIENTEDBOUNDINGBOX_H
#define ORIENTEDBOUNDINGBOX_H

#include "licore_global.h"
#include "cartesian3.h"
#include "matrix3.h"
#include "matrix4.h"
#include "rectangle.h"
#include "axisalignedboundingbox.h"

class Ellipsoid;
class EllipsoidTangentPlane;

/**
 * @brief
 * 方向包围盒OBB，不同于AxisAlignedBoundingBox（AABB），
 * OrientedBoundingBox是可旋转的，而不会改变它的大小形状。
 */
class LICORE_EXPORT OrientedBoundingBox
{
public:
    /**
     * @brief
     *
     */
    OrientedBoundingBox() {}
    /**
     * @brief
     *
     * @param iCenter
     * @param iHalfAxes
     */
    OrientedBoundingBox(const Vector3 &iCenter, const Matrix3 &iHalfAxes)
        : center(iCenter)
        , halfAxes(iHalfAxes)
    {
    }

    /**
     * @brief
     *
     * @param aabb
     * @param modelMatrix
     */
    OrientedBoundingBox(const AxisAlignedBoundingBox &aabb, const Matrix4 &modelMatrix);

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const { return center.isNull(); }

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 dirU() const { return halfAxes.column(0).normalized(); }
    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 dirV() const { return halfAxes.column(1).normalized(); }
    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 dirW() const { return halfAxes.column(2).normalized(); }

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 size() const;
    /**
     * @brief
     *
     * @return Matrix4
     */
    Matrix4 matrix() const;
    /**
     * @brief
     *
     * @return QVector<Vector3>
     */
    QVector<Vector3> corners() const;
    /**
     * @brief
     *
     * @return LiRectangle
     */
    LiRectangle rectangle() const;
    /**
     * @brief
     *
     * @return AxisAlignedBoundingBox
     */
    AxisAlignedBoundingBox localAABB() const;

    /**
     * @brief
     *
     * @param cartesian
     * @return double
     */
    double distanceTo(const Vector3 &cartesian) const;
    /**
     * @brief
     *
     * @param cartesian
     * @return double
     */
    double distanceSquaredTo(const Vector3 &cartesian) const;

    /**
     * @brief
     *
     * @param rectangle
     * @param minimumHeight
     * @param maximumHeight
     * @param ellipsoid
     * @return OrientedBoundingBox
     */
    static OrientedBoundingBox fromRectangle(const LiRectangle &rectangle,
                                             double minimumHeight,
                                             double maximumHeight,
                                             Ellipsoid *ellipsoid);

    /**
     * @brief
     *
     * @param cartesian
     * @param box
     * @return OrientedBoundingBox
     */
    static OrientedBoundingBox fromCartesianAABB(const Vector3 &cartesian, const AxisAlignedBoundingBox &box);

    /**
     * @brief
     *
     * @param tangentPlane
     * @param minimumX
     * @param maximumX
     * @param minimumY
     * @param maximumY
     * @param minimumZ
     * @param maximumZ
     * @return OrientedBoundingBox
     */
    static OrientedBoundingBox fromTangentPlaneExtents(EllipsoidTangentPlane *tangentPlane,
                                                       double minimumX, double maximumX,
                                                       double minimumY, double maximumY,
                                                       double minimumZ, double maximumZ);

    /**
     * @brief
     *
     * @param tangentPlane
     * @param box
     * @return OrientedBoundingBox
     */
    static OrientedBoundingBox fromTangentPlaneExtents(EllipsoidTangentPlane *tangentPlane, const AxisAlignedBoundingBox &box);

public:
    Vector3 center; /**< TODO: describe */
    Matrix3 halfAxes; /**< TODO: describe */
};

Q_DECLARE_METATYPE(OrientedBoundingBox)

#endif // ORIENTEDBOUNDINGBOX_H
