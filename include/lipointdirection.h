#ifndef LIPOINTDIRECTION_H
#define LIPOINTDIRECTION_H

#include "liparticledirection.h"

class LiPointDirectionPrivate;

class LICORE_EXPORT LiPointDirection : public LiParticleDirection
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qreal z READ z WRITE setZ NOTIFY zChanged)
    Q_PROPERTY(qreal xVariation READ xVariation WRITE setXVariation NOTIFY xVariationChanged)
    Q_PROPERTY(qreal yVariation READ yVariation WRITE setYVariation NOTIFY yVariationChanged)
    Q_PROPERTY(qreal zVariation READ zVariation WRITE setZVariation NOTIFY zVariationChanged)

public:
    explicit LiPointDirection(LiNode *parent = 0);

    Vector3 sample(const Vector3 &from) override;

    qreal x() const;
    qreal y() const;
    qreal z() const;

    qreal xVariation() const;
    qreal yVariation() const;
    qreal zVariation() const;

Q_SIGNALS:
    void xChanged(qreal arg);
    void yChanged(qreal arg);
    void zChanged(qreal arg);
    void xVariationChanged(qreal arg);
    void yVariationChanged(qreal arg);
    void zVariationChanged(qreal arg);

public Q_SLOTS:
    void setX(qreal arg);
    void setY(qreal arg);
    void setZ(qreal arg);
    void setXVariation(qreal arg);
    void setYVariation(qreal arg);
    void setZVariation(qreal arg);

private:
    Q_DECLARE_PRIVATE(LiPointDirection)
};

#endif // LIPOINTDIRECTION_H
