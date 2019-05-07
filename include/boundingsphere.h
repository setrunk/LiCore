#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include "licore_global.h"
#include "vector3.h"
#include "matrix4.h"
#include "interval.h"
#include "orientedboundingbox.h"
#include "axisalignedboundingbox.h"

/**
 * @brief
 * BoundingSphere定义了三维坐标空间的包围球。
 * 可用与摄像机视锥快速裁切计算，
 * 比BoundingBox的计算要高效，
 * 但没有BoundingBox的计算结果准确。
 */
class LICORE_EXPORT BoundingSphere
{
public:
    /**
     * @brief
     *
     */
    BoundingSphere()
        : radius(0)
    {
    }

    /**
     * @brief
     *
     * @param c
     * @param r
     */
    BoundingSphere(const Vector3 &c, double r)
        : center(c)
        , radius(r)
    {
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator ==(const BoundingSphere &other) const
    {
        return center == other.center && radius == other.radius;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator !=(const BoundingSphere &other) const
    {
        return center != other.center || radius != other.radius;
    }

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const { return radius == 0; }
    /**
     * @brief
     *
     * @return bool
     */
    bool isValid() const { return radius != 0; }

    /**
     * @brief
     *
     * @param other
     * @return bool
     */
    bool contains(const BoundingSphere &other) const;
    /**
     * @brief
     *
     * @param other
     */
    void merge(const BoundingSphere &other);
    /**
     * @brief
     *
     * @param point
     */
    void expand(const Vector3 &point);
    /**
     * @brief
     *
     */
    void reset();
    /**
     * @brief
     *
     * @param positions
     */
    void update(const QVector<Vector3> &positions);
    /**
     * @brief
     *
     * @param matrix
     */
    void transform(const Matrix4 &matrix);

    /**
     * @brief
     *
     * @param position
     * @param direction
     * @return Interval
     */
    Interval computePlaneDistances(const Vector3 &position, const Vector3 &direction) const;
    /**
     * @brief
     *
     * @param position
     * @return double
     */
    double distanceTo(const Vector3 &position) const;

    /**
     * @brief
     *
     * @param positions
     * @param center
     * @param stride
     * @return BoundingSphere
     */
    static BoundingSphere fromVertices(const QVector<double> &positions, const Cartesian3 &center, int stride = 3);
    /**
     * @brief
     *
     * @param orientedBoundingBox
     * @return BoundingSphere
     */
    static BoundingSphere fromOrientedBoundingBox(const OrientedBoundingBox &orientedBoundingBox);
    /**
     * @brief
     *
     * @param aabb
     * @return BoundingSphere
     */
    static BoundingSphere fromAxisAlignedBoundingBox(const AxisAlignedBoundingBox &aabb);
    /**
     * @brief
     *
     * @param positions
     * @return BoundingSphere
     */
    static BoundingSphere fromPoints(const QVector<Vector3> &positions);
    /**
     * @brief
     *
     * @param positions
     * @return BoundingSphere
     */
    static BoundingSphere fromPoints(const QVector<Cartesian3> &positions);
    /**
     * @brief
     *
     * @param value
     * @return BoundingSphere
     */
    static BoundingSphere fromJSValue(const QJSValue &value);

    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const { return QVariant::fromValue(*this); }

public:
    Vector3 center; /**< TODO: describe */
    double radius; /**< TODO: describe */
};

Q_DECLARE_METATYPE(BoundingSphere)

#endif // BOUNDINGSPHERE_H
