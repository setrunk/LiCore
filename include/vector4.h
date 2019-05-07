#ifndef VECTOR4_H
#define VECTOR4_H

#include "licore_global.h"
#include "cartesian4.h"
#include "vector2.h"
#include "vector3.h"

class Matrix4;

/**
 * @brief
 * 四维坐标点，在js/qml中使用Li.vector4(x,y,z,w)函数构造。
 */
class LICORE_EXPORT Vector4
{
public:
    /**
     * @brief
     *
     */
    Vector4();
    /**
     * @brief
     *
     * @param Qt::Initialization
     */
    explicit Vector4(Qt::Initialization) {}
    /**
     * @brief
     *
     * @param xpos
     * @param ypos
     * @param zpos
     * @param wpos
     */
    Vector4(double xpos, double ypos, double zpos, double wpos);
    /**
     * @brief
     *
     * @param vector
     */
    Vector4(const Vector2& vector);
    /**
     * @brief
     *
     * @param vector
     * @param zpos
     * @param wpos
     */
    Vector4(const Vector2& vector, double zpos, double wpos);
    /**
     * @brief
     *
     * @param vector
     */
    Vector4(const Vector3& vector);
    /**
     * @brief
     *
     * @param vector
     * @param wpos
     */
    Vector4(const Vector3& vector, double wpos);
    /**
     * @brief
     *
     * @param cartesian
     */
    Vector4(const Cartesian4& cartesian);
    /**
     * @brief
     *
     * @param vector
     */
    Vector4(const QVector4D& vector);

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
     * @return double
     */
    double w() const;

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
     * @param w
     */
    void setW(double w);

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
     * @return Vector4
     */
    Vector4 normalized() const;
    /**
     * @brief
     *
     * @return Vector4
     */
    Vector4 &normalize();

    /**
     * @brief
     *
     * @param vector
     * @return Vector4 &operator
     */
    Vector4 &operator+=(const Vector4 &vector);
    /**
     * @brief
     *
     * @param vector
     * @return Vector4 &operator
     */
    Vector4 &operator-=(const Vector4 &vector);
    /**
     * @brief
     *
     * @param factor
     * @return Vector4 &operator
     */
    Vector4 &operator*=(double factor);
    /**
     * @brief
     *
     * @param vector
     * @return Vector4 &operator
     */
    Vector4 &operator*=(const Vector4 &vector);
    /**
     * @brief
     *
     * @param divisor
     * @return Vector4 &operator
     */
    Vector4 &operator/=(double divisor);
    /**
     * @brief
     *
     * @param vector
     * @return Vector4 &operator
     */
    Vector4 &operator/=(const Vector4 &vector);

    /**
     * @brief
     *
     * @return Vector2
     */
    Vector2 toVector2D() const;
    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 toVector3D() const;

    /**
     * @brief
     *
     * @return operator
     */
    operator Cartesian4() const;
    /**
     * @brief
     *
     * @return operator
     */
    operator QVector4D() const;
    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const;

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return double
     */
    static double dot(const Vector4& v1, const Vector4& v2); //In Qt 6 convert to inline and constexpr
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return double
     */
    static double dotProduct(const Vector4& v1, const Vector4& v2); //In Qt 6 convert to inline and constexpr
    /**
     * @brief
     *
     * @param start
     * @param end
     * @param t
     * @return Vector4
     */
    static Vector4 lerp(const Vector4 &start, const Vector4 &end, double t);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Vector4
     */
    static Vector4 min(const Vector4 &v1, const Vector4 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Vector4
     */
    static Vector4 max(const Vector4 &v1, const Vector4 &v2);

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool operator
     */
    friend inline bool operator==(const Vector4 &v1, const Vector4 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool operator
     */
    friend inline bool operator!=(const Vector4 &v1, const Vector4 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector4 operator
     */
    friend inline const Vector4 operator+(const Vector4 &v1, const Vector4 &v2);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector4 operator
     */
    friend inline const Vector4 operator-(const Vector4 &v1, const Vector4 &v2);
    /**
     * @brief
     *
     * @param factor
     * @param vector
     * @return const Vector4 operator
     */
    friend inline const Vector4 operator*(double factor, const Vector4 &vector);
    /**
     * @brief
     *
     * @param vector
     * @param factor
     * @return const Vector4 operator
     */
    friend inline const Vector4 operator*(const Vector4 &vector, double factor);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return const Vector4 operator
     */
    friend inline const Vector4 operator*(const Vector4 &v1, const Vector4& v2);
    /**
     * @brief
     *
     * @param vector
     * @return const Vector4 operator
     */
    friend inline const Vector4 operator-(const Vector4 &vector);
    /**
     * @brief
     *
     * @param vector
     * @param divisor
     * @return const Vector4 operator
     */
    friend inline const Vector4 operator/(const Vector4 &vector, double divisor);
    /**
     * @brief
     *
     * @param vector
     * @param divisor
     * @return const Vector4 operator
     */
    friend inline const Vector4 operator/(const Vector4 &vector, const Vector4 &divisor);
    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return bool
     */
    friend inline bool qFuzzyCompare(const Vector4& v1, const Vector4& v2);

private:
    double xp, yp, zp, wp; /**< TODO: describe */

    friend class Vector2;
    friend class Vector3;
    /**
     * @brief
     *
     * @param vector
     * @param matrix
     * @return Vector4 operator
     */
    friend Vector4 operator*(const Vector4& vector, const Matrix4& matrix);
    /**
     * @brief
     *
     * @param matrix
     * @param vector
     * @return Vector4 operator
     */
    friend Vector4 operator*(const Matrix4& matrix, const Vector4& vector);
};

Q_DECLARE_METATYPE(Vector4)
Q_DECLARE_TYPEINFO(Vector4, Q_PRIMITIVE_TYPE);

/**
 * @brief
 *
 */
inline Vector4::Vector4() : xp(0.0), yp(0.0), zp(0.0), wp(0.0) {}

/**
 * @brief
 *
 * @param xpos
 * @param ypos
 * @param zpos
 * @param wpos
 */
inline Vector4::Vector4(double xpos, double ypos, double zpos, double wpos) : xp(xpos), yp(ypos), zp(zpos), wp(wpos) {}

/**
 * @brief
 *
 * @param vector
 */
inline Vector4::Vector4(const QVector4D &vector) : xp(vector.x()), yp(vector.y()), zp(vector.z()), wp(vector.w()) {}

/**
 * @brief
 *
 * @param vector
 */
inline Vector4::Vector4(const Vector2& vector)
{
    xp = vector.xp;
    yp = vector.yp;
    zp = 0.0;
    wp = 0.0;
}

/**
 * @brief
 *
 * @param vector
 * @param zpos
 * @param wpos
 */
inline Vector4::Vector4(const Vector2& vector, double zpos, double wpos)
{
    xp = vector.xp;
    yp = vector.yp;
    zp = zpos;
    wp = wpos;
}

/**
 * @brief
 *
 * @param vector
 */
inline Vector4::Vector4(const Vector3& vector)
{
    xp = vector.xp;
    yp = vector.yp;
    zp = vector.zp;
    wp = 0.0;
}

/**
 * @brief
 *
 * @param vector
 * @param wpos
 */
inline Vector4::Vector4(const Vector3& vector, double wpos)
{
    xp = vector.xp;
    yp = vector.yp;
    zp = vector.zp;
    wp = wpos;
}

/**
 * @brief
 *
 * @param cartesian
 */
inline Vector4::Vector4(const Cartesian4 &cartesian)
{
    xp = cartesian.x;
    yp = cartesian.y;
    zp = cartesian.z;
    wp = cartesian.w;
}

/**
 * @brief
 *
 * @return bool
 */
inline bool Vector4::isNull() const
{
    return qIsNull(xp) && qIsNull(yp) && qIsNull(zp) && qIsNull(wp);
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector4::x() const { return xp; }
/**
 * @brief
 *
 * @return double
 */
inline double Vector4::y() const { return yp; }
/**
 * @brief
 *
 * @return double
 */
inline double Vector4::z() const { return zp; }
/**
 * @brief
 *
 * @return double
 */
inline double Vector4::w() const { return wp; }

/**
 * @brief
 *
 * @param aX
 */
inline void Vector4::setX(double aX) { xp = aX; }
/**
 * @brief
 *
 * @param aY
 */
inline void Vector4::setY(double aY) { yp = aY; }
/**
 * @brief
 *
 * @param aZ
 */
inline void Vector4::setZ(double aZ) { zp = aZ; }
/**
 * @brief
 *
 * @param aW
 */
inline void Vector4::setW(double aW) { wp = aW; }

/**
 * @brief
 *
 * @param i
 * @return double &Vector4::operator
 */
inline double &Vector4::operator[](int i)
{
    Q_ASSERT(uint(i) < 4u);
    return *(&xp + i);
}

/**
 * @brief
 *
 * @param i
 * @return double Vector4::operator
 */
inline double Vector4::operator[](int i) const
{
    Q_ASSERT(uint(i) < 4u);
    return *(&xp + i);
}

/**
 * @brief
 *
 * @param vector
 * @return Vector4 &Vector4::operator
 */
inline Vector4 &Vector4::operator+=(const Vector4 &vector)
{
    xp += vector.xp;
    yp += vector.yp;
    zp += vector.zp;
    wp += vector.wp;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector4 &Vector4::operator
 */
inline Vector4 &Vector4::operator-=(const Vector4 &vector)
{
    xp -= vector.xp;
    yp -= vector.yp;
    zp -= vector.zp;
    wp -= vector.wp;
    return *this;
}

/**
 * @brief
 *
 * @param factor
 * @return Vector4 &Vector4::operator
 */
inline Vector4 &Vector4::operator*=(double factor)
{
    xp *= factor;
    yp *= factor;
    zp *= factor;
    wp *= factor;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector4 &Vector4::operator
 */
inline Vector4 &Vector4::operator*=(const Vector4 &vector)
{
    xp *= vector.xp;
    yp *= vector.yp;
    zp *= vector.zp;
    wp *= vector.wp;
    return *this;
}

/**
 * @brief
 *
 * @param divisor
 * @return Vector4 &Vector4::operator
 */
inline Vector4 &Vector4::operator/=(double divisor)
{
    xp /= divisor;
    yp /= divisor;
    zp /= divisor;
    wp /= divisor;
    return *this;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector4 &Vector4::operator
 */
inline Vector4 &Vector4::operator/=(const Vector4 &vector)
{
    xp /= vector.xp;
    yp /= vector.yp;
    zp /= vector.zp;
    wp /= vector.wp;
    return *this;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool operator
 */
inline bool operator==(const Vector4 &v1, const Vector4 &v2)
{
    return v1.xp == v2.xp && v1.yp == v2.yp && v1.zp == v2.zp && v1.wp == v2.wp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool operator
 */
inline bool operator!=(const Vector4 &v1, const Vector4 &v2)
{
    return v1.xp != v2.xp || v1.yp != v2.yp || v1.zp != v2.zp || v1.wp != v2.wp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector4 operator
 */
inline const Vector4 operator+(const Vector4 &v1, const Vector4 &v2)
{
    return Vector4(v1.xp + v2.xp, v1.yp + v2.yp, v1.zp + v2.zp, v1.wp + v2.wp);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector4 operator
 */
inline const Vector4 operator-(const Vector4 &v1, const Vector4 &v2)
{
    return Vector4(v1.xp - v2.xp, v1.yp - v2.yp, v1.zp - v2.zp, v1.wp - v2.wp);
}

/**
 * @brief
 *
 * @param factor
 * @param vector
 * @return const Vector4 operator
 */
inline const Vector4 operator*(double factor, const Vector4 &vector)
{
    return Vector4(vector.xp * factor, vector.yp * factor, vector.zp * factor, vector.wp * factor);
}

/**
 * @brief
 *
 * @param vector
 * @param factor
 * @return const Vector4 operator
 */
inline const Vector4 operator*(const Vector4 &vector, double factor)
{
    return Vector4(vector.xp * factor, vector.yp * factor, vector.zp * factor, vector.wp * factor);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return const Vector4 operator
 */
inline const Vector4 operator*(const Vector4 &v1, const Vector4& v2)
{
    return Vector4(v1.xp * v2.xp, v1.yp * v2.yp, v1.zp * v2.zp, v1.wp * v2.wp);
}

/**
 * @brief
 *
 * @param vector
 * @return const Vector4 operator
 */
inline const Vector4 operator-(const Vector4 &vector)
{
    return Vector4(-vector.xp, -vector.yp, -vector.zp, -vector.wp);
}

/**
 * @brief
 *
 * @param vector
 * @param divisor
 * @return const Vector4 operator
 */
inline const Vector4 operator/(const Vector4 &vector, double divisor)
{
    return Vector4(vector.xp / divisor, vector.yp / divisor, vector.zp / divisor, vector.wp / divisor);
}

/**
 * @brief
 *
 * @param vector
 * @param divisor
 * @return const Vector4 operator
 */
inline const Vector4 operator/(const Vector4 &vector, const Vector4 &divisor)
{
    return Vector4(vector.xp / divisor.xp, vector.yp / divisor.yp, vector.zp / divisor.zp, vector.wp / divisor.wp);
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return bool
 */
inline bool qFuzzyCompare(const Vector4& v1, const Vector4& v2)
{
    return qFuzzyCompare(v1.xp, v2.xp) &&
           qFuzzyCompare(v1.yp, v2.yp) &&
           qFuzzyCompare(v1.zp, v2.zp) &&
           qFuzzyCompare(v1.wp, v2.wp);
}

/**
 * @brief
 *
 * @return Vector4::operator
 */
inline Vector4::operator Cartesian4() const
{
    return Cartesian4(xp, yp, zp, wp);
}

/**
 * @brief
 *
 * @return Vector4::operator
 */
inline Vector4::operator QVector4D() const
{
    return QVector4D(xp, yp, zp, wp);
}

/**
 * @brief
 *
 * @return Vector4::operator
 */
inline Vector4::operator QVariant() const
{
    return QVariant::fromValue<Vector4>(*this);
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector4::length() const
{
    // Need some extra precision if the length is very small.
    double len = xp * xp + yp * yp + zp * zp + wp * wp;
    return std::sqrt(len);
}

/**
 * @brief
 *
 * @return double
 */
inline double Vector4::lengthSquared() const
{
    return xp * xp + yp * yp + zp * zp + wp * wp;
}

/**
 * @brief
 *
 * @return Vector4
 */
inline Vector4 Vector4::normalized() const
{
    // Need some extra precision if the length is very small.
    double len = xp * xp + yp * yp + zp * zp + wp * wp;
    if (qFuzzyIsNull(len - 1.0)) {
        return *this;
    } else if (!qFuzzyIsNull(len)) {
        double sqrtLen = 1.0 / std::sqrt(len);
        return Vector4(xp*sqrtLen, yp*sqrtLen, zp*sqrtLen, wp*sqrtLen);
    } else {
        return Vector4();
    }
}

/**
 * @brief
 *
 * @return Vector4
 */
inline Vector4 &Vector4::normalize()
{
    // Need some extra precision if the length is very small.
    double len = xp * xp + yp * yp + zp * zp + wp * wp;
    if (qFuzzyIsNull(len - 1.0) || qFuzzyIsNull(len))
        return *this;

    len = 1.0 / std::sqrt(len);

    xp *= len;
    yp *= len;
    zp *= len;
    wp *= len;

    return *this;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return double
 */
inline double Vector4::dot(const Vector4& v1, const Vector4& v2)
{
    return v1.xp * v2.xp + v1.yp * v2.yp + v1.zp * v2.zp + v1.wp * v2.wp;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return double
 */
inline double Vector4::dotProduct(const Vector4& v1, const Vector4& v2)
{
    return v1.xp * v2.xp + v1.yp * v2.yp + v1.zp * v2.zp + v1.wp * v2.wp;
}

/**
 * @brief
 *
 * @param start
 * @param end
 * @param t
 * @return Vector4
 */
inline Vector4 Vector4::lerp(const Vector4 &start, const Vector4 &end, double t)
{
    return start * (1.0 - t) + end * t;
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return Vector4
 */
inline Vector4 Vector4::min(const Vector4 &v1, const Vector4 &v2)
{
    return Vector4(std::min(v1.xp, v2.xp), std::min(v1.yp, v2.yp), std::min(v1.zp, v2.zp), std::min(v1.wp, v2.wp));
}

/**
 * @brief
 *
 * @param v1
 * @param v2
 * @return Vector4
 */
inline Vector4 Vector4::max(const Vector4 &v1, const Vector4 &v2)
{
    return Vector4(std::max(v1.xp, v2.xp), std::max(v1.yp, v2.yp), std::max(v1.zp, v2.zp), std::max(v1.wp, v2.wp));
}

/**
 * @brief
 *
 * @return Vector2
 */
inline Vector2 Vector4::toVector2D() const
{
    return Vector2(xp, yp);
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Vector4::toVector3D() const
{
    return Vector3(xp, yp, zp);
}

#endif
