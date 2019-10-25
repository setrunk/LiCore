#ifndef LIANIMATIONCLIP_H
#define LIANIMATIONCLIP_H

#include "linode.h"

class LiAnimationChannel;
class LiAnimationClipPrivate;

class LICORE_EXPORT LiAnimationClip : public LiNode
{
    Q_OBJECT
public:
    explicit LiAnimationClip(LiNode *parent = nullptr);

    QVector<LiAnimationChannel *> channels() const;
    void addChannel(LiAnimationChannel *channel);
    void removeChannel(LiAnimationChannel *channel);

Q_SIGNALS:
    void channelsChanged();

private:
    Q_DECLARE_PRIVATE(LiAnimationClip)
};

#endif // LIANIMATIONCLIP_H
