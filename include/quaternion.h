#ifndef QUATERNION_H
#define QUATERNION_H

#include "licore_global.h"
#include "vector4.h"
#include "matrix3.h"

/**
 * @brief
 * 四元组，表达一个物体在三维空间中绕任意周旋转任意角度。
 * 有关函数中涉及角度的参数都是以度（degree）为单位。
 * 使用四元组表达旋转最大的优势是两个四元组可以进行插值。
 */
class LICORE_EXPORT Quaternion
{
public:
    /**
     * @brief
     *
     */
    Quaternion();
    /**
     * @brief
     *
     * @param Qt::Initialization
     */
    explicit Quaternion(Qt::Initialization) {}
    /**
     * @brief
     *
     * @param scalar
     * @param xpos
     * @param ypos
     * @param zpos
     */
    Quaternion(double scalar, double xpos, double ypos, double zpos);
    /**
     * @brief
     *
     * @param scalar
     * @param vector
     */
    Quaternion(double scalar, const Vector3& vector);

    Quaternion(const QQuaternion &q);

    /**
     * @brief
     *
     * @param vector
     */
    explicit Quaternion(const Vector4& vector);

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const;
    /**
     * @brief
     *
     * @return bool
     */
    bool isIdentity() const;

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 vector() const;
    /**
     * @brief
     *
     * @param vector
     */
    void setVector(const Vector3& vector);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param z
     */
    void setVector(double x, double y, double z);

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
    double scalar() const;

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
     * @param scalar
     */
    void setScalar(double scalar);

    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @return double
     */
    static double dotProduct(const Quaternion &q1, const Quaternion &q2);

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
     * @return Quaternion
     */
    Quaternion normalized() const;
    /**
     * @brief
     *
     * @return Quaternion
     */
    Quaternion &normalize();

    /**
     * @brief
     *
     * @return Quaternion
     */
    inline Quaternion inverted() const;

    /**
     * @brief
     *
     * @return Quaternion
     */
    Quaternion conjugated() const;

    /**
     * @brief
     *
     * @param vector
     * @return Vector3
     */
    Vector3 rotatedVector(const Vector3& vector) const;

    /**
     * @brief
     *
     * @param quaternion
     * @return Quaternion &operator
     */
    Quaternion &operator+=(const Quaternion &quaternion);
    /**
     * @brief
     *
     * @param quaternion
     * @return Quaternion &operator
     */
    Quaternion &operator-=(const Quaternion &quaternion);
    /**
     * @brief
     *
     * @param factor
     * @return Quaternion &operator
     */
    Quaternion &operator*=(double factor);
    /**
     * @brief
     *
     * @param quaternion
     * @return Quaternion &operator
     */
    Quaternion &operator*=(const Quaternion &quaternion);
    /**
     * @brief
     *
     * @param divisor
     * @return Quaternion &operator
     */
    Quaternion &operator/=(double divisor);

    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @return bool operator
     */
    friend inline bool operator==(const Quaternion &q1, const Quaternion &q2);
    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @return bool operator
     */
    friend inline bool operator!=(const Quaternion &q1, const Quaternion &q2);
    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @return const Quaternion operator
     */
    friend inline const Quaternion operator+(const Quaternion &q1, const Quaternion &q2);
    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @return const Quaternion operator
     */
    friend inline const Quaternion operator-(const Quaternion &q1, const Quaternion &q2);
    /**
     * @brief
     *
     * @param factor
     * @param quaternion
     * @return const Quaternion operator
     */
    friend inline const Quaternion operator*(double factor, const Quaternion &quaternion);
    /**
     * @brief
     *
     * @param quaternion
     * @param factor
     * @return const Quaternion operator
     */
    friend inline const Quaternion operator*(const Quaternion &quaternion, double factor);
    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @return const Quaternion operator
     */
    friend inline const Quaternion operator*(const Quaternion &q1, const Quaternion& q2);
    /**
     * @brief
     *
     * @param quaternion
     * @return const Quaternion operator
     */
    friend inline const Quaternion operator-(const Quaternion &quaternion);
    /**
     * @brief
     *
     * @param quaternion
     * @param divisor
     * @return const Quaternion operator
     */
    friend inline const Quaternion operator/(const Quaternion &quaternion, double divisor);

    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @return bool
     */
    friend inline bool qFuzzyCompare(const Quaternion& q1, const Quaternion& q2);

    /**
     * @brief
     *
     * @return Vector4
     */
    Vector4 toVector4D() const;

    /**
     * @brief
     *
     * @param axis
     * @param angle
     */
    inline void getAxisAndAngle(Vector3 *axis, double *angle) const;
    /**
     * @brief
     *
     * @param axis
     * @param angle
     * @return Quaternion
     */
    static Quaternion fromAxisAndAngle(const Vector3& axis, double angle);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param z
     * @param angle
     */
    void getAxisAndAngle(double *x, double *y, double *z, double *angle) const;
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param z
     * @param angle
     * @return Quaternion
     */
    static Quaternion fromAxisAndAngle(double x, double y, double z, double angle);

    /**
     * @brief
     *
     * @return Vector3
     */
    inline Vector3 toEulerAngles() const;
    /**
     * @brief
     *
     * @param eulerAngles
     * @return Quaternion
     */
    static inline Quaternion fromEulerAngles(const Vector3 &eulerAngles);
    /**
     * @brief
     *
     * @param pitch
     * @param yaw
     * @param roll
     */
    void getEulerAngles(double *pitch, double *yaw, double *roll) const;
    /**
     * @brief
     *
     * @param pitch
     * @param yaw
     * @param roll
     * @return Quaternion
     */
    static Quaternion fromEulerAngles(double pitch, double yaw, double roll);

    /**
     * @brief
     *
     * @return Matrix3
     */
    Matrix3 toRotationMatrix() const;
    /**
     * @brief
     *
     * @param rot3x3
     * @return Quaternion
     */
    static Quaternion fromRotationMatrix(const Matrix3 &rot3x3);

    /**
     * @brief
     *
     * @param xAxis
     * @param yAxis
     * @param zAxis
     */
    void getAxes(Vector3 *xAxis, Vector3 *yAxis, Vector3 *zAxis) const;
    /**
     * @brief
     *
     * @param xAxis
     * @param yAxis
     * @param zAxis
     * @return Quaternion
     */
    static Quaternion fromAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);

    /**
     * @brief
     *
     * @param direction
     * @param up
     * @return Quaternion
     */
    static Quaternion fromDirection(const Vector3 &direction, const Vector3 &up);

    /**
     * @brief
     *
     * @param from
     * @param to
     * @return Quaternion
     */
    static Quaternion rotationTo(const Vector3 &from, const Vector3 &to);

    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @param t
     * @return Quaternion
     */
    static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, double t);
    /**
     * @brief
     *
     * @param q1
     * @param q2
     * @param t
     * @return Quaternion
     */
    static Quaternion nlerp(const Quaternion& q1, const Quaternion& q2, double t);

    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const;

private:
    double wp, xp, yp, zp; /**< TODO: describe */
};

Q_DECLARE_METATYPE(Quaternion)

/**
 * @brief
 *
 */
inline Quaternion::Quaternion() : wp(1.0), xp(0.0), yp(0.0), zp(0.0) {}

/**
 * @brief
 *
 * @param aScalar
 * @param xpos
 * @param ypos
 * @param zpos
 */
inline Quaternion::Quaternion(double aScalar, double xpos, double ypos, double zpos) : wp(aScalar), xp(xpos), yp(ypos), zp(zpos) {}

inline Quaternion::Quaternion(const QQuaternion &q)
    : wp(q.scalar()), xp(q.x()), yp(q.y()), zp(q.z()) {}
/**
 * @brief
 *
 * @param aVector
 */
inline Quaternion::Quaternion(const Vector4& aVector)
    : wp(aVector.w()), xp(aVector.x()), yp(aVector.y()), zp(aVector.z()) {}

/**
 * @brief
 *
 * @return Vector4
 */
inline Vector4 Quaternion::toVector4D() const
{
    return Vector4(xp, yp, zp, wp);
}

/**
 * @brief
 *
 * @return bool
 */
inline bool Quaternion::isNull() const
{
    return wp == 0.0 && xp == 0.0 && yp == 0.0 && zp == 0.0;
}

/**
 * @brief
 *
 * @return bool
 */
inline bool Quaternion::isIdentity() const
{
    return wp == 1.0 && xp == 0.0 && yp == 0.0 && zp == 0.0;
}

/**
 * @brief
 *
 * @return double
 */
inline double Quaternion::x() const { return xp; }
/**
 * @brief
 *
 * @return double
 */
inline double Quaternion::y() const { return yp; }
/**
 * @brief
 *
 * @return double
 */
inline double Quaternion::z() const { return zp; }
/**
 * @brief
 *
 * @return double
 */
inline double Quaternion::scalar() const { return wp; }

/**
 * @brief
 *
 * @param aX
 */
inline void Quaternion::setX(double aX) { xp = aX; }
/**
 * @brief
 *
 * @param aY
 */
inline void Quaternion::setY(double aY) { yp = aY; }
/**
 * @brief
 *
 * @param aZ
 */
inline void Quaternion::setZ(double aZ) { zp = aZ; }
/**
 * @brief
 *
 * @param aScalar
 */
inline void Quaternion::setScalar(double aScalar) { wp = aScalar; }

/**
 * @brief
 *
 * @param q1
 * @param q2
 * @return double
 */
inline double Quaternion::dotProduct(const Quaternion &q1, const Quaternion &q2)
{
    return q1.wp * q2.wp + q1.xp * q2.xp + q1.yp * q2.yp + q1.zp * q2.zp;
}

/**
 * @brief
 *
 * @return Quaternion
 */
inline Quaternion Quaternion::inverted() const
{
    // Need some extra precision if the length is very small.
    double len = double(wp) * double(wp) +
                 double(xp) * double(xp) +
                 double(yp) * double(yp) +
                 double(zp) * double(zp);
    if (!qFuzzyIsNull(len))
        return Quaternion(wp / len, -xp / len, -yp / len, -zp / len);
    return Quaternion(0.0, 0.0, 0.0, 0.0);
}

/**
 * @brief
 *
 * @return Quaternion
 */
inline Quaternion Quaternion::conjugated() const
{
    return Quaternion(wp, -xp, -yp, -zp);
}

/**
 * @brief
 *
 * @param quaternion
 * @return Quaternion &Quaternion::operator
 */
inline Quaternion &Quaternion::operator+=(const Quaternion &quaternion)
{
    wp += quaternion.wp;
    xp += quaternion.xp;
    yp += quaternion.yp;
    zp += quaternion.zp;
    return *this;
}

/**
 * @brief
 *
 * @param quaternion
 * @return Quaternion &Quaternion::operator
 */
inline Quaternion &Quaternion::operator-=(const Quaternion &quaternion)
{
    wp -= quaternion.wp;
    xp -= quaternion.xp;
    yp -= quaternion.yp;
    zp -= quaternion.zp;
    return *this;
}

/**
 * @brief
 *
 * @param factor
 * @return Quaternion &Quaternion::operator
 */
inline Quaternion &Quaternion::operator*=(double factor)
{
    wp *= factor;
    xp *= factor;
    yp *= factor;
    zp *= factor;
    return *this;
}

/**
 * @brief
 *
 * @param q1
 * @param q2
 * @return const Quaternion operator
 */
inline const Quaternion operator*(const Quaternion &q1, const Quaternion& q2)
{
    double yy = (q1.wp - q1.yp) * (q2.wp + q2.zp);
    double zz = (q1.wp + q1.yp) * (q2.wp - q2.zp);
    double ww = (q1.zp + q1.xp) * (q2.xp + q2.yp);
    double xx = ww + yy + zz;
    double qq = 0.5 * (xx + (q1.zp - q1.xp) * (q2.xp - q2.yp));

    double w = qq - ww + (q1.zp - q1.yp) * (q2.yp - q2.zp);
    double x = qq - xx + (q1.xp + q1.wp) * (q2.xp + q2.wp);
    double y = qq - yy + (q1.wp - q1.xp) * (q2.yp + q2.zp);
    double z = qq - zz + (q1.zp + q1.yp) * (q2.wp - q2.xp);

    return Quaternion(w, x, y, z);
}

/**
 * @brief
 *
 * @param quaternion
 * @return Quaternion &Quaternion::operator
 */
inline Quaternion &Quaternion::operator*=(const Quaternion &quaternion)
{
    *this = *this * quaternion;
    return *this;
}

/**
 * @brief
 *
 * @param divisor
 * @return Quaternion &Quaternion::operator
 */
inline Quaternion &Quaternion::operator/=(double divisor)
{
    wp /= divisor;
    xp /= divisor;
    yp /= divisor;
    zp /= divisor;
    return *this;
}

/**
 * @brief
 *
 * @param q1
 * @param q2
 * @return bool operator
 */
inline bool operator==(const Quaternion &q1, const Quaternion &q2)
{
    return q1.wp == q2.wp && q1.xp == q2.xp && q1.yp == q2.yp && q1.zp == q2.zp;
}

/**
 * @brief
 *
 * @param q1
 * @param q2
 * @return bool operator
 */
inline bool operator!=(const Quaternion &q1, const Quaternion &q2)
{
    return !operator==(q1, q2);
}

/**
 * @brief
 *
 * @param q1
 * @param q2
 * @return const Quaternion operator
 */
inline const Quaternion operator+(const Quaternion &q1, const Quaternion &q2)
{
    return Quaternion(q1.wp + q2.wp, q1.xp + q2.xp, q1.yp + q2.yp, q1.zp + q2.zp);
}

/**
 * @brief
 *
 * @param q1
 * @param q2
 * @return const Quaternion operator
 */
inline const Quaternion operator-(const Quaternion &q1, const Quaternion &q2)
{
    return Quaternion(q1.wp - q2.wp, q1.xp - q2.xp, q1.yp - q2.yp, q1.zp - q2.zp);
}

/**
 * @brief
 *
 * @param factor
 * @param quaternion
 * @return const Quaternion operator
 */
inline const Quaternion operator*(double factor, const Quaternion &quaternion)
{
    return Quaternion(quaternion.wp * factor, quaternion.xp * factor, quaternion.yp * factor, quaternion.zp * factor);
}

/**
 * @brief
 *
 * @param quaternion
 * @param factor
 * @return const Quaternion operator
 */
inline const Quaternion operator*(const Quaternion &quaternion, double factor)
{
    return Quaternion(quaternion.wp * factor, quaternion.xp * factor, quaternion.yp * factor, quaternion.zp * factor);
}

/**
 * @brief
 *
 * @param quaternion
 * @return const Quaternion operator
 */
inline const Quaternion operator-(const Quaternion &quaternion)
{
    return Quaternion(-quaternion.wp, -quaternion.xp, -quaternion.yp, -quaternion.zp);
}

/**
 * @brief
 *
 * @param quaternion
 * @param divisor
 * @return const Quaternion operator
 */
inline const Quaternion operator/(const Quaternion &quaternion, double divisor)
{
    return Quaternion(quaternion.wp / divisor, quaternion.xp / divisor, quaternion.yp / divisor, quaternion.zp / divisor);
}

/**
 * @brief
 *
 * @param q1
 * @param q2
 * @return bool
 */
inline bool qFuzzyCompare(const Quaternion& q1, const Quaternion& q2)
{
    return qFuzzyCompare(q1.wp, q2.wp) &&
           qFuzzyCompare(q1.xp, q2.xp) &&
           qFuzzyCompare(q1.yp, q2.yp) &&
           qFuzzyCompare(q1.zp, q2.zp);
}

/**
 * @brief
 *
 * @param aScalar
 * @param aVector
 */
inline Quaternion::Quaternion(double aScalar, const Vector3& aVector)
    : wp(aScalar), xp(aVector.x()), yp(aVector.y()), zp(aVector.z()) {}

/**
 * @brief
 *
 * @param aVector
 */
inline void Quaternion::setVector(const Vector3& aVector)
{
    xp = aVector.x();
    yp = aVector.y();
    zp = aVector.z();
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Quaternion::vector() const
{
    return Vector3(xp, yp, zp);
}

/**
 * @brief
 *
 * @param quaternion
 * @param vec
 * @return Vector3 operator
 */
inline Vector3 operator*(const Quaternion &quaternion, const Vector3 &vec)
{
    return quaternion.rotatedVector(vec);
}

/**
 * @brief
 *
 * @param axis
 * @param angle
 */
inline void Quaternion::getAxisAndAngle(Vector3 *axis, double *angle) const
{
    double aX, aY, aZ;
    getAxisAndAngle(&aX, &aY, &aZ, angle);
    *axis = Vector3(aX, aY, aZ);
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Quaternion::toEulerAngles() const
{
    double pitch, yaw, roll;
    getEulerAngles(&pitch, &yaw, &roll);
    return Vector3(pitch, yaw, roll);
}

/**
 * @brief
 *
 * @param eulerAngles
 * @return Quaternion
 */
inline Quaternion Quaternion::fromEulerAngles(const Vector3 &eulerAngles)
{
    return Quaternion::fromEulerAngles(eulerAngles.x(), eulerAngles.y(), eulerAngles.z());
}

/**
 * @brief
 *
 * @param aX
 * @param aY
 * @param aZ
 */
inline void Quaternion::setVector(double aX, double aY, double aZ)
{
    xp = aX;
    yp = aY;
    zp = aZ;
}

/**
 * @brief
 *
 * @return Quaternion::operator
 */
inline Quaternion::operator QVariant() const
{
    return QVariant::fromValue<Quaternion>(*this);
}

#endif
