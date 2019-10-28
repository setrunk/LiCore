#ifndef LISUN_H
#define LISUN_H

#include "licomponent.h"
#include "vector3.h"

class LiSunPrivate;

class LICORE_EXPORT LiSun : public LiComponent
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor ambient READ ambient WRITE setAmbient NOTIFY ambientChanged)
    Q_PROPERTY(float intensity READ intensity WRITE setIntensity NOTIFY intensityChanged)
    Q_PROPERTY(double density READ density WRITE setDensity NOTIFY densityChanged)
    Q_PROPERTY(float haloSize READ haloSize WRITE setHaloSize NOTIFY haloSizeChanged)
    Q_PROPERTY(bool castShadow READ castShadow WRITE setCastShadow NOTIFY castShadowChanged)
    Q_PROPERTY(float shadowBias READ shadowBias WRITE setShadowBias NOTIFY shadowBiasChanged)
public:
    explicit LiSun(LiNode *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    QColor ambient() const;
    void setAmbient(const QColor &ambient);

    float intensity() const;
    void setIntensity(float intensity);

    double density() const;
    void setDensity(double density);

    float haloSize() const;
    void setHaloSize(float haloSize);

    bool castShadow() const;
    void setCastShadow(bool castShadow);

    float shadowBias() const;
    void setShadowBias(float shadowBias);

signals:
    void colorChanged();
    void ambientChanged();
    void haloSizeChanged();
    void densityChanged();
    void intensityChanged();
    void castShadowChanged();
    void shadowBiasChanged();

private:
    Q_DECLARE_PRIVATE(LiSun)
};

#endif // LISUN_H
