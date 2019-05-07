#ifndef ELLIPSOIDGEOMETRY_H
#define ELLIPSOIDGEOMETRY_H

#include "ligeometry.h"
#include "cartesian3.h"

class LICORE_EXPORT EllipsoidGeometry : public LiGeometry
{
public:
    EllipsoidGeometry(const Cartesian3 &radii,
                      int stackPartitions = 64,
                      int slicePartitions = 64);

private:
    void create();

    Cartesian3 _radii;
    int _stackPartitions;
    int _slicePartitions;
};

#endif // ELLIPSOIDGEOMETRY_H
