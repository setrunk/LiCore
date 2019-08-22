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

    Cartographic toWgs84(double x, double y, const QgsCoordinateReferenceSystem &crs);
    QgsPointXY toNative(const Cartographic &p, const QgsCoordinateReferenceSystem &crs);

    LiRectangle toWgs84(const QgsRectangle &extent, const QgsCoordinateReferenceSystem &crs);
    QgsRectangle toNative(const LiRectangle &extent, const QgsCoordinateReferenceSystem &crs);

    static TransformHelper *instance();

    QgsCoordinateReferenceSystem *WGS84();
    QgsCoordinateReferenceSystem *CGCS2000();

    QgsCoordinateTransform *CGCS2000Transform();
    QgsCoordinateTransform *crsTransfrom(const QgsCoordinateReferenceSystem &crs);

private:
    TransformHelper();

    QgsCoordinateReferenceSystem _wgs84;
    QgsCoordinateReferenceSystem _cgcs2000;
    QHash<QString, QgsCoordinateTransform *> _crsTransforms;
};

#endif // TRANSFORMHELPER_H
