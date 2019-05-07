#ifndef CARTESIAN4_H
#define CARTESIAN4_H

#include "licore_global.h"
#include "cartesian3.h"

/**
 * @brief
 * Cartesian4定义了四维元素组，可以和Vector4相互转换。
 */
class LICORE_EXPORT Cartesian4
{
public:
    /**
     * @brief
     *
     */
    Cartesian4() : x(0), y(0), z(0), w(0) {}
    /**
     * @brief
     *
     * @param _x
     * @param _y
     * @param _z
     * @param _w
     */
    Cartesian4(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) {}
    /**
     * @brief
     *
     * @param v
     */
    Cartesian4(const Cartesian4 &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    /**
     * @brief
     *
     * @param v
     */
    Cartesian4(const Cartesian3 &v) : x(v.x), y(v.y), z(v.z), w(0) {}

    /**
     * @brief
     *
     * @return double
     */
    double getX() const { return x; }
    /**
     * @brief
     *
     * @return double
     */
    double getY() const { return y; }
    /**
     * @brief
     *
     * @return double
     */
    double getZ() const { return z; }
    /**
     * @brief
     *
     * @return double
     */
    double getW() const { return w; }

    /**
     * @brief
     *
     * @param value
     */
    void setX(double value) { x = value; }
    /**
     * @brief
     *
     * @param value
     */
    void setY(double value) { y = value; }
    /**
     * @brief
     *
     * @param value
     */
    void setZ(double value) { z = value; }
    /**
     * @brief
     *
     * @param value
     */
    void setW(double value) { w = value; }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator ==(const Cartesian4 &other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator !=(const Cartesian4 &other) const {
        return !(*this == other);
    }

    /**
     * @brief
     *
     * @return Cartesian4 operator
     */
    Cartesian4 operator -() const {
        return Cartesian4(-x, -y, -z, -w);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian4 operator
     */
    Cartesian4 operator +(const Cartesian4 &other) const {
        return Cartesian4(x + other.x,
                          y + other.y,
                          z + other.z,
                          w + other.w);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian4 &operator
     */
    Cartesian4 &operator +=(const Cartesian4 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian4 operator
     */
    Cartesian4 operator -(const Cartesian4 &other) const {
        return Cartesian4(x - other.x,
                          y - other.y,
                          z - other.z,
                          w - other.w);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian4 &operator
     */
    Cartesian4 &operator -=(const Cartesian4 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian4 operator
     */
    Cartesian4 operator *(double f) const {
        return Cartesian4(x*f, y*f, z*f, w*f);
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian4 &operator
     */
    Cartesian4 &operator *=(double f) {
        x *= f;
        y *= f;
        z *= f;
        w *= f;
        return *this;
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian4 operator
     */
    Cartesian4 operator /(double f) const {
        return Cartesian4(x/f, y/f, z/f, w/f);
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian4 &operator
     */
    Cartesian4 &operator /=(double f) {
        x /= f;
        y /= f;
        z /= f;
        w /= f;
        return *this;
    }

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const
    {
        return x == 0 && y == 0 && z == 0 && w == 0;
    }

    /**
     * @brief
     *
     * @return double
     */
    double magnitude() const {
        return sqrt(x*x + y*y + z*z + w*w);
    }

    /**
     * @brief
     *
     * @return double
     */
    double magnitudeSquared() const {
        return x*x + y*y + z*z + w*w;
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return double
     */
    static double dot(const Cartesian4 &left, const Cartesian4 &right) {
        return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
    }

    /**
     * @brief
     *
     * @param right
     * @return double
     */
    double dot(const Cartesian4 &right) const {
        return Cartesian4::dot(*this, right);
    }

    /**
     * @brief
     *
     * @return Cartesian4
     */
    Cartesian4 &normalize() {
        double t = x*x + y*y + z*z + w*w;
        if (!qFuzzyIsNull(t)) {
            t = 1.0 / sqrt(t);
            x *= t;
            y *= t;
            z *= t;
            w *= t;
        }
        return *this;
    }

public:
    double x; /**< TODO: describe */
    double y; /**< TODO: describe */
    double z; /**< TODO: describe */
    double w; /**< TODO: describe */
};

Q_DECLARE_METATYPE(Cartesian4)
Q_DECLARE_TYPEINFO(Cartesian4, Q_PRIMITIVE_TYPE);

#endif // CARTESIAN4_H
