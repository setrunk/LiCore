#ifndef LILINEEXTRUDER_H
#define LILINEEXTRUDER_H

#include "liparticleextruder.h"

class LiLineExtruder : public LiParticleExtruder
{
    Q_OBJECT
    //Default is topleft to bottom right. Flipped makes it topright to bottom left
    Q_PROPERTY(bool mirrored READ mirrored WRITE setMirrored NOTIFY mirroredChanged)

public:
    explicit LiLineExtruder(LiNode *parent = 0);

    Vector3 extrude(const BoundingRectangle &) override;
    bool contains(const BoundingRectangle &bounds, const Vector3 &point) override;

    bool mirrored() const
    {
        return m_mirrored;
    }

Q_SIGNALS:
    void mirroredChanged(bool arg);

public Q_SLOTS:
    void setMirrored(bool arg);

private:
    bool m_mirrored;
};

#endif // LILINEEXTRUDER_H
