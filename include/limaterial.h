#ifndef LIMATERIAL_H
#define LIMATERIAL_H

#include "linode.h"
#include <QQmlListProperty>

class LiShaderProgram;
class LiParameter;
class LiTexture;
class LiRenderState;
class LiMaterialPrivate;

/**
 * @brief
 * LiMaterial时渲染模块的核心类，渲染材质包含Shader、渲染状态、参数等。
 */
class LICORE_EXPORT LiMaterial : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(LiShaderProgram* shaderProgram READ shaderProgram WRITE setShaderProgram NOTIFY shaderProgramChanged)
    Q_PROPERTY(LiRenderState* renderState READ renderState)
    Q_PROPERTY(ShadingModel shadingModel READ shadingModel WRITE setShadingModel NOTIFY shadingModelChanged)
    Q_PROPERTY(AlphaMode alphaMode READ alphaMode WRITE setAlphaMode NOTIFY alphaModeChanged)
    Q_PROPERTY(bool receiveShadow READ receiveShadow WRITE setReceiveShadow NOTIFY receiveShadowChanged)
    Q_PROPERTY(bool castShadow READ castShadow WRITE setCastShadow NOTIFY castShadowChanged)
    Q_PROPERTY(bool bothSided READ bothSided WRITE setBothSided NOTIFY bothSidedChanged)
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(float maskThreshold READ maskThreshold WRITE setMaskThreshold NOTIFY maskThresholdChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(LiTexture* texture READ texture WRITE setTexture NOTIFY textureChanged)
    Q_PROPERTY(LiTexture* batchTable READ batchTable WRITE setBatchTable NOTIFY batchTableChanged)
    Q_PROPERTY(QQmlListProperty<LiParameter> parameters READ qmlParameters)

public:
    enum ShadingModel
    {
        MetallicRoughness,      // default, physically-based rendering (PBR)
        SpecularGlossiness,
        Subsurface,
        Water,
        Unlit,                  // no lighting
        UserShader
    };
    Q_ENUM(ShadingModel)

    enum Parameter {
        DiffuseMap,             // LiTexture
        DiffuseColor,           // QColor

        NormalMap,              // LiTexture
        NormalScale,            // float

        OcclusionMap,           // LiTexture
        OcclusionStrength,      // float

        EmissiveMap,            // QColor
        EmissiveColor,          // QColor

        // MetallicRoughness shading model
        MetallicRoughnessMap,   // LiTexture
        Metallic,               // float
        Roughness,              // float
        Reflectance,            // float
        Anisotropy,             // float

        // Subsurface shading model
        Thickness,              // float
        SubsurfacePower,        // float

        // SpecularGlossiness shading model
        SpecularGlossinessMap,  // LiTexture
        SpecularColor,          // QColor
        Glossiness              // float
    };
    Q_ENUM(Parameter)

    enum AlphaMode
    {
        Opaque,
        Masked,
        Blend
    };
    Q_ENUM(AlphaMode)

    enum Pass
    {
        ColorPass,
        DepthPass,
        ShadowPass,
        GBufferPass
    };
    Q_ENUM(Pass)

    explicit LiMaterial(LiNode *parent = nullptr);
    virtual ~LiMaterial();

    /**
     * basic propertices
     */

    ShadingModel shadingModel() const;
    void setShadingModel(ShadingModel model);

    QColor color() const;
    void setColor(const QColor &color);

    LiTexture *texture() const;
    void setTexture(LiTexture *texture);

    AlphaMode alphaMode() const;
    void setAlphaMode(AlphaMode mode);

    float opacity() const;
    void setOpacity(float opacity);

    bool isTransparent() const;
    void setTransparent(bool transparent);

    float maskThreshold() const;
    void setMaskThreshold(float threshold);

    bool bothSided() const;
    void setBothSided(bool bothSided);

    bool receiveShadow() const;
    void setReceiveShadow(bool receive);

    bool castShadow() const;
    void setCastShadow(bool cast);

    LiTexture *batchTable() const;
    void setBatchTable(LiTexture *batchTable);

    Q_INVOKABLE QVariant parameter(const QString &name) const;
    Q_INVOKABLE void setParameter(const QString &name, const QVariant &value);

    Q_INVOKABLE QVariant parameter(Parameter type) const;
    Q_INVOKABLE void setParameter(Parameter type, const QVariant &value);

    void addParameter(LiParameter *parameter);
    void removeParameter(LiParameter *parameter);
    QVector<LiParameter *> parameters() const;
    QQmlListProperty<LiParameter> qmlParameters();

    // user shaders
    LiShaderProgram *shaderProgram(Pass pass = ColorPass) const;
    void setShaderProgram(LiShaderProgram *shaderProgram, Pass pass = ColorPass);

    /**
     * @brief
     * 返回该材质使用的渲染状态(RenderState)对象
     * @return LiRenderState
     */
    LiRenderState *renderState() const;

    static LiMaterial *fromType(ShadingModel shadingModel);

Q_SIGNALS:
    void shadingModelChanged();
    void colorChanged();
    void textureChanged();
    void opacityChanged();
    void alphaModeChanged();
    void maskThresholdChanged();
    void bothSidedChanged();
    void receiveShadowChanged();
    void castShadowChanged();
    void batchTableChanged();
    void shaderProgramChanged();
    void shaderKeyChanged();

protected:
    explicit LiMaterial(LiMaterialPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiMaterial)
};

#endif // LIMATERIAL_H
