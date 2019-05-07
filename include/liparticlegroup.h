#ifndef LIPARTICLEGROUP_H
#define LIPARTICLEGROUP_H

#include "liparticlebase.h"

class LiParticleSystem;

class LICORE_EXPORT LiParticleGroup : public LiParticleBase
{
    Q_OBJECT
    Q_PROPERTY(LiParticleSystem* system READ system WRITE setSystem NOTIFY systemChanged)

public:
    explicit LiParticleGroup(LiNode* parent = 0);
    ~LiParticleGroup();

    QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    LiParticleSystem* system() const { return m_system; }
    int maximumAlive() const { return m_maximumAlive; }

public Q_SLOTS:
    void setMaximumAlive(int arg);
    void setSystem(LiParticleSystem* arg);

Q_SIGNALS:
    void maximumAliveChanged(int arg);
    void systemChanged(LiParticleSystem* arg);

protected:
    void componentComplete() override;

private:
    int m_maximumAlive;
    QString m_name;
    LiParticleSystem* m_system;
};

#endif // LIPARTICLEGROUP_H
