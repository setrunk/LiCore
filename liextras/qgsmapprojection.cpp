#include "qgsmapprojection.h"
#include "transformhelper.h"

QgsMapProjection::QgsMapProjection(const QgsCoordinateReferenceSystem &crs)
    : m_crs(crs)
{
}

Cartesian3 QgsMapProjection::project(const Cartographic &cartographic) const
{
    double x = qRadiansToDegrees(cartographic.longitude);
    double y = qRadiansToDegrees(cartographic.latitude);
    auto pt = TransformHelper::instance()->transform(x, y, &m_crs, false);
    return Cartesian3(pt.longitude, pt.latitude, cartographic.height);
}

Cartographic QgsMapProjection::unproject(const Cartesian3 &cartesian) const
{
    auto pt = TransformHelper::instance()->transform(cartesian.x, cartesian.y, &m_crs, true);
    return Cartographic(qDegreesToRadians(pt.longitude), qDegreesToRadians(pt.latitude), cartesian.z);
}
