#ifndef INTERSECTIONS2D_H
#define INTERSECTIONS2D_H

#include "licore_global.h"
#include "cartesian3.h"

class LICORE_EXPORT Intersections2D
{
public:

    static QVector<double> clipTriangleAtAxisAlignedThreshold(double threshold, bool keepAbove,
                                                              double u0, double u1, double u2);

    static Cartesian3 computeBarycentricCoordinates(double x, double y,
                                                    double x1, double y1,
                                                    double x2, double y2,
                                                    double x3, double y3);

};

#endif // INTERSECTIONS2D_H
