#ifndef QGSMAPPROJECTION_H
#define QGSMAPPROJECTION_H

#include "liextrasglobal.h"
#include "mapprojection.h"
#include "rectangle.h"
#include "qgscoordinatereferencesystem.h"
#include "qgscoordinatetransform.h"

class LIEXTRAS_EXPORT QgsMapProjection : public MapProjection
{
public:
    explicit QgsMapProjection(const QgsCoordinateReferenceSystem &crs);

    Cartesian3 project(const Cartographic &cartographic) const;
    Cartographic unproject(const Cartesian3 &cartesian) const;

    QgsRectangle toNative(const LiRectangle &r) const;
    LiRectangle toWgs84(const QgsRectangle &r) const;

    bool useWebMercator() const { return m_useWebMercator; }

    static double maximumLatitude;
    static double mercatorAngleToGeodeticLatitude(double mercatorAngle);
    static double geodeticLatitudeToMercatorAngle(double latitude);

private:
    QgsCoordinateTransform m_transform;
    bool m_useWebMercator;
};

inline LiRectangle toRectangle(const QgsRectangle &r)
{
    return LiRectangle(r.xMinimum(), r.yMinimum(), r.xMaximum(), r.yMaximum());
}

inline QgsRectangle toRectangle(const LiRectangle &r)
{
    return QgsRectangle(r.west, r.south, r.east, r.north);
}

inline LiRectangle computeTileExtent(int x, int y, int level)
{
    double space = Math::PI / (1<<level);
    double west = -Math::PI + x * space;
    double east = west + space;
    double north = Math::PI_OVER_TWO - y * space;
    double south = north - space;
    return LiRectangle(west, south, east, north);
}

#endif // QGSMAPPROJECTION_H
