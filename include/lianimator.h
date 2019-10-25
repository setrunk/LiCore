#ifndef LIANIMATOR_H
#define LIANIMATOR_H

#include "licomponent.h"

class LiAnimationClip;
class LiAnimatorPrivate;

class LICORE_EXPORT LiAnimator : public LiComponent
{
    Q_OBJECT
public:
    enum PlayMode
    {
        PlaySingle,
        PlayOrder,
        PlayAll
    };
    Q_ENUM(PlayMode)

    enum Loop
    {
        Inifinite = -1
    };
    Q_ENUM(Loop)

    explicit LiAnimator(LiNode *parent = nullptr);
    ~LiAnimator();

    QVector<LiAnimationClip *> animationClips() const;
    void addAnimationClip(LiAnimationClip *clip);
    void removeAnimationClip(LiAnimationClip *clip);
    int clipCount() const;

    bool isRunning() const;
    void setRunning(bool running);

    void start();
    void stop();

    PlayMode playMode() const;
    void setPlayMode(PlayMode playMode);

    int loopCount() const;
    void setLoopCount(int loopCount);

    int currentClip() const;
    void setCurrentClip(int currentClip);
    void setCurrentClip(LiAnimationClip *currentClip);

Q_SIGNALS:
    void animationClipsChanged();
    void runningChanged();
    void playModeChanged();
    void loopCountChanged();
    void currentClipChanged();

private:
    Q_DECLARE_PRIVATE(LiAnimator)
};

#endif // LIANIMATOR_H
