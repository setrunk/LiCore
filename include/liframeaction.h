#ifndef LIFRAMEACTION_H
#define LIFRAMEACTION_H

#include "licomponent.h"

class LICORE_EXPORT LiFrameAction : public LiComponent
{
    Q_OBJECT
public:
    explicit LiFrameAction(LiNode *parent = nullptr);
    ~LiFrameAction();

signals:
    void triggered(double dt);
};

#endif // LIFRAMEACTION_H
