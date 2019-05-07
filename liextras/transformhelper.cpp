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

Cartographic TransformHelper::transform(double x, double y, const QgsCoordinateReferenceSystem * crs, bool forward)
{
    QgsCoordinateTransform *t = crsTransfrom(crs);
    if (!t)
        return Cartographic();

    QgsPointXY p = t->transform(x, y, forward ? QgsCoordinateTransform::ForwardTransform : QgsCoordinateTransform::ReverseTransform);
    double lon = forward ? qDegreesToRadians(p.x()) : p.x();
    double lat = forward ? qDegreesToRadians(p.y()) : p.y();

    return Cartographic(lon, lat);
}

LiRectangle TransformHelper::transform(const QgsRectangle &extent, const QgsCoordinateReferenceSystem * crs, bool forward)
{
    QgsRectangle rect;
    QgsCoordinateTransform *t = crsTransfrom(crs);
    if (t)
    {
        rect = t->transform(extent, forward ? QgsCoordinateTransform::ForwardTransform : QgsCoordinateTransform::ReverseTransform);
    }
    else
    {
        rect = extent;
    }

    LiRectangle result(rect.xMinimum(),
                       rect.yMinimum(),
                       rect.xMaximum(),
                       rect.yMaximum());

    return forward ? result.toRadians() : result;
}

LiRectangle TransformHelper::transform(const LiRectangle &extent, const QgsCoordinateReferenceSystem *crs, bool forward)
{
    return transform(toRectangle(extent), crs, forward);
}
