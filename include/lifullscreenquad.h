#ifndef LIFULLSCREENQUAD_H
#define LIFULLSCREENQUAD_H

#include "ligeometryrenderer.h"

class LiFullscreenQuadPrivate;
class LiRenderTarget;

class LICORE_EXPORT LiFullscreenQuad : public LiGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(LiRenderTarget* renderTarget READ renderTarget WRITE setRenderTarget NOTIFY renderTargetChanged)
    Q_PROPERTY(QRectF viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(bool alphaBlend READ alphaBlend WRITE setAlphaBlend NOTIFY alphaBlendChanged)
    Q_PROPERTY(bool clearRenderTarget READ clearRenderTarget WRITE setClearRenderTarget NOTIFY clearRenderTargetChanged)
public:
    explicit LiFullscreenQuad(LiNode *parent = nullptr);

    LiRenderTarget *renderTarget() const;
    void setRenderTarget(LiRenderTarget *target);

    QRectF viewport() const;
    void setViewport(const QRectF &rect);

    bool alphaBlend() const;
    void setAlphaBlend(bool alphaBlend);

    bool clearRenderTarget() const;
    void setClearRenderTarget(bool clearRenderTarget);

signals:
    void renderTargetChanged();
    void viewportChanged();
    void alphaBlendChanged();
    void clearRenderTargetChanged();

public slots:

private:
    Q_DECLARE_PRIVATE(LiFullscreenQuad)
};

#endif // LIFULLSCREENQUAD_H
