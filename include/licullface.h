#ifndef LICULLFACE_H
#define LICULLFACE_H

#include "lirenderstate.h"

class LiCullFacePrivate;

class LICORE_EXPORT LiCullFace : public LiRenderState
{
    Q_OBJECT
    Q_PROPERTY(CullingMode mode READ mode WRITE setMode NOTIFY modeChanged)
public:

    enum CullingMode
    {
        NoCulling = 0x0,
        Front = 0x0404,
        Back = 0x0405,
        FrontAndBack = 0x0408
    };
    Q_ENUM(CullingMode)

    explicit LiCullFace(LiNode *parent = nullptr);
    explicit LiCullFace(CullingMode mode, LiNode *parent = nullptr);
    ~LiCullFace();

    CullingMode mode() const;

public Q_SLOTS:
    void setMode(CullingMode mode);

Q_SIGNALS:
    void modeChanged(CullingMode mode);

private:
    Q_DECLARE_PRIVATE(LiCullFace)
};

#endif // LICULLFACE_H
