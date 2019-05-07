#ifndef LIRECTANGLEEXTRUDER_H
#define LIRECTANGLEEXTRUDER_H

#include "liparticleextruder.h"

class LiRectangleExtruder : public LiParticleExtruder
{
    Q_OBJECT
    Q_PROPERTY(bool fill READ fill WRITE setFill NOTIFY fillChanged)

public:
    explicit LiRectangleExtruder(LiNode *parent = 0);

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

protected:
    bool m_fill;
};

#endif // LIRECTANGLEEXTRUDER_H
