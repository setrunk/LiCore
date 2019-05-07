#ifndef LIVIEWPORTQUADRENDERER_H
#define LIVIEWPORTQUADRENDERER_H

#include "ligeometryrenderer.h"

class LiRenderTarget;
class LiViewportQuadRendererPrivate;

class LICORE_EXPORT LiViewportQuadRenderer : public LiGeometryRenderer
{
    Q_OBJECT
public:
    explicit LiViewportQuadRenderer(LiNode *parent = nullptr);

    LiRenderTarget *framebuffer() const;
    void setFramebuffer(LiRenderTarget *framebuffer);

    QRect viewport() const;
    void setViewport(const QRect &viewport);

private:
    Q_DECLARE_PRIVATE(LiViewportQuadRenderer)
};

#endif // LIVIEWPORTQUADRENDERER_H
