#ifndef LILOGICSYSTEM_H
#define LILOGICSYSTEM_H

#include "liabstractsystem.h"

class LiLogicSystemPrivate;

class LiLogicSystem : public LiAbstractSystem
{
    Q_OBJECT
public:
    explicit LiLogicSystem(QObject *parent = nullptr);
    virtual ~LiLogicSystem();

private:
    void beginFrame();
    void update();
    void endFrame();

    Q_DECLARE_PRIVATE(LiLogicSystem)
};

#endif // LILOGICSYSTEM_H
