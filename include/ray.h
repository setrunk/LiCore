#ifndef RAY_H
#define RAY_H

#include "licore_global.h"
#include "vector3.h"

/**
 * @brief
 * 三维空间的射线，可用于拾取操作的检测计算。
 */
class LICORE_EXPORT Ray
{
public:
    /**
     * @brief
     *
     */
    Ray()
        : origin(0, 0, 0)
        , direction(0, 1, 0)
    {
    }

    /**
     * @brief
     *
     * @param o
     * @param d
     */
    Ray(const Vector3 &o, const Vector3 &d)
        : origin(o)
        , direction(d)
    {
    }

    /**
     * @brief
     *
     * @param value
     */
    Ray(const QJSValue &value);

    /**
     * @brief
     *
     * @param t
     * @return Vector3
     */
    Vector3 getPoint(double t) const
    {
        return origin + direction * t;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator==(const Ray &other) const
    {
        return origin == other.origin && direction == other.direction;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator!=(const Ray &other) const
    {
        return origin != other.origin || direction != other.direction;
    }

    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const { return QVariant::fromValue(*this); }

public:
    Vector3 origin; /**< TODO: describe */
    Vector3 direction; /**< TODO: describe */
};

Q_DECLARE_METATYPE(Ray)

#endif // RAY_H
