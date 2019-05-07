#ifndef LIPARTICLESYSTEM_H
#define LIPARTICLESYSTEM_H

#include "liparticle_global.h"
#include "ligeometryrenderer.h"
#include <QQmlParserStatus>

class LiParticleGroup;
class LiParticleEmitter;
class LiParticleRenderer;
class LiParticleAffector;
class LiParticleSystemPrivate;

class LICORE_EXPORT LiParticleSystem : public LiGeometryRenderer, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(bool running READ isRunning WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool paused READ isPaused WRITE setPaused NOTIFY pausedChanged)
    Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged)

public:
    explicit LiParticleSystem(LiNode *parent = 0);
    ~LiParticleSystem();

    bool isRunning() const;
    bool isPaused() const;
    bool isEmpty() const;
    int count();

    int timeStamp() const;
    void setTimeStamp(int t);

    bool debugMode() const;
    void setDebugMode(bool arg);

    QList<QPointer<LiParticleEmitter>> emitters() const;
    QList<QPointer<LiParticleAffector>> affectors() const;
    QList<QPointer<LiParticleRenderer>> renderers() const;

    void registerParticleRenderer(LiParticleRenderer* r);
    void registerParticleEmitter(LiParticleEmitter* e);
    void registerParticleAffector(LiParticleAffector* a);
    void registerParticleGroup(LiParticleGroup* g);

Q_SIGNALS:
    void runningChanged(bool arg);
    void pausedChanged(bool arg);
    void emptyChanged(bool arg);

public Q_SLOTS:
    void start();
    void stop();
    void restart();
    void pause();
    void resume();
    void reset();
    void setRunning(bool arg);
    void setPaused(bool arg);

protected:
    void componentComplete() override;
    void classBegin() override {}

private:
    Q_DECLARE_PRIVATE(LiParticleSystem)
};

#endif // LIPARTICLESYSTEM_H


