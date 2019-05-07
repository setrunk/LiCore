#ifndef TRANSFORMHELPER_H
#define TRANSFORMHELPER_H

#include "liextrasglobal.h"
#include "rectangle.h"
#include <qgscoordinatereferencesystem.h>
#include <qgscoordinatetransform.h>

class LIEXTRAS_EXPORT TransformHelper
{
public:
    ~TransformHelper();

    static TransformHelper *instance();

    QgsCoordinateReferenceSystem *WGS84();
    QgsCoordinateReferenceSystem *CGCS2000();

    QgsCoordinateTransform *CGCS2000Transform();
    QgsCoordinateTransform *crsTransfrom(const QgsCoordinateReferenceSystem * crs);

    Cartographic transform(double x, double y, const QgsCoordinateReferenceSystem * crs, bool forward = true);
    LiRectangle transform(const QgsRectangle &extent, const QgsCoordinateReferenceSystem * crs, bool forward = true);
    LiRectangle transform(const LiRectangle &extent, const QgsCoordinateReferenceSystem * crs, bool forward = true);

private:
    TransformHelper();

    QgsCoordinateReferenceSystem _wgs84;
    QgsCoordinateReferenceSystem _cgcs2000;
    QHash<QString, QgsCoordinateTransform *> _crsTransforms;
};

inline LiRectangle toRectangle(const QgsRectangle &r)
{
    return LiRectangle(r.xMinimum(), r.yMinimum(), r.xMaximum(), r.yMaximum());
}

inline QgsRectangle toRectangle(const LiRectangle &r)
{
    return QgsRectangle(r.west, r.south, r.east, r.north);
}

inline QgsRectangle computeTileExtent(int x, int y, int level)
{
    double space = 180.0 / (1<<level);
    double west = -180.0 + x * space;
    double east = west + space;
    double north = 90.0 - y * space;
    double south = north - space;
    return QgsRectangle(west, south, east, north);
}

#endif // TRANSFORMHELPER_H
