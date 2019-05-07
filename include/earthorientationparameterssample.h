#ifndef EARTHORIENTATIONPARAMETERSSAMPLE_H
#define EARTHORIENTATIONPARAMETERSSAMPLE_H

#include "licore_global.h"

struct EarthOrientationParametersSample
{
public:
    double xPoleWander = 0.0;
    double yPoleWander = 0.0;
    double xPoleOffset = 0.0;
    double yPoleOffset = 0.0;
    double ut1MinusUtc = 0.0;
};

#endif // EARTHORIENTATIONPARAMETERSSAMPLE_H
