#ifndef LICOMPUTERENDERER_H
#define LICOMPUTERENDERER_H

#include "licomponent.h"

class LiComputeRendererPrivate;
class LiRenderSystem;
class LiMaterial;

class LICORE_EXPORT LiComputeRenderer : public LiComponent
{
    Q_OBJECT
    Q_PROPERTY(LiMaterial* material READ material WRITE setMaterial NOTIFY materialChanged)
    Q_PROPERTY(int workGroupX READ workGroupX WRITE setWorkGroupX NOTIFY workGroupXChanged)
    Q_PROPERTY(int workGroupY READ workGroupY WRITE setWorkGroupY NOTIFY workGroupYChanged)
    Q_PROPERTY(int workGroupZ READ workGroupZ WRITE setWorkGroupZ NOTIFY workGroupZChanged)
public:
    explicit LiComputeRenderer(LiNode *parent = nullptr);

    LiMaterial *material() const;
    void setMaterial(LiMaterial *material);

    int workGroupX() const;
    int workGroupY() const;
    int workGroupZ() const;

    void setWorkGroupX(int workGroupX);
    void setWorkGroupY(int workGroupY);
    void setWorkGroupZ(int workGroupZ);

signals:
    void materialChanged(LiMaterial *material);
    void workGroupXChanged();
    void workGroupYChanged();
    void workGroupZChanged();

public slots:

private:
    Q_DECLARE_PRIVATE(LiComputeRenderer)
    friend class LiRenderSystem;
};

#endif // LICOMPUTERENDERER_H
