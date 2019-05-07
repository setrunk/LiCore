#ifndef CARTESIAN2_H
#define CARTESIAN2_H

#include "licore_global.h"
#include "limath.h"

/**
 * @brief
 * Cartesian2定义二维空间的坐标点，和Vector2类相似，可以和Vector2相互转换。。
 */
class LICORE_EXPORT Cartesian2
{
public:
    /**
     * @brief
     *
     */
    Cartesian2() : x(0), y(0) {}
    /**
     * @brief
     *
     * @param _x
     * @param _y
     */
    Cartesian2(double _x, double _y) : x(_x), y(_y) {}
    /**
     * @brief
     *
     * @param v
     */
    Cartesian2(const Cartesian2 &v) : x(v.x), y(v.y) {}

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
     * @param other
     * @return bool operator
     */
    bool operator ==(const Cartesian2 &other) const {
        return x == other.x && y == other.y;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator !=(const Cartesian2 &other) const {
        return !(*this == other);
    }

    /**
     * @brief
     *
     * @return Cartesian2 operator
     */
    Cartesian2 operator -() const {
        return Cartesian2(-x, -y);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian2 operator
     */
    Cartesian2 operator +(const Cartesian2 &other) const {
        return Cartesian2(x + other.x,
                          y + other.y);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian2 &operator
     */
    Cartesian2 &operator +=(const Cartesian2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian2 operator
     */
    Cartesian2 operator -(const Cartesian2 &other) const {
        return Cartesian2(x - other.x,
                          y - other.y);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian2 &operator
     */
    Cartesian2 &operator -=(const Cartesian2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian2 operator
     */
    Cartesian2 operator *(double f) const {
        return Cartesian2(x*f, y*f);
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian2 &operator
     */
    Cartesian2 &operator *=(double f) {
        x *= f;
        y *= f;
        return *this;
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian2 operator
     */
    Cartesian2 operator /(double f) const {
        return Cartesian2(x/f, y/f);
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian2 &operator
     */
    Cartesian2 &operator /=(double f) {
        x /= f;
        y /= f;
        return *this;
    }

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const {
        return x == 0 && y == 0;
    }

    /**
     * @brief
     *
     * @return double
     */
    double magnitude() const {
        return sqrt(x*x + y*y);
    }

    /**
     * @brief
     *
     * @return double
     */
    double magnitudeSquared() const {
        return x*x + y*y;
    }

    /**
     * @brief
     *
     * @param other
     * @return double
     */
    double distance(const Cartesian2 &other) const {
        return (*this - other).magnitude();
    }

    /**
     * @brief
     *
     * @return Cartesian2
     */
    Cartesian2 &normalize() {
        double t = x*x + y*y;
        if (!qFuzzyIsNull(t)) {
            t = 1.0 / sqrt(t);
            x *= t;
            y *= t;
        }
        return *this;
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return double
     */
    static double dot(const Cartesian2 &left, const Cartesian2 &right) {
        return left.x * right.x + left.y * right.y;
    }

    /**
     * @brief
     *
     * @param right
     * @return double
     */
    double dot(const Cartesian2 &right) const {
        return Cartesian2::dot(*this, right);
    }

public:
    double x; /**< TODO: describe */
    double y; /**< TODO: describe */
};

Q_DECLARE_METATYPE(Cartesian2)
Q_DECLARE_TYPEINFO(Cartesian2, Q_PRIMITIVE_TYPE);

#endif // CARTESIAN2_H
