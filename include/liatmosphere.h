#ifndef LIATMOSPHERE_H
#define LIATMOSPHERE_H

#include "ligeometryrenderer.h"

class Ellipsoid;
class LiAtmospherePrivate;

class LICORE_EXPORT LiAtmosphere : public LiGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(double hue READ hueShift WRITE setHueShift NOTIFY hueChanged)
    Q_PROPERTY(double saturation READ saturationShift WRITE setSaturationShift NOTIFY saturationChanged)
    Q_PROPERTY(double brightness READ brightnessShift WRITE setBrightnessShift NOTIFY brightnessChanged)
public:
    explicit LiAtmosphere(LiNode *parent = 0);

    bool show() const;
    void setShow(bool show);

    double hueShift() const;
    void setHueShift(double hueShift);

    double saturationShift() const;
    void setSaturationShift(double saturationShift);

    double brightnessShift() const;
    void setBrightnessShift(double brightnessShift);

signals:
    void hueChanged(double value);
    void saturationChanged(double value);
    void brightnessChanged(double value);

private:
    Q_DECLARE_PRIVATE(LiAtmosphere)
};

#endif // LIATMOSPHERE_H
