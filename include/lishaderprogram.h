#ifndef LISHADERPROGRAM_H
#define LISHADERPROGRAM_H

#include "linode.h"

class LiShader;
class LiShaderProgramPrivate;

/**
 * @brief
 * LiShaderProgram是渲染模块的核心类，负责gpu渲染的方式，一般情况下由VertexShader和FragmentShader组成。
 */
class LICORE_EXPORT LiShaderProgram : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(LiShader* vertexShader READ vertexShader WRITE setVertexShader NOTIFY vertexShaderChanged)
    Q_PROPERTY(LiShader* tessellationControlShader READ tessellationControlShader WRITE setTessellationControlShader NOTIFY tessellationControlShaderChanged)
    Q_PROPERTY(LiShader* tessellationEvaluationShader READ tessellationEvaluationShader WRITE setTessellationEvaluationShader NOTIFY tessellationEvaluationShaderChanged)
    Q_PROPERTY(LiShader* geometryShader READ geometryShader WRITE setGeometryShader NOTIFY geometryShaderChanged)
    Q_PROPERTY(LiShader* fragmentShader READ fragmentShader WRITE setFragmentShader NOTIFY fragmentShaderChanged)
    Q_PROPERTY(LiShader* computeShader READ computeShader WRITE setComputeShader NOTIFY computeShaderChanged)
    Q_PROPERTY(QByteArray vertexShaderCode READ vertexShaderCode WRITE setVertexShaderCode NOTIFY vertexShaderCodeChanged)
    Q_PROPERTY(QByteArray tessellationControlShaderCode READ tessellationControlShaderCode WRITE setTessellationControlShaderCode NOTIFY tessellationControlShaderCodeChanged)
    Q_PROPERTY(QByteArray tessellationEvaluationShaderCode READ tessellationEvaluationShaderCode WRITE setTessellationEvaluationShaderCode NOTIFY tessellationEvaluationShaderCodeChanged)
    Q_PROPERTY(QByteArray geometryShaderCode READ geometryShaderCode WRITE setGeometryShaderCode NOTIFY geometryShaderCodeChanged)
    Q_PROPERTY(QByteArray fragmentShaderCode READ fragmentShaderCode WRITE setFragmentShaderCode NOTIFY fragmentShaderCodeChanged)
    Q_PROPERTY(QByteArray computeShaderCode READ computeShaderCode WRITE setComputeShaderCode NOTIFY computeShaderCodeChanged)

public:
    /**
     * @brief
     * Shader类型
     */
    enum ShaderType {
        Vertex = 0,
        Fragment,
        TessellationControl,
        TessellationEvaluation,
        Geometry,
        Compute
    };
    Q_ENUM(ShaderType) // LCOV_EXCL_LINE

    /**
     * @brief
     * 内部标识
     */
    enum Flag
    {
        Lit             = (1 << 0),
        DiffuseMap      = (1 << 1),
        NormalMap       = (1 << 2),
        Reflection      = (1 << 3),
        TextureArray    = (1 << 4),
        AlphaTest       = (1 << 5),
        BatchTable      = (1 << 6),
        Instanced       = (1 << 7),
        ClipPlanes      = (1 << 8),
        ClipVolumes     = (1 << 9),
        ShadowPass      = (1 << 10),
        DepthPass       = (1 << 11),
        GBufferPass     = (1 << 12)
    };

    /**
     * @brief
     * 标准Shader类型，可通过类型创建内置标准Shader
     */
    enum StandardShader {
        UnlitColor = 0,
        UnlitTexture,
        UnlitTextureAlpha,
        UnlitTextureArray,
        UnlitTextureArrayAlpha,
        LitColor,
        LitTexture,
        LitTextureAlpha,
        LitTextureArray,
        LitTextureArrayAlpha
    };
    Q_ENUM(StandardShader) // LCOV_EXCL_LINE

    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiShaderProgram(LiNode *parent = 0);

    /**
     * @brief
     * 构造函数
     * @param vs
     * 顶点处理Shader
     * @param fs
     * 像素处理Shader
     * @param parent
     */
    LiShaderProgram(LiShader *vs, LiShader *fs, LiNode *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiShaderProgram();

    /**
     * @brief
     * 返回顶点Shader对象
     * @return LiShader
     */
    LiShader* vertexShader() const;

    /**
     * @brief
     * 返回像素Shader对象
     * @return LiShader
     */
    LiShader* fragmentShader() const;

    /**
     * @brief
     * 返回tessellationControlShader对象
     * @return LiShader
     */
    LiShader* tessellationControlShader() const;

    /**
     * @brief
     * 返回tessellationEvaluationShader对象
     * @return LiShader
     */
    LiShader* tessellationEvaluationShader() const;

    /**
     * @brief
     * 返回几何Shader对象
     * @return LiShader
     */
    LiShader* geometryShader() const;

    /**
     * @brief
     * 返回计算Shader对象
     * @return LiShader
     */
    LiShader* computeShader() const;

    /**
     * @brief
     * 返回顶点Shader的源码
     * @return QByteArray
     */
    QByteArray vertexShaderCode() const;

    /**
     * @brief
     * 返回像素Shader的源码
     * @return QByteArray
     */
    QByteArray fragmentShaderCode() const;

    /**
     * @brief
     * 返回tessellationControlShader的源码
     * @return QByteArray
     */
    QByteArray tessellationControlShaderCode() const;

    /**
     * @brief
     * 返回tessellationEvaluationShader的源码
     * @return QByteArray
     */
    QByteArray tessellationEvaluationShaderCode() const;

    /**
     * @brief
     * 返回几何Shader的源码
     * @return QByteArray
     */
    QByteArray geometryShaderCode() const;

    /**
     * @brief
     * 返回计算Shader的源码
     * @return QByteArray
     */
    QByteArray computeShaderCode() const;

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return LiNodeChangeBasePtr
     */
    LiNodeChangeBasePtr createChangePtr() const Q_DECL_OVERRIDE;

    /**
     * @brief
     * 通过路径和宏定义创建LiShaderProgram对象
     * @param vsUrl
     * 顶点Shader的文件路径
     * @param fsUrl
     * 像素Shader的文件路径
     * @param defines
     * 预编译的宏定义
     * @return LiShaderProgram
     */
    static LiShaderProgram *create(const QUrl &vsUrl, const QUrl &fsUrl, const QStringList &defines = QStringList());

    /**
     * @brief
     * 通过路径和宏定义创建计算ShaderProgram对象
     * @param url
     * 计算Shader的文件路径
     * @param defines
     * 预编译的宏定义
     * @return LiShaderProgram
     */
    static LiShaderProgram *createCompute(const QUrl &url, const QStringList &defines = QStringList());

    /**
     * @brief
     * 通过源码创建LiShaderProgram对象
     * @param vs
     * 顶点Shader的源码
     * @param fs
     * 像素Shader的源码
     * @return LiShaderProgram
     */
    static LiShaderProgram *createFromText(const QByteArray &vs, const QByteArray &fs);

    /**
     * @brief
     * 通过文件路径创建全屏处理ShaderProgram对象
     * @param url
     * 全屏像素处理Shader的文件路径
     * @param defines
     * 预编译的宏定义
     * @return LiShaderProgram
     */
    static LiShaderProgram *createViewportQuadShader(const QUrl &url, const QStringList &defines = QStringList());

    /**
     * @brief
     * 创建内置标准的LiShaderProgram对象
     * @param type
     * ShaderProgram的内置类型
     * @return LiShaderProgram
     */
    static LiShaderProgram *fromType(StandardShader type);

    /**
     * @brief
     * 通过标识创建内置标准的LiShaderProgram对象
     * @param flags
     * ShaderProgram的内置标识
     * @return LiShaderProgram
     */
    static LiShaderProgram *fromFlags(uint flags);

    /**
     * @brief
     * 返回之前缓存的关键字key的LiShaderProgram对象
     * @param key
     * 缓存关键字
     * @return LiShaderProgram
     */
    static LiShaderProgram *fromCache(const QString &key);

    /**
     * @brief
     * 缓存关键字key的LiShaderProgram对象
     * @param key
     * 缓存关键字
     * @param shaderProgram
     */
    static void cacheShaderProgram(const QString &key, LiShaderProgram *shaderProgram);

public Q_SLOTS:
    /**
     * @brief
     * 设置顶点Shader对象
     * @param shader
     */
    void setVertexShader(LiShader *shader);

    /**
     * @brief
     * 设置像素Shader对象
     * @param shader
     */
    void setFragmentShader(LiShader *shader);

    /**
     * @brief
     * 设置TessellationControlShader对象
     * @param shader
     */
    void setTessellationControlShader(LiShader *shader);

    /**
     * @brief
     * 设置TessellationEvaluationShader对象
     * @param shader
     */
    void setTessellationEvaluationShader(LiShader *shader);

    /**
     * @brief
     * 设置几何Shader对象
     * @param shader
     */
    void setGeometryShader(LiShader *shader);

    /**
     * @brief
     * 设置计算Shader对象
     * @param shader
     */
    void setComputeShader(LiShader *shader);

    /**
     * @brief
     * 设置顶点Shader源码
     * @param vertexShaderCode
     */
    void setVertexShaderCode(const QByteArray &vertexShaderCode);

    /**
     * @brief
     * 设置像素Shader源码
     * @param fragmentShaderCode
     */
    void setFragmentShaderCode(const QByteArray &fragmentShaderCode);

    /**
     * @brief
     * 设置TessellationControlShader源码
     * @param tessellationControlShaderCode
     */
    void setTessellationControlShaderCode(const QByteArray &tessellationControlShaderCode);

    /**
     * @brief
     * 设置TessellationEvaluationShader源码
     * @param tessellationEvaluationShaderCode
     */
    void setTessellationEvaluationShaderCode(const QByteArray &tessellationEvaluationShaderCode);

    /**
     * @brief
     * 设置几何Shader源码
     * @param geometryShaderCode
     */
    void setGeometryShaderCode(const QByteArray &geometryShaderCode);

    /**
     * @brief
     * 设置计算Shader源码
     * @param computeShaderCode
     */
    void setComputeShaderCode(const QByteArray &computeShaderCode);

    Q_INVOKABLE static QByteArray loadSource(const QUrl &sourceUrl);

signals:
    /**
     * @brief
     * 顶点Shader对象改变时，发出该信号
     * @param shader
     */
    void vertexShaderChanged(LiShader *shader);

    /**
     * @brief
     * 像素Shader对象改变时，发出该信号
     * @param shader
     */
    void fragmentShaderChanged(LiShader *shader);

    /**
     * @brief
     * tessellationControlShader对象改变时，发出该信号
     * @param shader
     */
    void tessellationControlShaderChanged(LiShader *shader);

    /**
     * @brief
     * tessellationEvaluationShader对象改变时，发出该信号
     * @param shader
     */
    void tessellationEvaluationShaderChanged(LiShader *shader);

    /**
     * @brief
     * 几何Shader对象改变时，发出该信号
     * @param shader
     */
    void geometryShaderChanged(LiShader *shader);

    /**
     * @brief
     * 计算Shader对象改变时，发出该信号
     * @param shader
     */
    void computeShaderChanged(LiShader *shader);

    /**
     * @brief
     * 顶点Shader源码改变时，发出该信号
     * @param vertexShaderCode
     */
    void vertexShaderCodeChanged(const QByteArray &vertexShaderCode);

    /**
     * @brief
     * 像素Shader源码改变时，发出该信号
     * @param fragmentShaderCode
     */
    void fragmentShaderCodeChanged(const QByteArray &fragmentShaderCode);

    /**
     * @brief
     * tessellationControlShader源码改变时，发出该信号
     * @param tessellationControlShaderCode
     */
    void tessellationControlShaderCodeChanged(const QByteArray &tessellationControlShaderCode);

    /**
     * @brief
     * tessellationEvaluationShader源码改变时，发出该信号
     * @param tessellationEvaluationShaderCode
     */
    void tessellationEvaluationShaderCodeChanged(const QByteArray &tessellationEvaluationShaderCode);

    /**
     * @brief
     * 几何Shader源码改变时，发出该信号
     * @param geometryShaderCode
     */
    void geometryShaderCodeChanged(const QByteArray &geometryShaderCode);

    /**
     * @brief
     * 计算Shader源码改变时，发出该信号
     * @param computeShaderCode
     */
    void computeShaderCodeChanged(const QByteArray &computeShaderCode);

private:
    Q_DECLARE_PRIVATE(LiShaderProgram)
};

#endif // LISHADERPROGRAM_H
