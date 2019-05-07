#ifndef VECTOR2_H
#define VECTOR2_H

#include "licore_global.h"
#include "cartesian2.h"
#include "limath.h"

class Vector3;
class Vector4;

/**
 * @brief
 * 二维空间的坐标点。
 * 在js/qml中使用Li.vector2(x,y)函数构造。
 */
class LICORE_EXPORT Vector2
{
public:
    /**
     * @brief
     *
     */
    Vector2();
    /**
     * @brief
     *
     * @param Qt::Initialization
     */
    explicit Vector2(Qt::Initialization) {}
    /**
     * @brief
     *
     * @param xpos
     * @param ypos
     */
    Vector2(double xpos, double ypos);
    /**
     * @brief
     *
     * @param vector
     */
    Vector2(const QVector2D &vector);

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const;

    /**
     * @brief
     *
     * @return double
     */
    double x() const;
    /**
     * @brief
     *
     * @return double
     */
    double y() const;

    /**
     * @brief
     *
     * @param x
     */
    void setX(double x);
    /**
     * @brief
     *
     * @param y
     */
    void setY(double y);

    /**
     * @brief
     *
     * @param i
     * @return double &operator
     */
    double &operator[](int i);
    /**
     * @brief
     *
     * @param i
     * @return double operator
     */
    double operator[](int i) const;

    /**
     * @brief
     *
     * @return double
     */
    double length() const;
    /**
     * @brief
     *
     * @return double
     */
    double lengthSquared() const; //In Qt 6 convert to inline and constexpr

    /**
     * @brief
     *
     * @return Vector2
     */
    Vector2 normalized() const;
    /**
     * @brief
     *
     * @return Vector2
     */
    Vector2 &normalize();

    /**
     * @brief
     *
     * @param point
     * @return double
     */
    double distanceToPoint(const Vector2 &point) const;
    /**
     * @brief
     *
     * @param point
     * @param direction
     * @return double
     */
    double distanceToLine(const Vector2& point, const Vector2& direction) const;

    /**
     * @brief
     *
     * @param vector
     * @return Vector2 &operator
     */
    Vector2 &operator+=(const Vector2 &vector);
    /**
     * @brief
     *
     * @param vector
     * @return Vector2 &operator
     */
    Vector2 &operator-=(const Vector2 &vector);
    /**
     * @brief
     *
     * @param factor
     * @return Vector2 &operator
     */
    Vector2 &operator*=(double factor);
    /**
     * @brief
     *
     * @param vector
     * @return Vector2 &operator
     */
    Vector2 &operator*=(const Vector2 &vector);
    /**
     * @brief
     *
     * @param divisor
     * @return Vector2 &operator
     */
    Vector2 &operator/=(double divisor);
    /**
     * @brief
     *
     * @param vector
     * @return Vector2 &operator
     */
    inline Vector2 &operator/=(const Vector2 &vector);

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return double
     */
    static double dot(const Vector2& v1, const Vector2& v2); //In Qt 6 convert to inline and constexpr
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return double
     */
    static double dotProduct(const Vector2& v1, const Vector2& v2); //In Qt 6 convert to inline and constexpr
    /**
     * @brief
     *
     * @param start
     * @param end
     * @param t
     * @return Vector2
     */
    static Vector2 lerp(const Vector2 &start, const Vector2 &end, double t);

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool operator
     */
    friend inline bool operator==(const Vector2 &v1, const Vector2 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool operator
     */
    friend inline bool operator!=(const Vector2 &v1, const Vector2 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector2 operator
     */
    friend inline const Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector2 operator
     */
    friend inline const Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
    /**
     * @brief
     *
     * @param factor
     * @param vector
     * @return const Vector2 operator
     */
    friend inline const Vector2 operator*(double factor, const Vector2 &vector);
    /**
     * @brief
     *
     * @param vector
     * @param factor
     * @return const Vector2 operator
     */
    friend inline const Vector2 operator*(const Vector2 &vector, double factor);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector2 operator
     */
    friend inline const Vector2 operator*(const Vector2 &v1, const Vector2 &v2);
    /**
     * @brief
     *
     * @param vector
     * @return const Vector2 operator
     */
    friend inline const Vector2 operator-(const Vector2 &vector);
    /**
     * @brief
     *
     * @param vector
     * @param divisor
     * @return const Vector2 operator
     */
    friend inline const Vector2 operator/(const Vector2 &vector, double divisor);
    /**
     * @brief
     *
     * @param vector
     * @param divisor
     * @return const Vector2 operator
     */
    friend inline const Vector2 operator/(const Vector2 &vector, const Vector2 &divisor);

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool
     */
    friend inline bool qFuzzyCompare(const Vector2& v1, const Vector2& v2);

    /**
     * @brief
     *
     * @return operator
     */
    operator Cartesian2() const;
    /**
     * @brief
     *
     * @return operator
     */
    operator QVector2D() const;
    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const;

private:
    double xp, yp; /**< TODO: describe */

    friend class Vector3;
    friend class Vector4;
};

Q_DECLARE_METATYPE(Vector2)
Q_DECLARE_TYPEINFO(Vector2, Q_PRIMITIVE_TYPE);

/**
 * @brief
 *
 */
inline Vector2::Vector2() : xp(0.0), yp(0.0) {}

/**
 * @brief
 *
 * @param xpos
 * @param ypos
 */
inline Vector2::Vector2(double xpos, double ypos) : xp(xpos), yp(ypos) {}

/**
 * @brief
 *
 * @param vector
 */
inline Vector2::Vector2(const QVector2D &vector) : xp(vector.x()), yp(vector.y()) {}

/**
 * @brief
 *
 * @return bool
 */
inline bool Vector2::isNull() const
{
    return qIsNull(xp) && qIsNull(yp);
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector2::x() const { return xp; }
/**
 * @brief
 *
 * @return double
 */
inline double Vector2::y() const { return yp; }

/**
 * @brief
 *
 * @param aX
 */
inline void Vector2::setX(double aX) { xp = aX; }
/**
 * @brief
 *
 * @param aY
 */
inline void Vector2::setY(double aY) { yp = aY; }

/**
 * @brief
 *
 * @param i
 * @return double &Vector2::operator
 */
inline double &Vector2::operator[](int i)
{
    Q_ASSERT(uint(i) < 2u);
    return *(&xp + i);
}

/**
 * @brief
 *
 * @param i
 * @return double Vector2::operator
 */
inline double Vector2::operator[](int i) const
{
    Q_ASSERT(uint(i) < 2u);
    return *(&xp + i);
}

/**
 * @brief
 *
 * @param vector
 * @return Vector2 &Vector2::operator
 */
inline Vector2 &Vector2::operator+=(const Vector2 &vector)
{
    xp += vector.xp;
    yp += vector.yp;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector2 &Vector2::operator
 */
inline Vector2 &Vector2::operator-=(const Vector2 &vector)
{
    xp -= vector.xp;
    yp -= vector.yp;
    return *this;
}

/**
 * @brief
 *
 * @param factor
 * @return Vector2 &Vector2::operator
 */
inline Vector2 &Vector2::operator*=(double factor)
{
    xp *= factor;
    yp *= factor;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector2 &Vector2::operator
 */
inline Vector2 &Vector2::operator*=(const Vector2 &vector)
{
    xp *= vector.xp;
    yp *= vector.yp;
    return *this;
}

/**
 * @brief
 *
 * @param divisor
 * @return Vector2 &Vector2::operator
 */
inline Vector2 &Vector2::operator/=(double divisor)
{
    xp /= divisor;
    yp /= divisor;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector2 &Vector2::operator
 */
inline Vector2 &Vector2::operator/=(const Vector2 &vector)
{
    xp /= vector.xp;
    yp /= vector.yp;
    return *this;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool operator
 */
inline bool operator==(const Vector2 &v1, const Vector2 &v2)
{
    return v1.xp == v2.xp && v1.yp == v2.yp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool operator
 */
inline bool operator!=(const Vector2 &v1, const Vector2 &v2)
{
    return v1.xp != v2.xp || v1.yp != v2.yp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector2 operator
 */
inline const Vector2 operator+(const Vector2 &v1, const Vector2 &v2)
{
    return Vector2(v1.xp + v2.xp, v1.yp + v2.yp);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector2 operator
 */
inline const Vector2 operator-(const Vector2 &v1, const Vector2 &v2)
{
    return Vector2(v1.xp - v2.xp, v1.yp - v2.yp);
}

/**
 * @brief
 *
 * @param factor
 * @param vector
 * @return const Vector2 operator
 */
inline const Vector2 operator*(double factor, const Vector2 &vector)
{
    return Vector2(vector.xp * factor, vector.yp * factor);
}

/**
 * @brief
 *
 * @param vector
 * @param factor
 * @return const Vector2 operator
 */
inline const Vector2 operator*(const Vector2 &vector, double factor)
{
    return Vector2(vector.xp * factor, vector.yp * factor);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector2 operator
 */
inline const Vector2 operator*(const Vector2 &v1, const Vector2 &v2)
{
    return Vector2(v1.xp * v2.xp, v1.yp * v2.yp);
}

/**
 * @brief
 *
 * @param vector
 * @return const Vector2 operator
 */
inline const Vector2 operator-(const Vector2 &vector)
{
    return Vector2(-vector.xp, -vector.yp);
}

/**
 * @brief
 *
 * @param vector
 * @param divisor
 * @return const Vector2 operator
 */
inline const Vector2 operator/(const Vector2 &vector, double divisor)
{
    return Vector2(vector.xp / divisor, vector.yp / divisor);
}

/**
 * @brief
 *
 * @param vector
 * @param divisor
 * @return const Vector2 operator
 */
inline const Vector2 operator/(const Vector2 &vector, const Vector2 &divisor)
{
    return Vector2(vector.xp / divisor.xp, vector.yp / divisor.yp);
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector2::length() const
{
    // Need some extra precision if the length is very small.
    double len = xp * xp + yp * yp;
    return std::sqrt(len);
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector2::lengthSquared() const
{
    return xp * xp + yp * yp;
}

/**
 * @brief
 *
 * @return Vector2
 */
inline Vector2 Vector2::normalized() const
{
    // Need some extra precision if the length is very small.
    double len = xp * xp + yp * yp;
    if (qFuzzyIsNull(len - 1.0)) {
        return *this;
    } else if (!qFuzzyIsNull(len)) {
        double sqrtLen = std::sqrt(len);
        return Vector2(xp / sqrtLen, yp / sqrtLen);
    } else {
        return Vector2();
    }
}

/**
 * @brief
 *
 * @return Vector2
 */
inline Vector2 &Vector2::normalize()
{
    // Need some extra precision if the length is very small.
    double len = xp * xp + yp * yp;
    if (qFuzzyIsNull(len - 1.0) || qFuzzyIsNull(len))
        return *this;

    len = std::sqrt(len);

    xp /= len;
    yp /= len;

    return *this;
}

/**
 * @brief
 *
 * @param point
 * @return double
 */
inline double Vector2::distanceToPoint(const Vector2& point) const
{
    return (*this - point).length();
}

/**
 * @brief
 *
 * @param point
 * @param direction
 * @return double
 */
inline double Vector2::distanceToLine(const Vector2& point, const Vector2& direction) const
{
    if (direction.isNull())
        return (*this - point).length();
    Vector2 p = point + dotProduct(*this - point, direction) * direction;
    return (*this - p).length();
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return double
 */
inline double Vector2::dotProduct(const Vector2& v1, const Vector2& v2)
{
    return v1.xp * v2.xp + v1.yp * v2.yp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return double
 */
inline double Vector2::dot(const Vector2& v1, const Vector2& v2)
{
    return v1.xp * v2.xp + v1.yp * v2.yp;
}

/**
 * @brief
 *
 * @param start
 * @param end
 * @param t
 * @return Vector2
 */
inline Vector2 Vector2::lerp(const Vector2 &start, const Vector2 &end, double t)
{
    return start * (1.0 - t) + end * t;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool
 */
inline bool qFuzzyCompare(const Vector2& v1, const Vector2& v2)
{
    return qFuzzyCompare(v1.xp, v2.xp) && qFuzzyCompare(v1.yp, v2.yp);
}

/**
 * @brief
 *
 * @return Vector2::operator
 */
inline Vector2::operator Cartesian2() const
{
    return Cartesian2(xp, yp);
}

/**
 * @brief
 *
 * @return Vector2::operator
 */
inline Vector2::operator QVector2D() const
{
    return QVector2D(xp, yp);
}

/**
 * @brief
 *
 * @return Vector2::operator
 */
inline Vector2::operator QVariant() const
{
    return QVariant::fromValue<Vector2>(*this);
}

#endif
