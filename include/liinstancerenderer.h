#ifndef LIINSTANCERENDERER_H
#define LIINSTANCERENDERER_H

#include "ligeometryrenderer_p.h"

class LiInstanceRendererPrivate;

class LICORE_EXPORT LiInstanceRenderer : public LiGeometryRenderer
{
    Q_OBJECT
public:
    explicit LiInstanceRenderer(LiNode *parent = nullptr);

signals:

public slots:

protected:
    LiInstanceRenderer(LiInstanceRendererPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiInstanceRenderer)
};

#endif // LIINSTANCERENDERER_H
