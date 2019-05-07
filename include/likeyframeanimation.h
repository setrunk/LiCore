#ifndef LIKEYFRAMEANIMATION_H
#define LIKEYFRAMEANIMATION_H

#include "lianimation.h"
#include <QEasingCurve>

class LiTransform;
class LiKeyframeAnimationPrivate;

class LICORE_EXPORT LiKeyframeAnimation : public LiAnimation
{
    Q_OBJECT
    Q_PROPERTY(QVector<double> framePositions READ framePositions WRITE setFramePositions NOTIFY framePositionsChanged)
    Q_PROPERTY(LiTransform *target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QEasingCurve easing READ easing WRITE setEasing NOTIFY easingChanged)
    Q_PROPERTY(QString targetName READ targetName WRITE setTargetName NOTIFY targetNameChanged)
    Q_PROPERTY(RepeatMode startMode READ startMode WRITE setStartMode NOTIFY startModeChanged)
    Q_PROPERTY(RepeatMode endMode READ endMode WRITE setEndMode NOTIFY endModeChanged)

public:
    explicit LiKeyframeAnimation(LiNode *parent = nullptr);

    enum RepeatMode
    {
        None,
        Constant,
        Repeat,
    };
    Q_ENUM(RepeatMode)

    QVector<double> framePositions() const;
    QVector<LiTransform *> keyframeList() const;
    LiTransform *target() const;
    QEasingCurve easing() const;
    QString targetName() const;
    RepeatMode startMode() const;
    RepeatMode endMode() const;

    void setKeyframes(const QVector<LiTransform *> &keyframes);
    void addKeyframe(LiTransform *keyframe);
    void removeKeyframe(LiTransform *keyframe);

public Q_SLOTS:
    void setFramePositions(const QVector<double> &positions);
    void setTarget(LiTransform *target);
    void setEasing(const QEasingCurve &easing);
    void setTargetName(const QString &name);
    void setStartMode(RepeatMode mode);
    void setEndMode(RepeatMode mode);

Q_SIGNALS:
    void framePositionsChanged(const QVector<double> &positions);
    void targetChanged(LiTransform *target);
    void easingChanged(const QEasingCurve &easing);
    void targetNameChanged(const QString &name);
    void startModeChanged(RepeatMode startMode);
    void endModeChanged(RepeatMode endMode);

private:
    void updateAnimation(double position);

    Q_DECLARE_PRIVATE(LiKeyframeAnimation)
};

#endif // LIKEYFRAMEANIMATION_H
