#ifndef INTERSECT_H
#define INTERSECT_H

#include "licore_global.h"
#include "vector3.h"
#include "ray.h"
#include "plane.h"
#include "interval.h"
#include "boundingsphere.h"
#include "orientedboundingbox.h"
#include "axisalignedboundingbox.h"

/**
 * @brief
 * 提供一系列三维空间的相交检测函数。
 */
class LICORE_EXPORT Intersect
{
public:
    /**
     * @brief
     *
     */
    enum Result
    {
        OUTSIDE = -1,
        INTERSECTING = 0,
        INSIDE = 1
    };

    /**
     * @brief
     *
     * @param plane
     * @param sphere
     * @return Result
     */
    static Result planeSphere(const Plane &plane, const BoundingSphere &sphere);
    /**
     * @brief
     *
     * @param plane
     * @param box
     * @return Result
     */
    static Result planeAxisAlignedBoundingBox(const Plane &plane, const AxisAlignedBoundingBox &box);
    /**
     * @brief
     *
     * @param plane
     * @param box
     * @return Result
     */
    static Result planeOrientedBoundingBox(const Plane &plane, const OrientedBoundingBox &box);

    /**
     * @brief
     *
     * @param ray
     * @param sphere
     * @param result
     * @return bool
     */
    static bool raySphere(const Ray &ray, const BoundingSphere &sphere, Interval *result);
    /**
     * @brief
     *
     * @param ray
     * @param box
     * @param result
     * @return bool
     */
    static bool rayOrientedBoundingBox(const Ray &ray, const OrientedBoundingBox &box, Vector3 *result);
    /**
     * @brief
     *
     * @param ray
     * @param plane
     * @param result
     * @return bool
     */
    static bool rayPlane(const Ray &ray, const Plane &plane, Vector3 *result);
    /**
     * @brief
     *
     * @param ray
     * @param plane
     * @param result
     * @return bool
     */
    static bool rayPlane(const Ray &ray, const Plane &plane, Cartesian3 *result);
    /**
     * @brief
     *
     * @param ray
     * @param p0
     * @param p1
     * @param p2
     * @param cullBackFaces
     * @param result
     * @return bool
     */
    static bool rayTriangleParametric(const Ray &ray,
                                      const Vector3 &p0,
                                      const Vector3 &p1,
                                      const Vector3 &p2,
                                      bool cullBackFaces,
                                      double *result);
    /**
     * @brief
     *
     * @param ray
     * @param p0
     * @param p1
     * @param p2
     * @param cullBackFaces
     * @param result
     * @return bool
     */
    static bool rayTriangle(const Ray &ray,
                            const Vector3 &p0,
                            const Vector3 &p1,
                            const Vector3 &p2,
                            bool cullBackFaces,
                            Vector3 *result);

    /**
     * @brief
     *
     * @param a
     * @param b
     * @param c
     * @return Vector2
     */
    static Vector2 solveQuadratic(double a, double b, double c);
};

#endif // INTERSECT_H
