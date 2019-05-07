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
    Q_PROPERTY(double density READ density WRITE setDensity NOTIFY densityChanged)
    Q_PROPERTY(bool castShadow READ castShadow WRITE setCastShadow NOTIFY castShadowChanged)
public:
    explicit LiSun(LiNode *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    QColor ambient() const;
    void setAmbient(const QColor &ambient);

    double density() const;
    void setDensity(double density);

    bool castShadow() const;
    void setCastShadow(bool castShadow);

signals:
    void colorChanged();
    void ambientChanged();
    void densityChanged();
    void castShadowChanged();

private:
    Q_DECLARE_PRIVATE(LiSun)
};

#endif // LISUN_H
