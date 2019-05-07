#ifndef LIRENDERVIEW_H
#define LIRENDERVIEW_H

#include "linode.h"

class LiRenderTarget;
class LiCamera;
class LiScene;
class DrawCommand;
class RenderDevice;
class LiRenderViewPrivate;

class LiRenderView : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(LiRenderTarget * renderTarget READ renderTarget WRITE setRenderTarget NOTIFY renderOutputChanged)
    Q_PROPERTY(QRectF viewport READ viewport WRITE setViewport NOTIFY viewportChanged)
    Q_PROPERTY(LiCamera * camera READ camera WRITE setCamera NOTIFY cameraChanged)
public:
    explicit LiRenderView(LiNode *parent = 0);

    LiRenderTarget *renderTarget() const;
    void setRenderTarget(LiRenderTarget *renderTarget);

    QRectF viewport() const;
    void setViewport(const QRectF &viewport);

    LiCamera *camera() const;
    void setCamera(LiCamera *camera);

    LiScene *scene() const;
    void setScene(LiScene *scene);

signals:
    void renderOutputChanged();
    void viewportChanged();
    void cameraChanged();

public slots:

protected:
    explicit LiRenderView(LiRenderViewPrivate &dd, LiNode *parent = 0);

private:
    Q_DECLARE_PRIVATE(LiRenderView)
};

#endif // LIRENDERVIEW_H
