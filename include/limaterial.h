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
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(LiTexture* texture READ texture WRITE setTexture NOTIFY textureChanged)
    Q_PROPERTY(LiTexture* normalMap READ normalMap WRITE setNormalMap NOTIFY normalMapChanged)
    Q_PROPERTY(LiTexture* reflectionMap READ reflectionMap WRITE setReflectionMap NOTIFY reflectionMapChanged)
    Q_PROPERTY(LiTexture* batchTable READ batchTable WRITE setBatchTable NOTIFY batchTableChanged)
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)
    Q_PROPERTY(float shininess READ shininess WRITE setShininess NOTIFY shininessChanged)
    Q_PROPERTY(float emissive READ emissive WRITE setEmissive NOTIFY emissiveChanged)
    Q_PROPERTY(float reflectionAmount READ reflectionAmount WRITE setReflectionAmount NOTIFY reflectionAmountChanged)
    Q_PROPERTY(bool lit READ lit WRITE setLit NOTIFY litChanged)
    Q_PROPERTY(bool alphaTest READ alphaTest WRITE setAlphaTest NOTIFY alphaTestChanged)
    Q_PROPERTY(bool instanced READ instanced WRITE setInstanced NOTIFY instancedChanged)
    Q_PROPERTY(bool transparent READ isTransparent WRITE setTransparent NOTIFY transparentChanged)
    Q_PROPERTY(bool bothSided READ isBothSided WRITE setBothSided NOTIFY bothSidedChanged)
    Q_PROPERTY(QQmlListProperty<LiParameter> parameters READ qmlParameters)
public:
    /**
     * @brief
     * 标准材质的标识
     */
    enum Flag
    {
        Lit             = (1 << 0), // 接受光照
        DiffuseMap      = (1 << 1), // 纹理贴图
        NormalMap       = (1 << 2), // 法线贴图
        Reflection      = (1 << 3), // 反射
        TextureArray    = (1 << 4), // 纹理阵列
        AlphaTest       = (1 << 5), // Alpha透空
        BatchTable      = (1 << 6), // BatchTable
        Instanced       = (1 << 7) // 多实例
    };
    Q_FLAG(Flag)

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

    /**
     * @brief
     * 渲染Pass
     */
    enum Pass
    {
        ColorPass,
        DepthPass,
        ShadowPass,
        GBufferPass
    };
    Q_ENUM(Pass)

    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiMaterial(LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiMaterial();

    /**
     * @brief
     * 返回材质的颜色参数
     * @return QColor
     */
    QColor color() const;

    /**
     * @brief
     * 设置材质的颜色参数
     * @param color
     */
    void setColor(const QColor &color);

    /**
     * @brief
     * 返回材质的纹理参数
     * @return LiTexture
     */
    LiTexture *texture() const;

    /**
     * @brief
     * 设置材质的纹理参数
     * @param texture
     */
    void setTexture(LiTexture *texture);

    /**
     * @brief
     * 返回材质的法线贴图参数
     * @return LiTexture
     */
    LiTexture *normalMap() const;

    /**
     * @brief
     * 设置材质的法线贴图参数
     * @param normalMap
     */
    void setNormalMap(LiTexture *normalMap);

    /**
     * @brief
     * 返回材质的反射贴图参数
     * @return LiTexture
     */
    LiTexture *reflectionMap() const;

    /**
     * @brief
     * 设置材质的反射贴图参数
     * @param reflectionMap
     */
    void setReflectionMap(LiTexture *reflectionMap);

    /**
     * @brief
     * 返回材质的BatchTable参数
     * @return LiTexture
     */
    LiTexture *batchTable() const;

    /**
     * @brief
     * 设置材质的BatchTable参数
     * @param batchTable
     */
    void setBatchTable(LiTexture *batchTable);

    /**
     * @brief
     * 返回材质的Shininess高光参数
     * @return float
     */
    float shininess() const;

    /**
     * @brief
     * 设置材质的Shininess高光参数
     * @param shininess
     */
    void setShininess(float shininess);

    /**
     * @brief
     * 返回材质的Emissive自发光参数
     * 0.0: 不发光，1.0: 100%自发光
     * @return float
     */
    float emissive() const;

    /**
     * @brief
     * 设置材质的Emissive自发光参数
     * @param emissive
     */
    void setEmissive(float emissive);

    /**
     * @brief
     * 返回材质的Opacity不透明性参数
     * @return float
     * 0.0: 完全透明，1.0: 完全不透明
     */
    float opacity() const;

    /**
     * @brief
     * 设置材质的Opacity不透明性参数
     * @param opacity
     */
    void setOpacity(float opacity);

    /**
     * @brief
     * 返回材质的反射强度参数
     * @return float
     * 0.0: 不反射，1.0: 100%反射
     */
    float reflectionAmount() const;

    /**
     * @brief
     * 设置材质的反射强度参数
     * @param reflectionAmount
     */
    void setReflectionAmount(float reflectionAmount);

    /**
     * @brief
     * 返回材质是否接受光照
     * @return bool
     */
    bool lit() const;

    /**
     * @brief
     * 设置材质是否接受光照
     * @param lit
     */
    void setLit(bool lit);

    /**
     * @brief
     * 返回材质是否Alpha透空
     * @return bool
     */
    bool alphaTest() const;

    /**
     * @brief
     * 设置材质是否Alpha透空
     * @param alphaTest
     */
    void setAlphaTest(bool alphaTest);

    /**
     * @brief
     * 返回材质是否带Instance标记
     * @return bool
     */
    bool instanced() const;

    /**
     * @brief
     * 设置材质是否带Instance标记
     * @param instanced
     */
    void setInstanced(bool instanced);

    // shader program
    /**
     * @brief
     * 返回材质的ShaderProgram
     * @param pass
     * 哪种类型的ShaderProgram
     * @return LiShaderProgram
     */
    LiShaderProgram *shaderProgram(Pass pass = ColorPass) const;
    /**
     * @brief
     * 设置材质的ShaderProgram
     * @param shaderProgram
     * 新的ShaderProgram
     * @param pass
     * 哪种类型的ShaderProgram
     */
    void setShaderProgram(LiShaderProgram *shaderProgram, Pass pass = ColorPass);

    /**
     * @brief
     * 是否是双面材质
     * @return bool
     */
    bool isBothSided() const;

    /**
     * @brief
     * 设置是否是双面材质
     * @param bothSided
     */
    void setBothSided(bool bothSided);

    /**
     * @brief
     * 是否是透明材质
     * @return bool
     */
    bool isTransparent() const;

    /**
     * @brief
     * 设置是否是透明材质
     * @param transparent
     */
    void setTransparent(bool transparent);

    /**
     * @brief
     * 返回RenderState对象
     * @return LiRenderState
     */
    LiRenderState *renderState() const;

    /**
     * @brief
     * 设置材质参数，如果该名称的参数不存在，会自动创建参数
     * @param name
     * 参数名称
     * @param value
     * 参数值
     */
    void setParameter(const QString &name, const QVariant &value);

    /**
     * @brief
     * 添加材质参数
     * @param name
     * 参数名称
     * @param value
     * 参数值
     */
    void addParameter(const QString &name, const QVariant &value);

    /**
     * @brief
     * 添加材质参数
     * @param parameter
     */
    void addParameter(LiParameter *parameter);

    /**
     * @brief
     * 移除材质参数，parameter对象被移除后不会自动删除释放，需要手动删除释放
     * @param parameter
     */
    void removeParameter(LiParameter *parameter);

    /**
     * @brief
     * 返回名称为name的参数对象
     * @param name
     * 参数名称
     * @return LiParameter
     */
    LiParameter *parameter(const QString &name) const;

    /**
     * @brief
     * 返回所有参数合集
     * @return QVector<LiParameter *>
     */
    QVector<LiParameter *> parameters() const;

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return QQmlListProperty<LiParameter>
     */
    QQmlListProperty<LiParameter> qmlParameters();

    /**
     * @brief
     * 创建标准材质
     * @param type
     * 标准材质类型
     * @return LiMaterial
     */
    Q_INVOKABLE static LiMaterial *fromType(Type type);

    /**
     * @brief
     * 根据标识创建标准材质
     * @param flags
     * 创建的标识，参见Flag说明
     * @return LiMaterial
     */
    Q_INVOKABLE static LiMaterial *fromFlags(uint flags);

    /**
     * @brief
     * 根据type类型，创建LiShaderProgram对象
     * @param type
     * 创建哪种类型的LiShaderProgram
     * @return LiShaderProgram
     */
    Q_INVOKABLE static LiShaderProgram *shaderProgramFromType(Type type);

Q_SIGNALS:
    /**
     * @brief
     * color属性改变时，发出该信号
     */
    void colorChanged();

    /**
     * @brief
     * texture属性改变时，发出该信号
     */
    void textureChanged();

    /**
     * @brief
     * normalMap属性改变时，发出该信号
     */
    void normalMapChanged();

    /**
     * @brief
     * reflectionMap属性改变时，发出该信号
     */
    void reflectionMapChanged();

    /**
     * @brief
     * batchTable属性改变时，发出该信号
     */
    void batchTableChanged();

    /**
     * @brief
     * shininess属性改变时，发出该信号
     */
    void shininessChanged();

    /**
     * @brief
     * emissive属性改变时，发出该信号
     */
    void emissiveChanged();

    /**
     * @brief
     * opacity属性改变时，发出该信号
     */
    void opacityChanged();

    /**
     * @brief
     * transparent属性改变时，发出该信号
     */
    void transparentChanged();

    /**
     * @brief
     * bothSided属性改变时，发出该信号
     */
    void bothSidedChanged();

    /**
     * @brief
     * reflectionAmount属性改变时，发出该信号
     */
    void reflectionAmountChanged();

    /**
     * @brief
     * lit属性改变时，发出该信号
     */
    void litChanged();

    /**
     * @brief
     * alphaTest属性改变时，发出该信号
     */
    void alphaTestChanged();

    /**
     * @brief
     * instanced属性改变时，发出该信号
     */
    void instancedChanged();

    /**
     * @brief
     * shaderProgram属性改变时，发出该信号
     */
    void shaderProgramChanged();

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiMaterial(LiMaterialPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiMaterial)
};

#endif // LIMATERIAL_H
