#ifndef LIANIMATIONSAMPLER_H
#define LIANIMATIONSAMPLER_H

#include "linode.h"

class LiAnimationSamplerPrivate;

class LICORE_EXPORT LiAnimationSampler : public LiNode
{
    Q_OBJECT
public:
    enum Interpolaction
    {
        Linear,
        Step,
        Cubic
    };
    Q_ENUM(Interpolaction)

    explicit LiAnimationSampler(LiNode *parent = nullptr);

    Interpolaction interpolaction() const;
    void setInterpolaction(Interpolaction interpolaction);

    // in seconds
    QVector<float> times() const;
    void setTimes(const QVector<float> &times);

    QByteArray values() const;
    void setValues(const QByteArray &values);

signals:
    void interpolactionChanged();

private:
    Q_DECLARE_PRIVATE(LiAnimationSampler)
};

#endif // LIANIMATIONSAMPLER_H
