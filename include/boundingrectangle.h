#ifndef BOUNDINGRECTANGLE_H
#define BOUNDINGRECTANGLE_H

#include "licore_global.h"
#include "cartesian3.h"
#include "vector3.h"

/**
 * @brief
 * BoundingRectangle定义了二维平面空间的范围。
 */
class LICORE_EXPORT BoundingRectangle
{
public:
    /**
     * @brief
     *
     */
    BoundingRectangle()
        : x(0)
        , y(0)
        , width(0)
        , height(0)
    {
    }

    /**
     * @brief
     *
     * @param _x
     * @param _y
     * @param _w
     * @param _h
     */
    BoundingRectangle(double _x, double _y, double _w, double _h)
        : x(_x)
        , y(_y)
        , width(_w)
        , height(_h)
    {
    }

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const
    {
        return x == 0 && y == 0 && width == 0 && height == 0;
    }

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 center() const
    {
        return Vector3(x + width*0.5, y + height*0.5, 0.0);
    }

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 minimum() const
    {
        return Vector3(x, y, 0);
    }

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 maximum() const
    {
        return Vector3(x+width, y+height, 0);
    }

    /**
     * @brief
     *
     * @param v
     * @return bool
     */
    bool contains(const Vector3 &v) const
    {
        return v.x() > x && v.x() < (x + width) &&
               v.y() > y && v.y() < (y + height);
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return BoundingRectangle
     */
    static BoundingRectangle unions(const BoundingRectangle &left, const BoundingRectangle &right);
    /**
     * @brief
     *
     * @param rectangle
     * @param point
     * @return BoundingRectangle
     */
    static BoundingRectangle expand(const BoundingRectangle &rectangle, const Cartesian3 &point);
    /**
     * @brief
     *
     * @param left
     * @param right
     * @return int
     */
    static int intersect(const BoundingRectangle &left, const BoundingRectangle &right);

public:
    double x; /**< TODO: describe */
    double y; /**< TODO: describe */
    double width; /**< TODO: describe */
    double height; /**< TODO: describe */
};

#endif // BOUNDINGRECTANGLE_H
