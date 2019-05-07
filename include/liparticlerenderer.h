#ifndef LIPARTICLERENDERER_H
#define LIPARTICLERENDERER_H

#include "liparticlebase.h"

class LiParticleSystem;
class LiParticleRendererPrivate;

class LICORE_EXPORT LiParticleRenderer : public LiParticleBase
{
    Q_OBJECT
    Q_PROPERTY(LiParticleSystem* system READ system WRITE setSystem NOTIFY systemChanged)
    Q_PROPERTY(QStringList groups READ groups WRITE setGroups NOTIFY groupsChanged)

public:
    explicit LiParticleRenderer(LiNode *parent = 0);
    ~LiParticleRenderer();

    LiParticleSystem *system() const;
    QStringList groups() const;
    int count() const;

    virtual void reset();

Q_SIGNALS:
    void systemChanged(LiParticleSystem* arg);
    void groupsChanged(const QStringList &arg);
    void countChanged();

public Q_SLOTS:
    void setSystem(LiParticleSystem* arg);
    void setGroups(const QStringList &arg);
    void setCount(int c);

protected:
    explicit LiParticleRenderer(LiParticleRendererPrivate &dd, LiNode *parent = 0);
    void componentComplete() override;

private:
    friend class LiParticleSystem;
    Q_DECLARE_PRIVATE(LiParticleRenderer)
};

#endif // LIPARTICLERENDERER_H
