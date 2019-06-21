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
    Q_PROPERTY(bool bothSided READ bothSided WRITE setBothSided NOTIFY bothSidedChanged)
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(float maskThreshold READ maskThreshold WRITE setMaskThreshold NOTIFY maskThresholdChanged)
    Q_PROPERTY(float metallic READ metallic WRITE setMetallic NOTIFY metallicChanged)
    Q_PROPERTY(float roughness READ roughness WRITE setRoughness NOTIFY roughnessChanged)
    Q_PROPERTY(float normalScale READ normalScale WRITE setNormalScale NOTIFY normalScaleChanged)
    Q_PROPERTY(float occlusionStrength READ occlusionStrength WRITE setOcclusionStrength NOTIFY occlusionStrengthChanged)
    Q_PROPERTY(float specularFactor READ specularFactor WRITE setSpecularFactor NOTIFY specularFactorChanged)
    Q_PROPERTY(float glossinessFactor READ glossinessFactor WRITE setGlossinessFactor NOTIFY glossinessFactorChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor emissive READ emissive WRITE setEmissive NOTIFY emissiveChanged)
    Q_PROPERTY(LiTexture* texture READ texture WRITE setTexture NOTIFY textureChanged)
    Q_PROPERTY(LiTexture* normalMap READ normalMap WRITE setNormalMap NOTIFY normalMapChanged)
    Q_PROPERTY(LiTexture* metallicRoughnessMap READ metallicRoughnessMap WRITE setMetallicRoughnessMap NOTIFY metallicRoughnessMapChanged)
    Q_PROPERTY(LiTexture* occlusionMap READ occlusionMap WRITE setOcclusionMap NOTIFY occlusionMapChanged)
    Q_PROPERTY(LiTexture* emissiveMap READ emissiveMap WRITE setEmissiveMap NOTIFY emissiveMapChanged)
    Q_PROPERTY(LiTexture* batchTable READ batchTable WRITE setBatchTable NOTIFY batchTableChanged)
    Q_PROPERTY(QQmlListProperty<LiParameter> parameters READ qmlParameters)
public:

    /**
     * @brief
     * 创建标准材质的类型
     */
    enum Type
    {
        UnlitColor, // 不接受光照，只有颜色
        UnlitTexture, // 不接受光照，带纹理贴图
        UnlitTextureAlpha, // 不接受光照，带纹理贴图，Alpha透空
        UnlitTextureArray, // 不接受光照，带纹理贴图，纹理采用纹理阵列
        UnlitTextureArrayAlpha, // 不接受光照，带纹理贴图，纹理采用纹理阵列，Alpha透空
        LitColor, // 接受光照，只有颜色
        LitTexture, // 接受光照，带纹理贴图
        LitTextureAlpha, // 接受光照，带纹理贴图，Alpha透空
        LitTextureArray, // 接受光照，带纹理贴图，纹理采用纹理阵列
        LitTextureArrayAlpha, // 接受光照，带纹理贴图，纹理采用纹理阵列，Alpha透空
        Water
    };
    Q_ENUM(Type)

    enum ShadingModel
    {
        Unlit,
        Lit,   // default, only lit color or texture
        PBR,   // physically-based rendering
        Glass,
        Cloth,
        Subsurface,
        SpecularGlossiness, // legacy, only for gltf specularGlossiness material
        UserShader
    };
    Q_ENUM(ShadingModel)

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
    */
    ShadingModel shadingModel() const;
    void setShadingModel(ShadingModel model);

    /**
     * basic propertices
     */
    LiTexture *texture() const;
    void setTexture(LiTexture *texture);
    QColor color() const;
    void setColor(const QColor &color);
    float opacity() const;
    void setOpacity(float opacity);
    bool isTransparent() const;
    void setTransparent(bool transparent);
    AlphaMode alphaMode() const;
    void setAlphaMode(AlphaMode mode);
    float maskThreshold() const;
    void setMaskThreshold(float threshold);
    bool bothSided() const;
    void setBothSided(bool bothSided);
    bool receiveShadow() const;
    void setReceiveShadow(bool shadow);
    QColor postLightingColor() const;
    void setPostLightingColor(const QColor &color);

    /**
     * PBR propertices
     */
    float metallic() const;
    void setMetallic(float metallic);
    float roughness() const;
    void setRoughness(float roughness);
    float reflectance() const;
    void setReflectance(float reflectance);
    float anisotropy() const;
    void setAnisotropy(float anisotropy);
    LiTexture *metallicRoughnessMap() const;
    void setMetallicRoughnessMap(LiTexture *map);
    LiTexture *normalMap() const;
    void setNormalMap(LiTexture *map);
    float normalScale() const;
    void setNormalScale(float scale);
    LiTexture *occlusionMap() const;
    void setOcclusionMap(LiTexture *map);
    float occlusionStrength() const;
    void setOcclusionStrength(float strength);
    LiTexture *emissiveMap() const;
    void setEmissiveMap(LiTexture *map);
    QColor emissive() const;
    void setEmissive(const QColor &emissive);

    /**
     * specularGlossiness
     */
    float specularFactor() const;
    void setSpecularFactor(float factor);
    float glossinessFactor() const;
    void setGlossinessFactor(float factor);

    LiTexture *reflectionMap() const;
    void setReflectionMap(LiTexture *reflectionMap);
    float reflectionAmount() const;
    void setReflectionAmount(float reflectionAmount);

    LiTexture *batchTable() const;
    void setBatchTable(LiTexture *batchTable);

    bool alphaTest() const;
    void setAlphaTest(bool alphaTest);

    bool instanced() const;
    void setInstanced(bool instanced);

    LiShaderProgram *shaderProgram(Pass pass = ColorPass) const;
    void setShaderProgram(LiShaderProgram *shaderProgram, Pass pass = ColorPass);

    /**
     * @brief
     * 返回RenderState对象
     * @return LiRenderState
     */
    LiRenderState *renderState() const;

    void setParameter(const QString &name, const QVariant &value);
    void addParameter(const QString &name, const QVariant &value);
    void addParameter(LiParameter *parameter);
    void removeParameter(LiParameter *parameter);
    LiParameter *parameter(const QString &name) const;
    QVector<LiParameter *> parameters() const;
    QQmlListProperty<LiParameter> qmlParameters();

    /**
     * @brief
     * 创建标准材质
     * @param type
     * 标准材质类型
     * @return LiMaterial
     */
    Q_INVOKABLE static LiMaterial *fromType(Type type);

Q_SIGNALS:
    void shadingModelChanged();
    void colorChanged();
    void textureChanged();
    void opacityChanged();
    void alphaModeChanged();
    void maskThresholdChanged();
    void receiveShadowChanged();
    void postLightingColorChanged();
    void metallicChanged();
    void roughnessChanged();
    void reflectanceChanged();
    void anisotropyChanged();
    void metallicRoughnessMapChanged();
    void normalMapChanged();
    void normalScaleChanged();
    void occlusionMapChanged();
    void occlusionStrengthChanged();
    void emissiveMapChanged();
    void emissiveChanged();
    void specularFactorChanged();
    void glossinessFactorChanged();
    void bothSidedChanged();
    void instancedChanged();
    void batchTableChanged();
    void shaderProgramChanged();

protected:
    explicit LiMaterial(LiMaterialPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiMaterial)
};

#endif // LIMATERIAL_H
