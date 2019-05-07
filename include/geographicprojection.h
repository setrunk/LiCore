#ifndef GEOGRAPHICPROJECTION_H
#define GEOGRAPHICPROJECTION_H

#include "mapprojection.h"

class Ellipsoid;

class LICORE_EXPORT GeographicProjection : public MapProjection
{
public:
    explicit GeographicProjection(Ellipsoid *ellipsoid = 0);

    Cartesian3 project(const Cartographic &cartographic) const;
    Cartographic unproject(const Cartesian3 &cartesian) const;

private:
    Ellipsoid *_ellipsoid;
    double _semimajorAxis;
    double _oneOverSemimajorAxis;
};

#endif // GEOGRAPHICPROJECTION_H
