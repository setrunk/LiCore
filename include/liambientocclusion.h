#ifndef LIAMBIENTOCCLUSION_H
#define LIAMBIENTOCCLUSION_H

#include "licomponent.h"

class LiAmbientOcclusionPrivate;
class LiRenderSystem;
class LiTexture;

class LICORE_EXPORT LiAmbientOcclusion : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(double fadeIn READ fadeIn WRITE setFadeIn NOTIFY fadeInChanged)
    Q_PROPERTY(double amount READ amount WRITE setAmount NOTIFY amountChanged)
public:
    explicit LiAmbientOcclusion(QObject *parent = 0);

    double radius() const;
    void setRadius(double radius);

    double fadeIn() const;
    void setFadeIn(double fadeIn);

    double amount() const;
    void setAmount(double amount);

    LiTexture *texture() const;

Q_SIGNALS:
    void radiusChanged();
    void fadeInChanged();
    void amountChanged();

private:
    Q_DECLARE_PRIVATE(LiAmbientOcclusion)
    friend class LiRenderSystem;
};

#endif // LIAMBIENTOCCLUSION_H
