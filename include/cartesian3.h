#ifndef CARTESIAN3_H
#define CARTESIAN3_H

#include "licore_global.h"
#include "cartesian2.h"
#include <QJSValue>

class Cartographic;

/**
 * @brief
 * Cartesian3定义了三维空间的坐标点，类似于Vector3，可以和Vector3相互转换。。
 * 在js/qml中可以用Li.cartesian3(x,y,z)函数构造。
 */
class LICORE_EXPORT Cartesian3
{
public:
    /**
     * @brief
     *
     */
    Cartesian3() : x(0), y(0), z(0) {}
    /**
     * @brief
     *
     * @param _x
     * @param _y
     * @param _z
     */
    Cartesian3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    /**
     * @brief
     *
     * @param v
     */
    Cartesian3(const Cartesian3 &v) : x(v.x), y(v.y), z(v.z) {}
    /**
     * @brief
     *
     * @param v
     */
    Cartesian3(const Cartesian2 &v) : x(v.x), y(v.y), z(0) {}
    /**
     * @brief
     *
     * @param value
     */
    Cartesian3(const QJSValue &value);

    static Cartesian3 UNIT_X; /**< TODO: describe */
    static Cartesian3 UNIT_Y; /**< TODO: describe */
    static Cartesian3 UNIT_Z; /**< TODO: describe */

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
     * @return bool
     */
    bool isNull() const
    {
        return x == 0 && y == 0 && z == 0;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator ==(const Cartesian3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator !=(const Cartesian3 &other) const {
        return !(*this == other);
    }

    /**
     * @brief
     *
     * @return Cartesian3 operator
     */
    Cartesian3 operator -() const {
        return Cartesian3(-x, -y, -z);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian3 operator
     */
    Cartesian3 operator +(const Cartesian3 &other) const {
        return Cartesian3(x + other.x,
                          y + other.y,
                          z + other.z);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian3 &operator
     */
    Cartesian3 &operator +=(const Cartesian3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian3 operator
     */
    Cartesian3 operator -(const Cartesian3 &other) const {
        return Cartesian3(x - other.x,
                          y - other.y,
                          z - other.z);
    }

    /**
     * @brief
     *
     * @param other
     * @return Cartesian3 &operator
     */
    Cartesian3 &operator -=(const Cartesian3 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian3 operator
     */
    Cartesian3 operator *(double f) const {
        return Cartesian3(x*f, y*f, z*f);
    }

    /**
     * @brief
     *
     * @param right
     * @return Cartesian3 operator
     */
    Cartesian3 operator *(const Cartesian3 &right) const {
        return Cartesian3(x*right.x, y*right.y, z*right.z);
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian3 &operator
     */
    Cartesian3 &operator *=(double f) {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    /**
     * @brief
     *
     * @param right
     * @return Cartesian3 &operator
     */
    Cartesian3 &operator *=(const Cartesian3 &right) {
        x *= right.x;
        y *= right.y;
        z *= right.z;
        return *this;
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian3 operator
     */
    Cartesian3 operator /(double f) const {
        return Cartesian3(x/f, y/f, z/f);
    }

    /**
     * @brief
     *
     * @param right
     * @return Cartesian3 operator
     */
    Cartesian3 operator /(const Cartesian3 &right) const {
        return Cartesian3(x/right.x, y/right.y, z/right.z);
    }

    /**
     * @brief
     *
     * @param f
     * @return Cartesian3 &operator
     */
    Cartesian3 &operator /=(double f) {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    /**
     * @brief
     *
     * @param right
     * @return Cartesian3 &operator
     */
    Cartesian3 &operator /=(const Cartesian3 &right) {
        x /= right.x;
        y /= right.y;
        z /= right.z;
        return *this;
    }

    /**
     * @brief
     *
     * @param vector
     * @return bool operator
     */
    bool operator<(const Cartesian3 &vector) const
    {
        return x < vector.x && y < vector.y && z < vector.z;
    }

    /**
     * @brief
     *
     * @param vecotr
     * @return bool operator >
     */
    bool operator>(const Cartesian3 &vecotr) const
    {
        return x > vecotr.x && y > vecotr.y && z > vecotr.z;
    }

    /**
     * @brief
     *
     * @return double
     */
    double magnitude() const {
        return sqrt(x*x + y*y + z*z);
    }

    /**
     * @brief
     *
     * @return double
     */
    double magnitudeSquared() const {
        return x*x + y*y + z*z;
    }

    /**
     * @brief
     *
     * @return double
     */
    double length() const {
        return sqrt(x*x + y*y + z*z);
    }

    /**
     * @brief
     *
     * @return double
     */
    double lengthSquared() const {
        return x*x + y*y + z*z;
    }

    /**
     * @brief
     *
     * @param other
     * @return double
     */
    double distance(const Cartesian3 &other) const {
        return distance(*this, other);
    }

    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 abs() const
    {
        return Cartesian3(std::abs(x), std::abs(y), std::abs(z));
    }

    /**
     * @brief
     *
     * @param right
     * @return double
     */
    double dot(const Cartesian3 &right) const {
        return dot(*this, right);
    }

    /**
     * @brief
     *
     * @param right
     * @return double
     */
    double dotProduct(const Cartesian3 &right) const {
        return dotProduct(*this, right);
    }

    /**
     * @brief
     *
     * @param right
     * @return Cartesian3
     */
    Cartesian3 cross(const Cartesian3 &right) const {
        return cross(*this, right);
    }

    /**
     * @brief
     *
     * @param right
     * @return Cartesian3
     */
    Cartesian3 crossProduct(const Cartesian3 &right) const {
        return crossProduct(*this, right);
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return double
     */
    static double dot(const Cartesian3 &left, const Cartesian3 &right) {
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return double
     */
    static double dotProduct(const Cartesian3 &left, const Cartesian3 &right) {
        return left.x * right.x + left.y * right.y + left.z * right.z;
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return Cartesian3
     */
    static Cartesian3 cross(const Cartesian3 &left, const Cartesian3 &right) {
        return Cartesian3(left.y * right.z - left.z * right.y,
                          left.z * right.x - left.x * right.z,
                          left.x * right.y - left.y * right.x);
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return Cartesian3
     */
    static Cartesian3 crossProduct(const Cartesian3 &left, const Cartesian3 &right) {
        return Cartesian3(left.y * right.z - left.z * right.y,
                          left.z * right.x - left.x * right.z,
                          left.x * right.y - left.y * right.x);
    }

    /**
     * @brief
     *
     * @param left
     * @param right
     * @return double
     */
    static double distance(const Cartesian3 &left, const Cartesian3 &right) {
        return (left - right).magnitude();
    }

    /**
     * @brief
     *
     * @param start
     * @param end
     * @param t
     * @return Cartesian3
     */
    static Cartesian3 lerp(const Cartesian3 &start, const Cartesian3 &end, double t) {
        return start * (1.0 - t) + end * t;
    }

    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 &normalize()
    {
        double t = x*x + y*y + z*z;
        if (t != 0) {
            t = 1.0 / sqrt(t);
            x *= t;
            y *= t;
            z *= t;
        }
        return *this;
    }

    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 normalized() const
    {
        double t = x*x + y*y + z*z;
        if (t != 0) {
            t = 1.0 / sqrt(t);
            return Cartesian3(x*t, y*t, z*t);
        }
        return *this;
    }

    /**
     * @brief
     *
     * @param longitude
     * @param latitude
     * @param height
     * @return Cartesian3
     */
    static Cartesian3 fromDegrees(double longitude, double latitude, double height = 0);
    /**
     * @brief
     *
     * @param longitude
     * @param latitude
     * @param height
     * @return Cartesian3
     */
    static Cartesian3 fromRadians(double longitude, double latitude, double height = 0);
    /**
     * @brief
     *
     * @param cartographic
     * @return Cartesian3
     */
    static Cartesian3 fromCartographic(const Cartographic &cartographic);

    /**
     * @brief
     *
     * @param cartesian
     * @return QJSValue
     */
    static QJSValue toJSValue(const Cartesian3 &cartesian);
    /**
     * @brief
     *
     * @param value
     * @return Cartesian3
     */
    static Cartesian3 fromJSValue(const QJSValue &value);
    /**
     * @brief
     *
     * @param value
     */
    void toJSValue(QJSValue &value);

    /**
     * @brief
     *
     * @return double
     */
    double minimumComponent() const
    {
        return std::min(std::min(x, y), z);
    }

    /**
     * @brief
     *
     * @return double
     */
    double maximumComponent() const
    {
        return std::max(std::max(x, y), z);
    }

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Cartesian3
     */
    static Cartesian3 minimumByComponent(const Cartesian3 &v1, const Cartesian3 &v2)
    {
        return Cartesian3(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
    }

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Cartesian3
     */
    static Cartesian3 maximumByComponent(const Cartesian3 &v1, const Cartesian3 &v2)
    {
        return Cartesian3(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
    }

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Cartesian3
     */
    static Cartesian3 min(const Cartesian3 &v1, const Cartesian3 &v2)
    {
        return Cartesian3(std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z));
    }

    /**
     * @brief
     *
     * @param v1
     * @param v2
     * @return Cartesian3
     */
    static Cartesian3 max(const Cartesian3 &v1, const Cartesian3 &v2)
    {
        return Cartesian3(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
    }

//    void fromSpherical();

    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const;

public:
    double x; /**< TODO: describe */
    double y; /**< TODO: describe */
    double z; /**< TODO: describe */
};

Q_DECLARE_METATYPE(Cartesian3)
Q_DECLARE_TYPEINFO(Cartesian3, Q_PRIMITIVE_TYPE);

#endif // CARTESIAN3_H
