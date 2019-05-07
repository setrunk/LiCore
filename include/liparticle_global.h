#ifndef PARTICLE_GLOBAL_H
#define PARTICLE_GLOBAL_H

#include "licore_global.h"

typedef int ParticleGroupDataID;

const int particleMaxLife = 600000;

struct Color4ub
{
    uchar r;
    uchar g;
    uchar b;
    uchar a;
};

static inline int roundedTime(qreal a)
{
    // in ms
    return (int)qRound(a*1000.0);
}

#endif // PARTICLE_GLOBAL_H
