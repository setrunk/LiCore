#ifndef WEBMERCATORPROJECTION_H
#define WEBMERCATORPROJECTION_H

#include "mapprojection.h"

class Ellipsoid;

class LICORE_EXPORT WebMercatorProjection : public MapProjection
{
public:
    WebMercatorProjection(Ellipsoid *ellipsoid = 0);

    Cartesian3 project(const Cartographic &cartographic) const;
    Cartographic unproject(const Cartesian3 &cartesian) const;

    static double maximumLatitude;
    static double mercatorAngleToGeodeticLatitude(double mercatorAngle);
    static double geodeticLatitudeToMercatorAngle(double latitude);

private:
    Ellipsoid *_ellipsoid;
    double _semimajorAxis;
    double _oneOverSemimajorAxis;
};

#endif // WEBMERCATORPROJECTION_H
