#ifndef LIPARTICLEEXTRUDER_H
#define LIPARTICLEEXTRUDER_H

#include "liparticlebase.h"
#include "boundingrectangle.h"
#include "vector3.h"

class LiParticleExtruderPrivate;

class LICORE_EXPORT LiParticleExtruder : public LiParticleBase
{
    Q_OBJECT
public:
    explicit LiParticleExtruder(LiNode *parent = 0);
    ~LiParticleExtruder();

    virtual Vector3 extrude(const BoundingRectangle &) = 0;
    virtual bool contains(const BoundingRectangle &bounds, const Vector3 &point) = 0;

protected:
    explicit LiParticleExtruder(LiParticleExtruderPrivate &dd, LiNode *parent = 0);
};

#endif // LIPARTICLEEXTRUDER_H
