#ifndef VECTOR3_H
#define VECTOR3_H

#include "licore_global.h"
#include "cartesian3.h"
#include "vector2.h"
#include <QJSValue>

class Matrix4;
class Vector2;
class Vector4;

/**
 * @brief
 * 三维空间的点或矢量，在js/qml中使用Li.vector3(x,y,z)函数构造。
 */
class LICORE_EXPORT Vector3
{
public:
    /**
     * @brief
     *
     */
    Vector3();
    /**
     * @brief
     *
     * @param Qt::Initialization
     */
    explicit Vector3(Qt::Initialization) {}
    /**
     * @brief
     *
     * @param xpos
     * @param ypos
     * @param zpos
     */
    Vector3(double xpos, double ypos, double zpos) : xp(xpos), yp(ypos), zp(zpos) {}
    /**
     * @brief
     *
     * @param vector
     */
    Vector3(const Vector2& vector);
    /**
     * @brief
     *
     * @param vector
     * @param zpos
     */
    Vector3(const Vector2& vector, double zpos);
    /**
     * @brief
     *
     * @param vector
     */
    Vector3(const Vector4& vector);
    /**
     * @brief
     *
     * @param cartesian
     */
    Vector3(const Cartesian3& cartesian);
    /**
     * @brief
     *
     * @param vector
     */
    Vector3(const QVector3D& vector);
    /**
     * @brief
     *
     * @param value
     */
    Vector3(const QJSValue &value);

    static Vector3 xAxis; /**< TODO: describe */
    static Vector3 yAxis; /**< TODO: describe */
    static Vector3 zAxis; /**< TODO: describe */

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
     * @return double
     */
    double z() const;

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
     * @param z
     */
    void setZ(double z);

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
    double maximumComponent() const;

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
    double lengthSquared() const;

    /**
     * @brief
     *
     * @return double
     */
    double magnitude() const;
    /**
     * @brief
     *
     * @return double
     */
    double magnitudeSquared() const;

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 normalized() const;
    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 &normalize();

    /**
     * @brief
     *
     * @param vector
     * @return Vector3 &operator
     */
    Vector3 &operator+=(const Vector3 &vector);
    /**
     * @brief
     *
     * @param vector
     * @return Vector3 &operator
     */
    Vector3 &operator-=(const Vector3 &vector);
    /**
     * @brief
     *
     * @param factor
     * @return Vector3 &operator
     */
    Vector3 &operator*=(double factor);
    /**
     * @brief
     *
     * @param vector
     * @return Vector3 &operator
     */
    Vector3 &operator*=(const Vector3& vector);
    /**
     * @brief
     *
     * @param divisor
     * @return Vector3 &operator
     */
    Vector3 &operator/=(double divisor);
    /**
     * @brief
     *
     * @param vector
     * @return Vector3 &operator
     */
    Vector3 &operator/=(const Vector3 &vector);
    /**
     * @brief
     *
     * @param vector
     * @return bool operator
     */
    bool operator<(const Vector3 &vector) const;
    /**
     * @brief
     *
     * @param vecotr
     * @return bool operator >
     */
    bool operator>(const Vector3 &vecotr) const;

    /**
     * @brief
     *
     * @param v2
     * @return double
     */
    double dotProduct(const Vector3& v2) const;
    /**
     * @brief
     *
     * @param v2
     * @return Vector3
     */
    Vector3 crossProduct(const Vector3& v2) const;

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return double
     */
    static double dot(const Vector3& v1, const Vector3& v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return double
     */
    static double dotProduct(const Vector3& v1, const Vector3& v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Vector3
     */
    static Vector3 cross(const Vector3& v1, const Vector3& v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Vector3
     */
    static Vector3 crossProduct(const Vector3& v1, const Vector3& v2);

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Vector3
     */
    static Vector3 min(const Vector3 &v1, const Vector3 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Vector3
     */
    static Vector3 max(const Vector3 &v1, const Vector3 &v2);

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Vector3
     */
    static Vector3 normal(const Vector3& v1, const Vector3& v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @param v3
     * @return Vector3
     */
    static Vector3 normal(const Vector3& v1, const Vector3& v2, const Vector3& v3);

    /**
     * @brief
     *
     * @param start
     * @param end
     * @param t
     * @return Vector3
     */
    static Vector3 lerp(const Vector3 &start, const Vector3 &end, double t);

    /**
     * @brief
     *
     * @param modelView
     * @param projection
     * @param viewport
     * @return Vector3
     */
    Vector3 project(const Matrix4 &modelView, const Matrix4 &projection, const QRect &viewport) const;
    /**
     * @brief
     *
     * @param modelView
     * @param projection
     * @param viewport
     * @return Vector3
     */
    Vector3 unproject(const Matrix4 &modelView, const Matrix4 &projection, const QRect &viewport) const;

    /**
     * @brief
     *
     * @param point
     * @return double
     */
    double distanceToPoint(const Vector3& point) const;
    /**
     * @brief
     *
     * @param plane
     * @param normal
     * @return double
     */
    double distanceToPlane(const Vector3& plane, const Vector3& normal) const;
    /**
     * @brief
     *
     * @param plane1
     * @param plane2
     * @param plane3
     * @return double
     */
    double distanceToPlane(const Vector3& plane1, const Vector3& plane2, const Vector3& plane3) const;
    /**
     * @brief
     *
     * @param point
     * @param direction
     * @return double
     */
    double distanceToLine(const Vector3& point, const Vector3& direction) const;

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool operator
     */
    friend inline bool operator==(const Vector3 &v1, const Vector3 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool operator
     */
    friend inline bool operator!=(const Vector3 &v1, const Vector3 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector3 operator
     */
    friend inline const Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector3 operator
     */
    friend inline const Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
    /**
     * @brief
     *
     * @param factor
     * @param vector
     * @return const Vector3 operator
     */
    friend inline const Vector3 operator*(double factor, const Vector3 &vector);
    /**
     * @brief
     *
     * @param vector
     * @param factor
     * @return const Vector3 operator
     */
    friend inline const Vector3 operator*(const Vector3 &vector, double factor);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector3 operator
     */
    friend const Vector3 operator*(const Vector3 &v1, const Vector3& v2);
    /**
     * @brief
     *
     * @param vector
     * @return const Vector3 operator
     */
    friend inline const Vector3 operator-(const Vector3 &vector);
    /**
     * @brief
     *
     * @param vector
     * @param divisor
     * @return const Vector3 operator
     */
    friend inline const Vector3 operator/(const Vector3 &vector, double divisor);
    /**
     * @brief
     *
     * @param vector
     * @param divisor
     * @return const Vector3 operator
     */
    friend inline const Vector3 operator/(const Vector3 &vector, const Vector3 &divisor);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool
     */
    friend inline bool qFuzzyCompare(const Vector3& v1, const Vector3& v2);

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 floor() const;
    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 ceil() const;

    /**
     * @brief
     *
     * @return Vector2
     */
    Vector2 toVector2() const;
    /**
     * @brief
     *
     * @return Vector4
     */
    Vector4 toVector4() const;

    /**
     * @brief
     *
     * @return operator
     */
    operator Cartesian3() const;
    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const;

    /**
     * @brief
     *
     * @param value
     * @return Vector3
     */
    static Vector3 fromJSValue(const QJSValue &value);

private:
    double xp, yp, zp; /**< TODO: describe */

    friend class Vector2;
    friend class Vector4;
    /**
     * @brief
     *
     * @param vector
     * @param matrix
     * @return Vector3 operator
     */
    friend Vector3 operator*(const Vector3& vector, const Matrix4& matrix);
    /**
     * @brief
     *
     * @param matrix
     * @param vector
     * @return Vector3 operator
     */
    friend Vector3 operator*(const Matrix4& matrix, const Vector3& vector);
};

Q_DECLARE_METATYPE(Vector3)
Q_DECLARE_TYPEINFO(Vector3, Q_PRIMITIVE_TYPE);

/**
 * @brief
 *
 */
inline Vector3::Vector3() : xp(0.0), yp(0.0), zp(0.0) {}

/**
 * @brief
 *
 * @return bool
 */
inline bool Vector3::isNull() const
{
//    return qIsNull(xp) && qIsNull(yp) && qIsNull(zp);
    return xp == 0.0 && yp == 0.0 && zp == 0.0;
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector3::x() const { return xp; }
/**
 * @brief
 *
 * @return double
 */
inline double Vector3::y() const { return yp; }
/**
 * @brief
 *
 * @return double
 */
inline double Vector3::z() const { return zp; }

/**
 * @brief
 *
 * @param aX
 */
inline void Vector3::setX(double aX) { xp = aX; }
/**
 * @brief
 *
 * @param aY
 */
inline void Vector3::setY(double aY) { yp = aY; }
/**
 * @brief
 *
 * @param aZ
 */
inline void Vector3::setZ(double aZ) { zp = aZ; }

/**
 * @brief
 *
 * @return double
 */
inline double Vector3::maximumComponent() const { return std::max(std::max(xp, yp), zp); }

/**
 * @brief
 *
 * @param i
 * @return double &Vector3::operator
 */
inline double &Vector3::operator[](int i)
{
    Q_ASSERT(uint(i) < 3u);
    return *(&xp + i);
}

/**
 * @brief
 *
 * @param i
 * @return double Vector3::operator
 */
inline double Vector3::operator[](int i) const
{
    Q_ASSERT(uint(i) < 3u);
    return *(&xp + i);
}

/**
 * @brief
 *
 * @param vector
 * @return Vector3 &Vector3::operator
 */
inline Vector3 &Vector3::operator+=(const Vector3 &vector)
{
    xp += vector.xp;
    yp += vector.yp;
    zp += vector.zp;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector3 &Vector3::operator
 */
inline Vector3 &Vector3::operator-=(const Vector3 &vector)
{
    xp -= vector.xp;
    yp -= vector.yp;
    zp -= vector.zp;
    return *this;
}

/**
 * @brief
 *
 * @param factor
 * @return Vector3 &Vector3::operator
 */
inline Vector3 &Vector3::operator*=(double factor)
{
    xp *= factor;
    yp *= factor;
    zp *= factor;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector3 &Vector3::operator
 */
inline Vector3 &Vector3::operator*=(const Vector3& vector)
{
    xp *= vector.xp;
    yp *= vector.yp;
    zp *= vector.zp;
    return *this;
}

/**
 * @brief
 *
 * @param divisor
 * @return Vector3 &Vector3::operator
 */
inline Vector3 &Vector3::operator/=(double divisor)
{
    xp /= divisor;
    yp /= divisor;
    zp /= divisor;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector3 &Vector3::operator
 */
inline Vector3 &Vector3::operator/=(const Vector3 &vector)
{
    xp /= vector.xp;
    yp /= vector.yp;
    zp /= vector.zp;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return bool Vector3::operator
 */
inline bool Vector3::operator <(const Vector3 &vector) const
{
    return xp < vector.xp && yp < vector.yp && zp < vector.zp;
}

/**
 * @brief
 *
 * @param vector
 * @return bool Vector3::operator >
 */
inline bool Vector3::operator >(const Vector3 &vector) const
{
    return xp > vector.xp && yp > vector.yp && zp > vector.zp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return Vector3
 */
inline Vector3 Vector3::min(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(std::min(v1.xp, v2.xp), std::min(v1.yp, v2.yp), std::min(v1.zp, v2.zp));
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return Vector3
 */
inline Vector3 Vector3::max(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(std::max(v1.xp, v2.xp), std::max(v1.yp, v2.yp), std::max(v1.zp, v2.zp));
}

/**
 * @brief
 *
 * @param start
 * @param end
 * @param t
 * @return Vector3
 */
inline Vector3 Vector3::lerp(const Vector3 &start, const Vector3 &end, double t)
{
    return start * (1.0 - t) + end * t;
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Vector3::floor() const
{
    return Vector3(std::floor(xp), std::floor(yp), std::floor(zp));
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Vector3::ceil() const
{
    return Vector3(std::ceil(xp), std::ceil(yp), std::ceil(zp));
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool operator
 */
inline bool operator==(const Vector3 &v1, const Vector3 &v2)
{
    return v1.xp == v2.xp && v1.yp == v2.yp && v1.zp == v2.zp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool operator
 */
inline bool operator!=(const Vector3 &v1, const Vector3 &v2)
{
    return v1.xp != v2.xp || v1.yp != v2.yp || v1.zp != v2.zp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector3 operator
 */
inline const Vector3 operator+(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(v1.xp + v2.xp, v1.yp + v2.yp, v1.zp + v2.zp);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector3 operator
 */
inline const Vector3 operator-(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(v1.xp - v2.xp, v1.yp - v2.yp, v1.zp - v2.zp);
}

/**
 * @brief
 *
 * @param factor
 * @param vector
 * @return const Vector3 operator
 */
inline const Vector3 operator*(double factor, const Vector3 &vector)
{
    return Vector3(vector.xp * factor, vector.yp * factor, vector.zp * factor);
}

/**
 * @brief
 *
 * @param vector
 * @param factor
 * @return const Vector3 operator
 */
inline const Vector3 operator*(const Vector3 &vector, double factor)
{
    return Vector3(vector.xp * factor, vector.yp * factor, vector.zp * factor);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector3 operator
 */
inline const Vector3 operator*(const Vector3 &v1, const Vector3& v2)
{
    return Vector3(v1.xp * v2.xp, v1.yp * v2.yp, v1.zp * v2.zp);
}

/**
 * @brief
 *
 * @param vector
 * @return const Vector3 operator
 */
inline const Vector3 operator-(const Vector3 &vector)
{
    return Vector3(-vector.xp, -vector.yp, -vector.zp);
}

/**
 * @brief
 *
 * @param vector
 * @param divisor
 * @return const Vector3 operator
 */
inline const Vector3 operator/(const Vector3 &vector, double divisor)
{
    return Vector3(vector.xp / divisor, vector.yp / divisor, vector.zp / divisor);
}

/**
 * @brief
 *
 * @param vector
 * @param divisor
 * @return const Vector3 operator
 */
inline const Vector3 operator/(const Vector3 &vector, const Vector3 &divisor)
{
    return Vector3(vector.xp / divisor.xp, vector.yp / divisor.yp, vector.zp / divisor.zp);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool
 */
inline bool qFuzzyCompare(const Vector3& v1, const Vector3& v2)
{
    return qFuzzyCompare(v1.xp, v2.xp) &&
           qFuzzyCompare(v1.yp, v2.yp) &&
           qFuzzyCompare(v1.zp, v2.zp);
}

/**
 * @brief
 *
 * @return Vector3::operator
 */
inline Vector3::operator Cartesian3() const
{
    return Cartesian3(xp, yp, zp);
}

/**
 * @brief
 *
 * @return Vector3::operator
 */
inline Vector3::operator QVariant() const
{
    return QVariant::fromValue<Vector3>(*this);
}

/**
 * @brief
 *
 * @param vector
 */
inline Vector3::Vector3(const Vector2& vector)
{
    xp = vector.xp;
    yp = vector.yp;
    zp = 0.0;
}

/**
 * @brief
 *
 * @param vector
 * @param zpos
 */
inline Vector3::Vector3(const Vector2& vector, double zpos)
{
    xp = vector.xp;
    yp = vector.yp;
    zp = zpos;
}

/**
 * @brief
 *
 * @param cartesian
 */
inline Vector3::Vector3(const Cartesian3 &cartesian)
{
    xp = cartesian.x;
    yp = cartesian.y;
    zp = cartesian.z;
}

/**
 * @brief
 *
 * @param vector
 */
inline Vector3::Vector3(const QVector3D &vector)
{
    xp = vector.x();
    yp = vector.y();
    zp = vector.z();
}

/**
 * @brief
 *
 * @return Vector2
 */
inline Vector2 Vector3::toVector2() const
{
    return Vector2(xp, yp);
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Vector3::normalized() const
{
    // Need some extra precision if the length is very small.
    double len = xp * xp + yp * yp + zp * zp;
    if (qFuzzyIsNull(len - 1.0)) {
        return *this;
    } else if (!qFuzzyIsNull(len)) {
        double sqrtLen = std::sqrt(len);
        return Vector3(xp / sqrtLen,
                       yp / sqrtLen,
                       zp / sqrtLen);
    } else {
        return Vector3();
    }
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 &Vector3::normalize()
{
    // Need some extra precision if the length is very small.
    double len = xp * xp + yp * yp + zp * zp;
    if (qFuzzyIsNull(len - 1.0) || qFuzzyIsNull(len))
        return *this;

    len = std::sqrt(len);

    xp /= len;
    yp /= len;
    zp /= len;

    return *this;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return double
 */
inline double Vector3::dot(const Vector3 &v1, const Vector3 &v2)
{
    return v1.xp * v2.xp + v1.yp * v2.yp + v1.zp * v2.zp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return double
 */
inline double Vector3::dotProduct(const Vector3& v1, const Vector3& v2)
{
    return v1.xp * v2.xp + v1.yp * v2.yp + v1.zp * v2.zp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return Vector3
 */
inline Vector3 Vector3::cross(const Vector3 &v1, const Vector3 &v2)
{
    return Vector3(v1.yp * v2.zp - v1.zp * v2.yp,
                   v1.zp * v2.xp - v1.xp * v2.zp,
                   v1.xp * v2.yp - v1.yp * v2.xp);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return Vector3
 */
inline Vector3 Vector3::crossProduct(const Vector3& v1, const Vector3& v2)
{
    return Vector3(v1.yp * v2.zp - v1.zp * v2.yp,
                   v1.zp * v2.xp - v1.xp * v2.zp,
                   v1.xp * v2.yp - v1.yp * v2.xp);
}

/**
 * @brief
 *
 * @param v2
 * @return double
 */
inline double Vector3::dotProduct(const Vector3 &v2) const
{
    return xp * v2.xp + yp * v2.yp + zp * v2.zp;
}

/**
 * @brief
 *
 * @param v2
 * @return Vector3
 */
inline Vector3 Vector3::crossProduct(const Vector3 &v2) const
{
    return Vector3(yp * v2.zp - zp * v2.yp,
                   zp * v2.xp - xp * v2.zp,
                   xp * v2.yp - yp * v2.xp);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return Vector3
 */
inline Vector3 Vector3::normal(const Vector3& v1, const Vector3& v2)
{
    return crossProduct(v1, v2).normalized();
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @param v3
 * @return Vector3
 */
inline Vector3 Vector3::normal(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
    return crossProduct((v2 - v1), (v3 - v1)).normalized();
}

/**
 * @brief
 *
 * @param point
 * @return double
 */
inline double Vector3::distanceToPoint(const Vector3& point) const
{
    return (*this - point).length();
}

/**
 * @brief
 *
 * @param plane
 * @param normal
 * @return double
 */
inline double Vector3::distanceToPlane(const Vector3& plane, const Vector3& normal) const
{
    return dotProduct(*this - plane, normal);
}

/**
 * @brief
 *
 * @param plane1
 * @param plane2
 * @param plane3
 * @return double
 */
inline double Vector3::distanceToPlane(const Vector3& plane1, const Vector3& plane2, const Vector3& plane3) const
{
    Vector3 n = normal(plane2 - plane1, plane3 - plane1);
    return dotProduct(*this - plane1, n);
}

/**
 * @brief
 *
 * @param point
 * @param direction
 * @return double
 */
inline double Vector3::distanceToLine(const Vector3& point, const Vector3& direction) const
{
    if (direction.isNull())
        return (*this - point).length();
    Vector3 p = point + dotProduct(*this - point, direction) * direction;
    return (*this - p).length();
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector3::length() const
{
    // Need some extra precision if the length is very small.
    return std::sqrt(xp * xp + yp * yp + zp * zp);
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector3::lengthSquared() const
{
    return xp * xp + yp * yp + zp * zp;
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector3::magnitude() const
{
    // Need some extra precision if the length is very small.
    return std::sqrt(xp * xp + yp * yp + zp * zp);
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector3::magnitudeSquared() const
{
    return xp * xp + yp * yp + zp * zp;
}

#endif
