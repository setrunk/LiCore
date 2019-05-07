#ifndef LILIGHT_H
#define LILIGHT_H

#include "licomponent.h"

class LiLightPrivate;

class LICORE_EXPORT LiLight : public LiComponent
{
    Q_OBJECT
public:
    enum Type
    {
        Directional,
        Point,
        Spot
    };
    Q_ENUM(Type)

    explicit LiLight(LiNode *parent = 0);
    explicit LiLight(Type type, LiNode *parent = 0);
    virtual ~LiLight();

    Type type() const;
    void setType(Type type);

    float range() const;
    void setRange(float range);

    float spotAngle() const; // degrees
    void setSpotAngle(float angle);

    QColor color() const;
    void setColor(const QColor &color);

    QColor ambient() const;
    void setAmbient(const QColor &ambient);

    float intensity() const;
    void setIntensity(float intensity);

protected:
    explicit LiLight(LiLightPrivate &dd, LiNode *parent = nullptr);

signals:
    void typeChanged(Type type);
    void rangeChanged(double range);
    void spotAngleChanged(double angle);
    void colorChanged(const QColor &color);
    void ambientChanged(const QColor &ambient);
    void intensityChanged(float intensity);

private:
    Q_DECLARE_PRIVATE(LiLight)
};

#endif // LILIGHT_H
