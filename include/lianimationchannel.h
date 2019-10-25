#ifndef LIANIMATIONCHANNEL_H
#define LIANIMATIONCHANNEL_H

#include "linode.h"

class LiEntity;
class LiAnimationSampler;
class LiAnimationChannelPrivate;

class LICORE_EXPORT LiAnimationChannel : public LiNode
{
    Q_OBJECT
public:
    enum TransformType
    {
        Translation,
        Rotation,
        Scale,
        Weights
    };
    Q_ENUM(TransformType)

    explicit LiAnimationChannel(LiNode *parent = nullptr);

    TransformType transformType() const;
    void setTransformType(TransformType type);

    LiAnimationSampler *sampler() const;
    void setSampler(LiAnimationSampler *sampler);

    LiEntity *target() const;
    void setTarget(LiEntity *target);

signals:
    void transformTypeChanged();
    void samplerChanged();
    void targetChanged();

private:
    Q_DECLARE_PRIVATE(LiAnimationChannel)
};

#endif // LIANIMATIONCHANNEL_H
