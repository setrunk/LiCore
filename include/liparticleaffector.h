#ifndef PARTICLEAFFECTOR_H
#define PARTICLEAFFECTOR_H

#include "liparticlebase.h"

class LiParticleSystem;
class LiParticleExtruder;
class LiParticleAffectorPrivate;

class LICORE_EXPORT LiParticleAffector : public LiParticleBase
{
    Q_OBJECT
    Q_PROPERTY(LiParticleSystem* system READ system WRITE setSystem NOTIFY systemChanged)
    Q_PROPERTY(LiParticleExtruder* shape READ shape WRITE setShape NOTIFY shapeChanged)
    Q_PROPERTY(QStringList groups READ groups WRITE setGroups NOTIFY groupsChanged)
    Q_PROPERTY(QStringList whenCollidingWith READ whenCollidingWith WRITE setWhenCollidingWith NOTIFY whenCollidingWithChanged)
    Q_PROPERTY(bool once READ onceOff WRITE setOnceOff NOTIFY onceChanged)

public:
    explicit LiParticleAffector(LiNode *parent = 0);
    ~LiParticleAffector();

    virtual void affectSystem(qreal dt);

    LiParticleSystem* system() const;
    QStringList groups() const;
    LiParticleExtruder* shape() const;
    QStringList whenCollidingWith() const;
    bool onceOff() const;

Q_SIGNALS:
    void systemChanged(LiParticleSystem* arg);
    void groupsChanged(const QStringList &arg);
    void onceChanged(bool arg);
    void shapeChanged(LiParticleExtruder* arg);
    void whenCollidingWithChanged(const QStringList &arg);

public Q_SLOTS:
    void setSystem(LiParticleSystem* arg);
    void setGroups(const QStringList &arg);
    void setOnceOff(bool arg);
    void setShape(LiParticleExtruder* arg);
    void setWhenCollidingWith(const QStringList &arg);

protected:
    explicit LiParticleAffector(LiParticleAffectorPrivate &dd, LiNode *parent = 0);
    void componentComplete() override;

private:
    friend class LiParticleSystem;
    Q_DECLARE_PRIVATE(LiParticleAffector)
};

#endif // PARTICLEAFFECTOR_H
