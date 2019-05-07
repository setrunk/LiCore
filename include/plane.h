#ifndef PLANE_H
#define PLANE_H

#include "licore_global.h"
#include "vector3.h"
#include "vector4.h"

/**
 * @brief
 * 三维空间平面，表达了三维空间中一个无限大的平面，由一个三维点和一个方向矢量组成。
 */
class LICORE_EXPORT Plane
{
public:
    /**
     * @brief
     *
     */
    Plane();
    /**
     * @brief
     *
     * @param n
     * @param d
     */
    Plane(const Vector3 &n, double d);
    /**
     * @brief
     *
     * @param p
     * @param n
     */
    Plane(const Vector3 &p, const Vector3 &n);
    /**
     * @brief
     *
     * @param cartesian
     */
    Plane(const Vector4 &cartesian);

    /**
     * @brief
     *
     * @param cartesian
     * @return Plane &operator
     */
    Plane &operator =(const Vector4 &cartesian);

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator==(const Plane &other) const
    {
        return normal == other.normal && distance == other.distance;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator!=(const Plane &other) const
    {
        return normal != other.normal || distance != other.distance;
    }

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @param v3
     */
    void create(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3);

    /**
     * @brief
     *
     * @param point
     * @return double
     */
    double getPointDistance(const Vector3 &point) const;

    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const { return QVariant::fromValue(*this); }

public:
    static Plane ORIGIN_XY_PLANE; /**< TODO: describe */
    static Plane ORIGIN_YZ_PLANE; /**< TODO: describe */
    static Plane ORIGIN_ZX_PLANE; /**< TODO: describe */

    Vector3 normal; /**< TODO: describe */
    double distance; /**< TODO: describe */
};

Q_DECLARE_METATYPE(Plane)

#endif // PLANE_H
