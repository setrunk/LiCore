#ifndef LIRENDERTARGET_H
#define LIRENDERTARGET_H

#include "linode.h"

class LiRenderTargetOutput;
class LiRenderTargetPrivate;

/**
 * @brief
 * LiRenderTarget是对OpenGL里面的Framebuffer的封装，是由多个LiRenderTargetOutput渲染输出组成的渲染目标。
 * 而LiRenderTargetOutput是对OpenGL里面的Attachment的封装。
 */
class LICORE_EXPORT LiRenderTarget : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<LiRenderTargetOutput> outputs READ qmlOutputs)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiRenderTarget(LiNode *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    ~LiRenderTarget();

    /**
     * @brief
     * 添加LiRenderTargetOutput渲染输出对象
     * @param output
     */
    void addOutput(LiRenderTargetOutput *output);

    /**
     * @brief
     * 移除LiRenderTargetOutput渲染输出对象
     * @param output
     */
    void removeOutput(LiRenderTargetOutput *output);

    /**
     * @brief
     * 返回所有的LiRenderTargetOutput渲染输出合集
     * @return QVector<LiRenderTargetOutput *>
     */
    QVector<LiRenderTargetOutput *> outputs() const;

    /**
     * @brief
     * 返回渲染目标的大小尺寸
     * @return QSize
     */
    QSize size() const;

    /**
     * @brief
     * 调整渲染目标的大小尺寸，内部所有的LiRenderTargetOutput渲染输出都会调整到同样的尺寸
     * @param size
     */
    void resizeDrawBuffers(const QSize &size);

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return QQmlListProperty<LiRenderTargetOutput>
     */
    QQmlListProperty<LiRenderTargetOutput> qmlOutputs();

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return LiNodeChangeBasePtr
     */
    LiNodeChangeBasePtr createChangePtr() const;

private:
    Q_DECLARE_PRIVATE(LiRenderTarget)
};

#endif // LIRENDERTARGET_H
