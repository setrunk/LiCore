#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "licore_global.h"
#include "limath.h"
#include "vector4.h"
#include "cartographic.h"

class Ellipsoid;
class BoundingSphere;

/**
 * @brief
 * 制图空间的坐标范围，是以经纬度坐标为参考，可以和球面坐标相互转换。
 */
class LICORE_EXPORT LiRectangle
{
public:
    static LiRectangle MAX_VALUE; /**< TODO: describe */

    /**
     * @brief
     *
     */
    LiRectangle()
        : west(0.0)
        , south(0.0)
        , east(0.0)
        , north(0.0)
    {
    }

    /**
     * @brief
     *
     * @param w
     * @param s
     * @param e
     * @param n
     */
    LiRectangle(double w, double s, double e, double n)
        : west(w)
        , south(s)
        , east(e)
        , north(n)
    {
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator==(const LiRectangle &other) const
    {
        return west == other.west && south == other.south &&
                east == other.east && north == other.north;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator!=(const LiRectangle &other) const
    {
        return west != other.west || south != other.south ||
                east != other.east || north != other.north;
    }

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const
    {
        return west == 0 && south == 0 && east == 0 && north == 0;
    }

    /**
     * @brief
     *
     * @return double
     */
    double getWest() const { return west; }
    /**
     * @brief
     *
     * @return double
     */
    double getSouth() const { return south; }
    /**
     * @brief
     *
     * @return double
     */
    double getEast() const { return east; }
    /**
     * @brief
     *
     * @return double
     */
    double getNorth() const { return north; }
    /**
     * @brief
     *
     * @param value
     */
    void setWest(double value) { west = value; }
    /**
     * @brief
     *
     * @param value
     */
    void setSouth(double value) { south = value; }
    /**
     * @brief
     *
     * @param value
     */
    void setEast(double value) { east = value; }
    /**
     * @brief
     *
     * @param value
     */
    void setNorth(double value) { north = value; }

    /**
     * @brief
     *
     * @return double
     */
    double width() const { return east - west; }
    /**
     * @brief
     *
     * @return double
     */
    double height() const { return north - south; }
    /**
     * @brief
     *
     * @return double
     */
    double computeWidth();
    /**
     * @brief
     *
     * @return double
     */
    double computeHeight();

    /**
     * @brief
     *
     * @return Cartographic
     */
    Cartographic center() const;
    /**
     * @brief
     *
     * @return Cartographic
     */
    Cartographic southwest() const { return Cartographic(west, south, 0); }
    /**
     * @brief
     *
     * @return Cartographic
     */
    Cartographic northwest() const { return Cartographic(west, north, 0); }
    /**
     * @brief
     *
     * @return Cartographic
     */
    Cartographic northeast() const { return Cartographic(east, north, 0); }
    /**
     * @brief
     *
     * @return Cartographic
     */
    Cartographic southeast() const { return Cartographic(east, south, 0); }

    /**
     * @brief
     *
     * @param other
     */
    void combine(const LiRectangle &other);
    /**
     * @brief
     *
     * @param c
     */
    void combine(const Cartographic &c);
    /**
     * @brief
     *
     * @param cartographic
     * @return bool
     */
    bool contains(const Cartographic &cartographic) const;
    /**
     * @brief
     *
     * @param other
     * @return bool
     */
    bool intersected(const LiRectangle &other) const;

    /**
     * @brief
     *
     * @return BoundingSphere
     */
    BoundingSphere bounds() const;
    /**
     * @brief
     *
     * @return Vector4
     */
    Vector4 toVector4() const;
    /**
     * @brief
     *
     * @return Cartesian4
     */
    Cartesian4 toCartesian4() const;
    /**
     * @brief
     *
     * @return LiRectangle
     */
    LiRectangle toDegrees() const;
    /**
     * @brief
     *
     * @return LiRectangle
     */
    LiRectangle toRadians() const;
    /**
     * @brief
     *
     * @param value
     */
    void toJSValue(QJSValue &value) const;

    /**
     * @brief
     *
     * @param ellipsoid
     * @param surfaceHeight
     * @return QVector<Cartesian3>
     */
    QVector<Cartesian3> subsample(Ellipsoid *ellipsoid, double surfaceHeight) const;

    /**
     * @brief
     *
     * @param w
     * @param s
     * @param e
     * @param n
     * @return LiRectangle
     */
    static LiRectangle fromDegrees(double w, double s, double e, double n);
    /**
     * @brief
     *
     * @param w
     * @param s
     * @param e
     * @param n
     * @return LiRectangle
     */
    static LiRectangle fromRadians(double w, double s, double e, double n);
    /**
     * @brief
     *
     * @param value
     * @return LiRectangle
     */
    static LiRectangle fromJSValue(const QJSValue &value);
    /**
     * @brief
     *
     * @param rectangle
     * @param otherRectangle
     * @return LiRectangle
     */
    static LiRectangle intersection(const LiRectangle &rectangle, const LiRectangle &otherRectangle);
    /**
     * @brief
     *
     * @param rectangle
     * @param otherRectangle
     * @return LiRectangle
     */
    static LiRectangle simpleIntersection(const LiRectangle &rectangle, const LiRectangle &otherRectangle);

    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const { return QVariant::fromValue(*this); }

public:
    double west; /**< TODO: describe */
    double south; /**< TODO: describe */
    double east; /**< TODO: describe */
    double north; /**< TODO: describe */
};

Q_DECLARE_METATYPE(LiRectangle)
Q_DECLARE_TYPEINFO(LiRectangle, Q_PRIMITIVE_TYPE);

#endif // RECTANGLE_H
