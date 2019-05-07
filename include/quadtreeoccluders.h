#ifndef QUADTREEOCCLUDERS_H
#define QUADTREEOCCLUDERS_H

#include "licore_global.h"

class Ellipsoid;
class EllipsoidalOccluder;

class LICORE_EXPORT QuadtreeOccluders
{
public:
    QuadtreeOccluders(Ellipsoid *ellipsoid);

    EllipsoidalOccluder *ellipsoid() const { return _ellipsoid; }

private:
    EllipsoidalOccluder *_ellipsoid;
};

#endif // QUADTREEOCCLUDERS_H
