#include "qgsmapprojection.h"

double QgsMapProjection::maximumLatitude = QgsMapProjection::mercatorAngleToGeodeticLatitude(Math::PI);

QgsMapProjection::QgsMapProjection(const QgsCoordinateReferenceSystem &crs)
    : m_useWebMercator(crs.authid() == QLatin1String("EPSG:3857"))
{
    static QgsCoordinateReferenceSystem wgs84 = QgsCoordinateReferenceSystem::fromOgcWmsCrs("EPSG:4326");
    m_transform = QgsCoordinateTransform(crs, wgs84);
}

Cartesian3 QgsMapProjection::project(const Cartographic &cartographic) const
{
    double lon = Math::toDegrees(cartographic.longitude);
    double lat = m_useWebMercator ?
                Math::toDegrees(Math::clamp(cartographic.latitude, -maximumLatitude, maximumLatitude)) :
                Math::toDegrees(cartographic.latitude);
    auto s = m_transform.transform(lon, lat, QgsCoordinateTransform::ReverseTransform);
    return Cartesian3(s.x(), s.y(), cartographic.height);
}

Cartographic QgsMapProjection::unproject(const Cartesian3 &cartesian) const
{
    auto s = m_transform.transform(cartesian.x, cartesian.y, QgsCoordinateTransform::ForwardTransform);
    return Cartographic(Math::toRadians(s.x()), Math::toRadians(s.y()), cartesian.z);
}

QgsRectangle QgsMapProjection::toNative(const LiRectangle &r) const
{
    auto southwest = project(r.southwest());
    auto northeast = project(r.northeast());
    return QgsRectangle(southwest.x, southwest.y, northeast.x, northeast.y);
}

LiRectangle QgsMapProjection::toWgs84(const QgsRectangle &r) const
{
    auto southwest = unproject(Cartesian3(r.xMinimum(), r.yMinimum(), 0));
    auto northeast = unproject(Cartesian3(r.xMaximum(), r.yMaximum(), 0));
    return LiRectangle(southwest.longitude, southwest.latitude, northeast.longitude, northeast.latitude);
}

double QgsMapProjection::mercatorAngleToGeodeticLatitude(double mercatorAngle)
{
    return Math::PI_OVER_TWO - (2.0 * atan(exp(-mercatorAngle)));
}

double QgsMapProjection::geodeticLatitudeToMercatorAngle(double latitude)
{
    // Clamp the latitude coordinate to the valid Mercator bounds.
    latitude = Math::clamp(latitude, -maximumLatitude, maximumLatitude);
    double sinLatitude = sin(latitude);
    return 0.5 * log((1.0 + sinLatitude) / (1.0 - sinLatitude));
}
