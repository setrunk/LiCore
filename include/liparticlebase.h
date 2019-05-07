#ifndef LIPARTICLEBASE_H
#define LIPARTICLEBASE_H

#include "linode.h"
#include "liparticle_global.h"
#include <QQmlParserStatus>

class LiParticleBasePrivate;

class LICORE_EXPORT LiParticleBase : public LiNode, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

public:
    explicit LiParticleBase(LiNode *parent = nullptr);
    virtual ~LiParticleBase();

protected:
    explicit LiParticleBase(LiParticleBasePrivate &dd, LiNode *parent = nullptr);
    void classBegin() override {}
    void componentComplete() override {}
};

#endif // LIPARTICLEBASE_H
