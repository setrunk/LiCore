#ifndef LIANIMATION_H
#define LIANIMATION_H

#include "linode.h"

class LiAnimationPrivate;

class LICORE_EXPORT LiAnimation : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(QString animationName READ animationName WRITE setAnimationName NOTIFY animationNameChanged)
    Q_PROPERTY(LiAnimation::AnimationType animationType READ animationType CONSTANT)
    Q_PROPERTY(double position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(double duration READ duration NOTIFY durationChanged)

public:
    enum AnimationType
    {
        KeyframeAnimation = 1,
        MorphingAnimation = 2,
        VertexBlendAnimation = 3,
    };
    Q_ENUM(AnimationType)

    explicit LiAnimation(LiNode *parent = nullptr);
    virtual ~LiAnimation();

    QString animationName() const;
    AnimationType animationType() const;
    double position() const;
    double duration() const;

public Q_SLOTS:
    void setAnimationName(const QString &name);
    void setPosition(double position);
    void setDuration(double duration);

protected:
    explicit LiAnimation(LiAnimationPrivate &dd, LiNode *parent = nullptr);

Q_SIGNALS:
    void animationNameChanged(const QString &name);
    void positionChanged(double position);
    void durationChanged(double duration);

private:
    Q_DECLARE_PRIVATE(LiAnimation)
};

#endif // LIANIMATION_H
