#ifndef LIPARTICLEEMITTER_H
#define LIPARTICLEEMITTER_H

#include "liparticlebase.h"
#include "axisalignedboundingbox.h"
#include "vector3.h"

class LiParticleSystem;
class LiParticleExtruder;
class LiParticleDirection;
class LiParticleEmitterPrivate;

class LICORE_EXPORT LiParticleEmitter : public LiParticleBase
{
    Q_OBJECT
    Q_PROPERTY(LiParticleSystem* system READ system WRITE setSystem NOTIFY systemChanged)
    Q_PROPERTY(QString groupName READ groupName WRITE setGroupName NOTIFY groupNameChanged)
    Q_PROPERTY(LiParticleExtruder* shapeType READ extruder WRITE setExtruder NOTIFY extruderChanged)
    Q_PROPERTY(int startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(int emitRate READ particlesPerSecond WRITE setParticlesPerSecond NOTIFY particlesPerSecondChanged)
    Q_PROPERTY(int lifeSpan READ particleDuration WRITE setParticleDuration NOTIFY particleDurationChanged)
    Q_PROPERTY(int lifeSpanVariation READ particleDurationVariation WRITE setParticleDurationVariation NOTIFY particleDurationVariationChanged)
    Q_PROPERTY(int maximumEmitted READ maxParticleCount WRITE setMaxParticleCount NOTIFY maximumEmittedChanged)
    Q_PROPERTY(qreal size READ particleSize WRITE setParticleSize NOTIFY particleSizeChanged)
    Q_PROPERTY(qreal endSize READ particleEndSize WRITE setParticleEndSize NOTIFY particleEndSizeChanged)
    Q_PROPERTY(qreal sizeVariation READ particleSizeVariation WRITE setParticleSizeVariation NOTIFY particleSizeVariationChanged)
    Q_PROPERTY(LiParticleDirection* velocity READ velocity WRITE setVelocity NOTIFY velocityChanged)
    Q_PROPERTY(LiParticleDirection* acceleration READ acceleration WRITE setAcceleration NOTIFY accelerationChanged)
    Q_PROPERTY(qreal velocityFromMovement READ velocityFromMovement WRITE setVelocityFromMovement NOTIFY velocityFromMovementChanged)

public:
    enum Lifetime
    {
        InfiniteLife = particleMaxLife
    };
    Q_ENUM(Lifetime)

    enum ShapeType
    {
        Line,
        Rectangle,
        Ellipse
    };
    Q_ENUM(ShapeType)

    explicit LiParticleEmitter(LiNode *parent = 0);
    ~LiParticleEmitter();

    ShapeType shapeType() const;
    void setShapeType(ShapeType shape);

    Vector2 shapeSize() const;
    void setShapeSize(const Vector2 &size);

    bool fillShape() const;
    void setFillShape(bool fill);

    qreal width() const;
    qreal height() const;

    Vector3 offset() const;
    void setOffset(const Vector3 &offset);

    LiParticleSystem *system() const;
    LiParticleExtruder *extruder() const;
    LiParticleDirection *velocity() const;
    LiParticleDirection *acceleration() const;

    QString groupName() const;

    int startTime() const;
    int particleCount() const;
    int maxParticleCount() const;
    int particleDuration() const;
    int particleDurationVariation() const;
    int particlesPerSecond() const;
    qreal particleSize() const;
    qreal particleEndSize() const;
    qreal particleSizeVariation() const;

    qreal velocityFromMovement() const;
    void setVelocityFromMovement(qreal s);

    virtual void reset();
    virtual void emitParticles(int timeStamp);

    AABB boundingBox() const;

Q_SIGNALS:
    void particlesPerSecondChanged(int);
    void particleDurationChanged(int);
    void enabledChanged(bool);
    void systemChanged(LiParticleSystem* arg);
    void groupNameChanged(const QString &arg);
    void particleDurationVariationChanged(int arg);
    void extruderChanged(LiParticleExtruder* arg);
    void particleSizeChanged(qreal arg);
    void particleEndSizeChanged(qreal arg);
    void particleSizeVariationChanged(qreal arg);
    void velocityChanged(LiParticleDirection * arg);
    void accelerationChanged(LiParticleDirection * arg);
    void maximumEmittedChanged(int arg);
    void particleCountChanged();
    void velocityFromMovementChanged();
    void startTimeChanged(int arg);

public Q_SLOTS:
    void pulse(int milliseconds);
    void burst(int num);
    void burst(int num, qreal xMin, qreal yMin);
    void setParticlesPerSecond(int arg);
    void setParticleDuration(int arg);
    void setSystem(LiParticleSystem* arg);
    void setGroupName(const QString &arg);
    void setParticleDurationVariation(int arg);
    void setExtruder(LiParticleExtruder* arg);
    void setParticleSize(qreal arg);
    void setParticleEndSize(qreal arg);
    void setParticleSizeVariation(qreal arg);
    void setVelocity(LiParticleDirection * arg);
    void setAcceleration(LiParticleDirection * arg);
    void setMaxParticleCount(int arg);
    void setStartTime(int arg);

protected:
    explicit LiParticleEmitter(LiParticleEmitterPrivate &dd, LiNode *parent = 0);
    void componentComplete() override;

private:
    friend class LiParticleSystem;
    Q_DECLARE_PRIVATE(LiParticleEmitter)
};

#endif // LIPARTICLEEMITTER_H
