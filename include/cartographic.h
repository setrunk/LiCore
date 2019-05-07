#ifndef CARTOGRAPHIC_H
#define CARTOGRAPHIC_H

#include "licore_global.h"
#include <QJSValue>

class Cartesian3;

/**
 * @brief
 * Cartographic定义了制图空间的经纬度坐标点。
 * 在js/qml中使用Li.cartographic(lon,lat,height)函数构造。
 */
class LICORE_EXPORT Cartographic
{
public:
    /**
     * @brief
     *
     */
    Cartographic()
        : longitude(0)
        , latitude(0)
        , height(0)
    {
    }

    /**
     * @brief
     *
     * @param lon
     * @param lat
     * @param h
     */
    Cartographic(double lon, double lat, double h = 0.0)
        : longitude(lon)
        , latitude(lat)
        , height(h)
    {
    }

    /**
     * @brief
     *
     * @param value
     */
    Cartographic(const QJSValue &value);

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator ==(const Cartographic &other) const
    {
        return  other.longitude == longitude &&
                other.latitude == latitude &&
                other.height == height;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator !=(const Cartographic &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const
    {
        return longitude == 0 && latitude == 0 && height == 0;
    }

    /**
     * @brief
     *
     * @return double
     */
    double getLongitude() const { return longitude; }
    /**
     * @brief
     *
     * @param value
     */
    void setLongitude(double value) { longitude = value; }

    /**
     * @brief
     *
     * @return double
     */
    double getLatitude() const { return latitude; }
    /**
     * @brief
     *
     * @param value
     */
    void setLatitude(double value) { latitude = value; }

    /**
     * @brief
     *
     * @return double
     */
    double getHeight() const { return height; }
    /**
     * @brief
     *
     * @param value
     */
    void setHeight(double value) { height = value; }

    /**
     * @brief
     *
     * @return Cartographic
     */
    Cartographic toDegrees() const;
    /**
     * @brief
     *
     * @return Cartographic
     */
    Cartographic toRadius() const;

    /**
     * @brief
     *
     * @param longitude
     * @param latitude
     * @param height
     * @return Cartographic
     */
    static Cartographic fromDegrees(double longitude, double latitude, double height);
    /**
     * @brief
     *
     * @param cartesian
     * @return Cartographic
     */
    static Cartographic fromCartesian(const Cartesian3 &cartesian);

    /**
     * @brief
     *
     * @param value
     * @return Cartographic
     */
    static Cartographic fromJSValue(const QJSValue &value);
    /**
     * @brief
     *
     * @param value
     */
    void toJSValue(QJSValue &value);

public:
    double longitude; /**< TODO: describe */
    double latitude; /**< TODO: describe */
    double height; /**< TODO: describe */
};

Q_DECLARE_METATYPE(Cartographic)
Q_DECLARE_TYPEINFO(Cartographic, Q_PRIMITIVE_TYPE);

#endif // CARTOGRAPHIC_H
