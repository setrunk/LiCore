#ifndef LIRENDERSTATE_H
#define LIRENDERSTATE_H

#include "linode.h"

class RenderStateSet;
class LiRenderStatePrivate;

class LICORE_EXPORT LiRenderState : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(Order frontFace READ frontFace WRITE setFrontFace NOTIFY frontFaceChanged)
    Q_PROPERTY(bool cull READ cull WRITE setCull NOTIFY cullChanged)
    Q_PROPERTY(CullFace cullFace READ cullFace WRITE setCullFace NOTIFY cullFaceChanged)
    Q_PROPERTY(float lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(bool polygonOffset READ polygonOffset WRITE setPolygonOffset NOTIFY polygonOffsetChanged)
    Q_PROPERTY(float polygonOffsetFactor READ polygonOffsetFactor WRITE setPolygonOffsetFactor NOTIFY polygonOffsetFactorChanged)
    Q_PROPERTY(float polygonOffsetUnits READ polygonOffsetUnits WRITE setPolygonOffsetUnits NOTIFY polygonOffsetUnitsChanged)
    Q_PROPERTY(bool scissorTest READ scissorTest WRITE setScissorTest NOTIFY scissorTestChanged)
    Q_PROPERTY(QRect scissorTestRect READ scissorTestRect WRITE setScissorTestRect NOTIFY scissorTestRectChanged)
    Q_PROPERTY(QVector2D depthRange READ depthRange WRITE setDepthRange NOTIFY depthRangeChanged)
    Q_PROPERTY(bool depthTest READ depthTest WRITE setDepthTest NOTIFY depthTestChanged)
    Q_PROPERTY(AlphaFunc depthTestFunc READ depthTestFunc WRITE setDepthTestFunc NOTIFY depthTestFuncChanged)
    Q_PROPERTY(bool depthWriteMask READ depthWriteMask WRITE setDepthWriteMask NOTIFY depthWriteMaskChanged)
    Q_PROPERTY(uint stencilWriteMask READ stencilWriteMask WRITE setStencilWriteMask NOTIFY stencilWriteMaskChanged)
    Q_PROPERTY(bool blending READ blending WRITE setBlending NOTIFY blendingChanged)
    Q_PROPERTY(QColor blendColor READ blendColor WRITE setBlendColor NOTIFY blendColorChanged)
    Q_PROPERTY(Equation blendEquationRgb READ blendEquationRgb WRITE setBlendEquationRgb NOTIFY blendEquationRgbChanged)
    Q_PROPERTY(Equation blendEquationAlpha READ blendEquationAlpha WRITE setBlendEquationAlpha NOTIFY blendEquationAlphaChanged)
    Q_PROPERTY(BlendFunc blendFuncSourceRgb READ blendFuncSourceRgb WRITE setBlendFuncSourceRgb NOTIFY blendFuncSourceRgbChanged)
    Q_PROPERTY(BlendFunc blendFuncSourceAlpha READ blendFuncSourceAlpha WRITE setBlendFuncSourceAlpha NOTIFY blendFuncSourceAlphaChanged)
    Q_PROPERTY(BlendFunc blendFuncDestRgb READ blendFuncDestRgb WRITE setBlendFuncDestRgb NOTIFY blendFuncDestRgbChanged)
    Q_PROPERTY(BlendFunc blendFuncDestAlpha READ blendFuncDestAlpha WRITE setBlendFuncDestAlpha NOTIFY blendFuncDestAlphaChanged)
public:
    enum CullFace {
        CullNone = 0,
        CullFront = 0x0404,
        CullBack = 0x0405
    };
    Q_ENUM(CullFace)

    enum Order {
        CW = 0x0900,
        CCW = 0x0901
    };
    Q_ENUM(Order)

    enum Operation {
        Keep = 0x1E00,
        Replace = 0x1E01,
        Increase = 0x1E02,
        Decrease = 0x1E03
    };
    Q_ENUM(Operation)

    enum AlphaFunc {
        Never = 0x0200,
        Less = 0x0201,
        Equal = 0x0202,
        LessEqual = 0x0203,
        Greater = 0x0204,
        NotEqual = 0x0205,
        GreaterEqual = 0x0206,
        Always = 0x0207
    };
    Q_ENUM(AlphaFunc)

    enum BlendFunc
    {
        Zero = 0,
        One = 1,
        SourceColor = 0x0300,
        SourceAlpha = 0x0302,
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
        OneMinusConstantAlpha = 0x8004
    };
    Q_ENUM(BlendFunc)

    enum Equation
    {
        Add = 0x8006,
        Subtract = 0x800A,
        ReverseSubtract = 0x800B,
        Min = 0x8007,
        Max = 0x8008
    };
    Q_ENUM(Equation)

    explicit LiRenderState(LiNode *parent = 0);
    ~LiRenderState();

    Order frontFace() const;
    void setFrontFace(Order order);

    bool cull() const;
    void setCull(bool enabled);
    CullFace cullFace() const;
    void setCullFace(CullFace cullFace);

    float lineWidth() const;
    void setLineWidth(float width);

    bool polygonOffset() const;
    void setPolygonOffset(bool enabled);
    float polygonOffsetFactor() const;
    void setPolygonOffsetFactor(float factor);
    float polygonOffsetUnits() const;
    void setPolygonOffsetUnits(float units);

    bool scissorTest() const;
    void setScissorTest(bool enabled);
    QRect scissorTestRect() const;
    void setScissorTestRect(const QRect &rect);

    QVector2D depthRange() const;
    void setDepthRange(const QVector2D &range);

    bool depthTest() const;
    void setDepthTest(bool enabled);
    AlphaFunc depthTestFunc() const;
    void setDepthTestFunc(AlphaFunc func);

    bool depthWriteMask() const;
    void setDepthWriteMask(bool enabled);

    void colorMask(bool *red, bool *green, bool *blue, bool *alpha) const;
    void setColorMask(bool red, bool green, bool blue, bool alpha);

    uint stencilWriteMask() const;
    void setStencilWriteMask(uint mask);
    bool stencilTest() const;
    void setStencilTest(bool enabled);
    AlphaFunc stencilFrontFunc() const;
    void setStencilFrontFunc(AlphaFunc func);
    AlphaFunc stencilBackFunc() const;
    void setStencilBackFunc(AlphaFunc func);
    int stencilReference() const;
    void setStencilReference(int reference);

    Operation stencilFrontFailOp() const;
    void setStencilFrontFailOp(Operation op);
    Operation stencilFrontZFailOp() const;
    void setStencilFrontZFailOp(Operation op);
    Operation stencilFrontZPassOp() const;
    void setStencilFrontZPassOp(Operation op);

    Operation stencilBackFailOp() const;
    void setStencilBackFailOp(Operation op);
    Operation stencilBackZFailOp() const;
    void setStencilBackZFailOp(Operation op);
    Operation stencilBackZPassOp() const;
    void setStencilBackZPassOp(Operation op);

    bool blending(int buffer = 0) const;
    void setBlending(bool enabled, int buffer = 0);
    QColor blendColor() const;
    void setBlendColor(const QColor &color);
    Equation blendEquationRgb() const;
    void setBlendEquationRgb(Equation equation);
    Equation blendEquationAlpha() const;
    void setBlendEquationAlpha(Equation equation);
    BlendFunc blendFuncSourceRgb() const;
    void setBlendFuncSourceRgb(BlendFunc func);
    BlendFunc blendFuncSourceAlpha() const;
    void setBlendFuncSourceAlpha(BlendFunc func);
    BlendFunc blendFuncDestRgb() const;
    void setBlendFuncDestRgb(BlendFunc func);
    BlendFunc blendFuncDestAlpha() const;
    void setBlendFuncDestAlpha(BlendFunc func);

signals:
    void frontFaceChanged();
    void cullChanged();
    void cullFaceChanged();
    void lineWidthChanged();
    void polygonOffsetChanged();
    void polygonOffsetFactorChanged();
    void polygonOffsetUnitsChanged();
    void scissorTestChanged();
    void scissorTestRectChanged();
    void depthRangeChanged();
    void depthTestChanged();
    void depthTestFuncChanged();
    void depthWriteMaskChanged();
    void stencilWriteMaskChanged();
    void blendingChanged();
    void blendColorChanged();
    void blendEquationRgbChanged();
    void blendEquationAlphaChanged();
    void blendFuncSourceRgbChanged();
    void blendFuncSourceAlphaChanged();
    void blendFuncDestRgbChanged();
    void blendFuncDestAlphaChanged();

protected:
    explicit LiRenderState(LiRenderStatePrivate &dd, LiNode *parent = nullptr);

private:
    friend class RenderStateSet;
    Q_DECLARE_PRIVATE(LiRenderState)
};

#endif // LIRENDERSTATE_H
