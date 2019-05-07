#ifndef LIPARTICLEDIRECTION_H
#define LIPARTICLEDIRECTION_H

#include "liparticlebase.h"
#include "vector3.h"

class LiParticleDirectionPrivate;

class LICORE_EXPORT LiParticleDirection : public LiParticleBase
{
    Q_OBJECT
public:
    explicit LiParticleDirection(LiNode *parent = 0);
    ~LiParticleDirection();

    virtual Vector3 sample(const Vector3 &from);

protected:
    explicit LiParticleDirection(LiParticleDirectionPrivate &dd, LiNode *parent = 0);
};

#endif // LIPARTICLEDIRECTION_H
