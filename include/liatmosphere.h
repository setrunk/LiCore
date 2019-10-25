#ifndef LIATMOSPHERE_H
#define LIATMOSPHERE_H

#include "ligeometryrenderer.h"

class Ellipsoid;
class LiAtmospherePrivate;

class LICORE_EXPORT LiAtmosphere : public LiGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(float hue READ hueShift WRITE setHueShift NOTIFY hueChanged)
    Q_PROPERTY(float saturation READ saturationShift WRITE setSaturationShift NOTIFY saturationChanged)
    Q_PROPERTY(float brightness READ brightnessShift WRITE setBrightnessShift NOTIFY brightnessChanged)
    Q_PROPERTY(float intensity READ intensity WRITE setIntensity NOTIFY intensityChanged)
    Q_PROPERTY(float exposure READ exposure WRITE setExposure NOTIFY exposureChanged)
public:
    explicit LiAtmosphere(LiNode *parent = 0);

    bool show() const;
    void setShow(bool show);

    float intensity() const;
    void setIntensity(float intensity);

    float exposure() const;
    void setExposure(float exposure);

    float hueShift() const;
    void setHueShift(float hueShift);

    float saturationShift() const;
    void setSaturationShift(float saturationShift);

    float brightnessShift() const;
    void setBrightnessShift(float brightnessShift);

signals:
    void intensityChanged(float value);
    void exposureChanged(float value);
    void hueChanged(float value);
    void saturationChanged(float value);
    void brightnessChanged(float value);

private:
    Q_DECLARE_PRIVATE(LiAtmosphere)
};

#endif // LIATMOSPHERE_H
