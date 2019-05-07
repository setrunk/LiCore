#ifndef LISHADER_H
#define LISHADER_H

#include "linode.h"

class LiShaderPrivate;

/**
 * @brief
 * LiShader是渲染模块的核心类，负责管理Shader的创建以及编译的版本控制等。
 */
class LICORE_EXPORT LiShader : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiShader(LiNode *parent = nullptr);

    /**
     * @brief
     * 构造函数
     * @param url
     * Shader文件的路径
     * @param parent
     */
    explicit LiShader(const QUrl &url, LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    ~LiShader();

    /**
     * @brief
     * 返回创建该对象的文件路径
     * @return QUrl
     */
    QUrl url() const;

    /**
     * @brief
     * 设置该对象的文件路径
     * @param url
     */
    void setUrl(const QUrl &url);

    /**
     * @brief
     * 该Shader编译的版本，比如'300 core', '430'等
     * @return QByteArray
     */
    QByteArray version() const;

    /**
     * @brief
     * 设置Shader编译的版本，如果没有设置版本号，默认为'430'
     * @param version
     */
    void setVersion(const QByteArray &version);

    /**
     * @brief
     * 返回该Shader的源码
     * @return QByteArray
     */
    QByteArray sourceCode();

    /**
     * @brief
     * 添加预编译宏定义
     * @param name
     */
    Q_INVOKABLE void addDefine(const QString &define);

    /**
     * @brief
     * 设置多个预编译宏定义
     * @param defines
     */
    Q_INVOKABLE void setDefines(const QStringList &defines);

    /**
     * @brief
     * 设置多个带定义值的预编译宏定义
     * @param values
     */
    Q_INVOKABLE void setDefineValues(const QVariantMap &values);

    /**
     * @brief
     * 返回所有预编译宏定义合集
     * @return QStringList
     */
    Q_INVOKABLE QStringList defines() const;

    /**
     * @brief
     * 创建LiShader对象
     * @param url
     * Shader文件的路径
     * @param defines
     * 预编译宏定义
     * @return LiShader
     */
    Q_INVOKABLE static LiShader *create(const QUrl &url, const QStringList &defines = QStringList());

    /**
     * @brief
     * 返回全屏顶底处理Shader
     * @return LiShader
     */
    Q_INVOKABLE static LiShader *viewportQuadVS();

    /**
     * @brief
     * 解析Shader文件，比如处理include行，并返回源码结果
     * @param sourceUrl
     * Shader文件的路径
     * @return QByteArray
     */
    Q_INVOKABLE static QByteArray loadSource(const QUrl &sourceUrl);

Q_SIGNALS:
    /**
     * @brief
     * Shader文件路径改变时，发出该信号
     * @param url
     */
    void urlChanged(const QUrl &url);

    /**
     * @brief
     * Shader编译版本改变时，发出该信号
     * @param version
     */
    void versionChanged(const QByteArray &version);

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiShader(LiShaderPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiShader)
};

#endif // LISHADER_H
