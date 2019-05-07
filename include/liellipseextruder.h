#ifndef LIELLIPSEEXTRUDER_H
#define LIELLIPSEEXTRUDER_H

#include "liparticleextruder.h"

class LiEllipseExtruder : public LiParticleExtruder
{
    Q_OBJECT
    Q_PROPERTY(bool fill READ fill WRITE setFill NOTIFY fillChanged)//###Use base class? If it's still box

public:
    explicit LiEllipseExtruder(LiNode *parent = 0);

    Vector3 extrude(const BoundingRectangle &) override;
    bool contains(const BoundingRectangle &bounds, const Vector3 &point) override;

    bool fill() const
    {
        return m_fill;
    }

Q_SIGNALS:
    void fillChanged(bool arg);

public Q_SLOTS:
    void setFill(bool arg);

private:
    bool m_fill;
};

#endif // LIELLIPSEEXTRUDER_H
