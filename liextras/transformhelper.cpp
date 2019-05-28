#include "transformhelper.h"
#include "qgspointxy.h"
#include "qgsrectangle.h"
#include "cartographic.h"

TransformHelper::TransformHelper()
{
    _wgs84.createFromOgcWmsCrs("EPSG:4326");
    _cgcs2000.createFromOgcWmsCrs("EPSG:4547");
}

TransformHelper::~TransformHelper()
{

}

TransformHelper *TransformHelper::instance()
{
    static TransformHelper gis;
    return &gis;
}

QgsCoordinateReferenceSystem *TransformHelper::WGS84()
{
    return &_wgs84;
}

QgsCoordinateReferenceSystem *TransformHelper::CGCS2000()
{
    return &_cgcs2000;
}

QgsCoordinateTransform *TransformHelper::CGCS2000Transform()
{
    return crsTransfrom(&_cgcs2000);
}

QgsCoordinateTransform *TransformHelper::crsTransfrom(const QgsCoordinateReferenceSystem * crs)
{
    if (!crs)
        return nullptr;

    QgsCoordinateTransform *transform = _crsTransforms.value(crs->authid(), 0);
    if (!transform)
    {
        transform = new QgsCoordinateTransform(*crs, _wgs84);
        _crsTransforms[crs->authid()] = transform;
    }
    return transform;
}

Cartographic TransformHelper::toWgs84(double x, double y, const QgsCoordinateReferenceSystem *crs)
{
    Cartographic result;

    QgsCoordinateTransform *t = crsTransfrom(crs);
    if (t)
    {
        QgsPointXY p = t->transform(x, y, QgsCoordinateTransform::ForwardTransform);
        result.longitude = qDegreesToRadians(p.x());
        result.latitude = qDegreesToRadians(p.y());
    }

    return result;
}

QgsPointXY TransformHelper::toNative(const Cartographic &p, const QgsCoordinateReferenceSystem *crs)
{
    QgsPointXY result;

    QgsCoordinateTransform *t = crsTransfrom(crs);
    if (t)
    {
        result = t->transform(qRadiansToDegrees(p.longitude), qRadiansToDegrees(p.latitude), QgsCoordinateTransform::ReverseTransform);
    }

    return result;
}

LiRectangle TransformHelper::toWgs84(const QgsRectangle &extent, const QgsCoordinateReferenceSystem *crs)
{
    auto pMin = toWgs84(extent.xMinimum(), extent.yMinimum(), crs);
    auto pMax = toWgs84(extent.xMaximum(), extent.yMaximum(), crs);
    return LiRectangle(pMin.longitude, pMin.latitude, pMax.longitude, pMax.latitude);
}

QgsRectangle TransformHelper::toNative(const LiRectangle &extent, const QgsCoordinateReferenceSystem *crs)
{
    auto pMin = toNative(extent.southwest(), crs);
    auto pMax = toNative(extent.northeast(), crs);
    return QgsRectangle(pMin, pMax);
}
