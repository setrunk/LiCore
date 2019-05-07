#ifndef LIGRAVITYAFFECTOR_H
#define LIGRAVITYAFFECTOR_H

#include "liparticleaffector.h"
#include "vector3.h"

class LiGravityAffectorPrivate;

class LICORE_EXPORT LiGravityAffector : public LiParticleAffector
{
    Q_OBJECT
    Q_PROPERTY(qreal magnitude READ magnitude WRITE setMagnitude NOTIFY magnitudeChanged)
    Q_PROPERTY(Vector3 direction READ direction WRITE setDirection NOTIFY directionChanged)

public:
    explicit LiGravityAffector(LiNode *parent = 0);

    qreal magnitude() const;
    Vector3 direction() const;

Q_SIGNALS:
    void magnitudeChanged(qreal arg);
    void directionChanged(const Vector3 &arg);

public Q_SLOTS:
    void setMagnitude(qreal arg);
    void setDirection(const Vector3 &arg);

private:
    Q_DECLARE_PRIVATE(LiGravityAffector)
};

#endif // LIGRAVITYAFFECTOR_H
