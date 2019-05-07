#ifndef LIBLENDING_H
#define LIBLENDING_H

#include "lirenderstate.h"

class LiBlendingPrivate;

class LICORE_EXPORT LiBlending : public LiRenderState
{
    Q_OBJECT
    Q_PROPERTY(bool blendEnabled READ blendEnabled WRITE setBlendEnabled NOTIFY blendEnabledChanged)
    Q_PROPERTY(Blending sourceRgb READ sourceRgb WRITE setSourceRgb NOTIFY sourceRgbChanged)
    Q_PROPERTY(Blending sourceAlpha READ sourceAlpha WRITE setSourceAlpha NOTIFY sourceAlphaChanged)
    Q_PROPERTY(Blending destinationRgb READ destinationRgb WRITE setDestinationRgb NOTIFY destinationRgbChanged)
    Q_PROPERTY(Blending destinationAlpha READ destinationAlpha WRITE setDestinationAlpha NOTIFY destinationAlphaChanged)
    Q_PROPERTY(int bufferIndex READ bufferIndex WRITE setBufferIndex NOTIFY bufferIndexChanged)
//    Q_PROPERTY(BlendFunction blendFunction READ blendFunction WRITE setBlendFunction NOTIFY blendFunctionChanged)
public:
    enum Blending
    {
        Zero = 0,
        One = 1,
        SourceColor = 0x0300,
        SourceAlpha = 0x0302,
        Source1Alpha,
        Source1Color,
        DestinationColor = 0x0306,
        DestinationAlpha = 0x0304,
        SourceAlphaSaturate = 0x0308,
        ConstantColor = 0x8001,
        ConstantAlpha = 0x8003,
        OneMinusSourceColor = 0x0301,
        OneMinusSourceAlpha = 0x0303,
        OneMinusDestinationAlpha = 0x0305,
        OneMinusDestinationColor = 0x0307,
        OneMinusConstantColor = 0x8002,
        OneMinusConstantAlpha = 0x8004,
        OneMinusSource1Alpha,
        OneMinusSource1Color,
        OneMinusSource1Color0 = OneMinusSource1Color
    };
    Q_ENUM(Blending)

    enum BlendFunction
    {
        Add = 0x8006,
        Subtract = 0x800A,
        ReverseSubtract = 0x800B,
        Min = 0x8007,
        Max = 0x8008
    };
    Q_ENUM(BlendFunction)

    explicit LiBlending(LiNode *parent = nullptr);
    explicit LiBlending(bool blendEnabled, LiNode *parent = nullptr);

    bool blendEnabled() const;
    int bufferIndex() const;
    Blending sourceRgb() const;
    Blending destinationRgb() const;
    Blending sourceAlpha() const;
    Blending destinationAlpha() const;
    BlendFunction equationRgb() const;
    BlendFunction equationAlpha() const;

    static LiBlending *alphaBlend();
    static LiBlending *blendDisabled();

public Q_SLOTS:
    void setBlendEnabled(bool blendEnabled);
    void setBufferIndex(int index);
    void setSourceRgb(Blending sourceRgb);
    void setDestinationRgb(Blending destinationRgb);
    void setSourceAlpha(Blending sourceAlpha);
    void setDestinationAlpha(Blending destinationAlpha);
    void setSourceRgba(Blending sourceRgba);
    void setDestinationRgba(Blending destinationRgba);
    void setEquationRgb(BlendFunction equation);
    void setEquationAlpha(BlendFunction equation);

Q_SIGNALS:
    void blendEnabledChanged(bool blendEnabled);
    void bufferIndexChanged(int index);
    void sourceRgbChanged(Blending sourceRgb);
    void sourceAlphaChanged(Blending sourceAlpha);
    void destinationRgbChanged(Blending destinationRgb);
    void destinationAlphaChanged(Blending destinationAlpha);
    void sourceRgbaChanged(Blending sourceRgba);
    void destinationRgbaChanged(Blending destinationRgba);
    void equationRgbChanged(BlendFunction equation);
    void equationAlphaChanged(BlendFunction equation);

private:
    Q_DECLARE_PRIVATE(LiBlending)
};

#endif // LIBLENDING_H
