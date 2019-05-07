#ifndef LIIMAGERAPARTICLERENDERER_H
#define LIIMAGERAPARTICLERENDERER_H

#include "liparticlerenderer.h"

class LiParticleDirection;
class LiImageParticleRendererPrivate;

class LICORE_EXPORT LiImageParticleRenderer : public LiParticleRenderer
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(EntryEffect entryEffect READ entryEffect WRITE setEntryEffect NOTIFY entryEffectChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged RESET resetColor)
    Q_PROPERTY(qreal colorVariation READ colorVariation WRITE setColorVariation NOTIFY colorVariationChanged RESET resetColor)
    Q_PROPERTY(qreal alpha READ alpha WRITE setAlpha NOTIFY alphaChanged RESET resetColor)
    Q_PROPERTY(qreal alphaVariation READ alphaVariation WRITE setAlphaVariation NOTIFY alphaVariationChanged RESET resetColor)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged RESET resetRotation)
    Q_PROPERTY(qreal rotationVariation READ rotationVariation WRITE setRotationVariation NOTIFY rotationVariationChanged RESET resetRotation)
    Q_PROPERTY(qreal rotationVelocity READ rotationVelocity WRITE setRotationVelocity NOTIFY rotationVelocityChanged RESET resetRotation)
    Q_PROPERTY(qreal rotationVelocityVariation READ rotationVelocityVariation WRITE setRotationVelocityVariation NOTIFY rotationVelocityVariationChanged RESET resetRotation)
    Q_PROPERTY(bool autoRotation READ autoRotation WRITE setAutoRotation NOTIFY autoRotationChanged RESET resetRotation)
    Q_PROPERTY(LiParticleDirection* xVector READ xVector WRITE setXVector NOTIFY xVectorChanged RESET resetDeformation)
    Q_PROPERTY(LiParticleDirection* yVector READ yVector WRITE setYVector NOTIFY yVectorChanged RESET resetDeformation)

public:
    explicit LiImageParticleRenderer(LiNode *parent = 0);
    ~LiImageParticleRenderer();

    enum Status
    {
        Null,
        Ready,
        Loading,
        Error
    };
    Q_ENUM(Status)

    enum EntryEffect
    {
        None = 0,
        Fade = 1,
        Scale = 2
    };
    Q_ENUM(EntryEffect)

    enum BlendMode
    {
        NormalBlend,
        AdditiveBlend
    };
    Q_ENUM(BlendMode)

    Status status() const;
    EntryEffect entryEffect() const;
    QUrl image() const;
    QColor color() const;
    qreal colorVariation() const;
    qreal alpha() const;
    qreal alphaVariation() const;

    BlendMode blendMode() const;

    qreal rotation() const;
    qreal rotationVariation() const;
    qreal rotationVelocity() const;
    qreal rotationVelocityVariation() const;
    bool autoRotation() const;

    LiParticleDirection *xVector() const;
    LiParticleDirection *yVector() const;

    void resetColor();
    void resetRotation();
    void resetDeformation();

Q_SIGNALS:
    void statusChanged(Status arg);
    void entryEffectChanged(EntryEffect arg);
    void imageChanged();
    void colorChanged();
    void colorVariationChanged();
    void alphaChanged();
    void alphaVariationChanged();
    void rotationChanged(qreal arg);
    void rotationVariationChanged(qreal arg);
    void rotationVelocityChanged(qreal arg);
    void rotationVelocityVariationChanged(qreal arg);
    void autoRotationChanged(bool arg);
    void xVectorChanged(LiParticleDirection* arg);
    void yVectorChanged(LiParticleDirection* arg);

public Q_SLOTS:
    void setEntryEffect(EntryEffect arg);
    void setImage(const QUrl &image);
    void setColor(const QColor &arg);
    void setColorVariation(qreal arg);
    void setAlpha(qreal arg);
    void setAlphaVariation(qreal arg);
    void setBlendMode(BlendMode mode);
    void setRotation(qreal arg);
    void setRotationVariation(qreal arg);
    void setRotationVelocity(qreal arg);
    void setRotationVelocityVariation(qreal arg);
    void setAutoRotation(bool arg);
    void setXVector(LiParticleDirection* arg);
    void setYVector(LiParticleDirection* arg);

private:
    friend class LiParticleSystem;
    Q_DECLARE_PRIVATE(LiImageParticleRenderer)
};

#endif // LIIMAGERAPARTICLERENDERER_H
