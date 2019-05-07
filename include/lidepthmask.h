#ifndef LIDEPTHMASK_H
#define LIDEPTHMASK_H

#include "lirenderstate.h"

class LiDepthMaskPrivate;

class LICORE_EXPORT LiDepthMask : public LiRenderState
{
    Q_OBJECT
    Q_PROPERTY(Mask mask READ mask WRITE setMask NOTIFY maskChanged)
public:
    enum Mask {
        Read,
        ReadWrite
    };

    explicit LiDepthMask(LiNode *parent = nullptr);

    Mask mask() const;

public slots:
    void setMask(Mask mask);

signals:
    void maskChanged(Mask mask);

private:
    Q_DECLARE_PRIVATE(LiDepthMask)
};

#endif // LIDEPTHMASK_H
