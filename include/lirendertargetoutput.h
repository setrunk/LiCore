#ifndef LIRENDERTARGETOUTPUT_H
#define LIRENDERTARGETOUTPUT_H

#include "linode.h"
#include "litexture.h"

class LiRenderTargetOutputPrivate;

/**
 * @brief
 * LiRenderTargetOutput渲染输出，是对OpenGL里面的Attachment的封装，
 */
class LICORE_EXPORT LiRenderTargetOutput : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(AttachmentPoint attachmentPoint READ attachmentPoint WRITE setAttachmentPoint NOTIFY attachmentPointChanged)
    Q_PROPERTY(LiTexture *texture READ texture WRITE setTexture NOTIFY textureChanged)
    Q_PROPERTY(int mipLevel READ mipLevel WRITE setMipLevel NOTIFY mipLevelChanged)
    Q_PROPERTY(int layer READ layer WRITE setLayer NOTIFY layerChanged)
    Q_PROPERTY(LiTexture::CubeMapFace face READ face WRITE setFace NOTIFY faceChanged)
    Q_PROPERTY(BufferType bufferType READ bufferType WRITE setBufferType NOTIFY bufferTypeChanged)
    Q_PROPERTY(QColor clearColor READ clearColor WRITE setClearColor NOTIFY clearColorChanged)
    Q_PROPERTY(float clearDepthValue READ clearDepthValue WRITE setClearDepthValue NOTIFY clearDepthValueChanged)
    Q_PROPERTY(int clearStencilValue READ clearStencilValue WRITE setClearStencilValue NOTIFY clearStencilValueChanged)

public:
    /**
     * @brief
     * OpenGL渲染管线的渲染输出点
     */
    enum AttachmentPoint {
        Color0 = 0,
        Color1,
        Color2,
        Color3,
        Color4,
        Color5,
        Color6,
        Color7,
        Color8,
        Color9,
        Color10,
        Color11,
        Color12,
        Color13,
        Color14,
        Color15,
        Depth,
        Stencil,
        DepthStencil
    };
    Q_ENUM(AttachmentPoint) // LCOV_EXCL_LINE

    /**
     * @brief
     * 渲染缓存类型
     */
    enum BufferType {
        None = 0,
        ColorBuffer = (1 << 0),
        DepthBuffer = (1 << 1),
        StencilBuffer = (1 << 2),
        DepthStencilBuffer = DepthBuffer | StencilBuffer,
        ColorDepthBuffer = ColorBuffer | DepthBuffer,
        ColorDepthStencilBuffer = ColorBuffer | DepthStencilBuffer,
        AllBuffers = 0xFFFFFFFF
    };
    Q_ENUM(BufferType)
    Q_DECLARE_FLAGS(BufferTypeFlags, BufferType)

    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiRenderTargetOutput(LiNode *parent = nullptr);

    /**
     * @brief
     * 构造函数
     * @param tex
     * 内部的离线渲染纹理
     * @param point
     * OpenGL渲染管线的渲染输出点
     * @param parent
     */
    LiRenderTargetOutput(LiTexture *tex, AttachmentPoint point, LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    ~LiRenderTargetOutput();

    /**
     * @brief
     * 返回OpenGL渲染管线的渲染输出点
     * @return AttachmentPoint
     */
    AttachmentPoint attachmentPoint() const;

    /**
     * @brief
     * 设置OpenGL渲染管线的渲染输出点
     * @param attachmentPoint
     */
    void setAttachmentPoint(AttachmentPoint attachmentPoint);

    /**
     * @brief
     * 返回内部的离线渲染纹理
     * @return LiTexture
     */
    LiTexture *texture() const;

    /**
     * @brief
     * 设置内部的离线渲染纹理
     * @param texture
     */
    void setTexture(LiTexture *texture);

    /**
     * @brief
     * 返回内部的离线渲染纹理采用哪一层MipMap链
     * @return int
     */
    int mipLevel() const;

    /**
     * @brief
     * 设置内部的离线渲染纹理采用哪一层MipMap链
     * @param level
     */
    void setMipLevel(int level);

    /**
     * @brief
     * 返回内部的离线渲染纹理采用哪一层2D纹理（针对3D纹理）
     * @return int
     */
    int layer() const;

    /**
     * @brief
     * 设置内部的离线渲染纹理采用哪一层2D纹理（针对3D纹理）
     * @param layer
     */
    void setLayer(int layer);

    /**
     * @brief
     * 返回内部的离线渲染纹理采用哪一面的2D纹理（针对CubeMap纹理）
     * @return LiTexture::CubeMapFace
     */
    LiTexture::CubeMapFace face() const;

    /**
     * @brief
     * 设置内部的离线渲染纹理采用哪一面的2D纹理（针对CubeMap纹理）
     * @param face
     */
    void setFace(LiTexture::CubeMapFace face);

    /**
     * @brief
     * 返回该渲染输出的缓存类型
     * @return BufferType
     */
    BufferType bufferType() const;

    /**
     * @brief
     * 设置该渲染输出的缓存类型
     * @param bufferType
     */
    void setBufferType(BufferType bufferType);

    /**
     * @brief
     * 返回进行Clear操作时采用的颜色值
     * @return QColor
     */
    QColor clearColor() const;

    /**
     * @brief
     * 设置进行Clear操作时采用的颜色值
     * @param color
     */
    void setClearColor(const QColor& color);

    /**
     * @brief
     * 返回进行Clear操作时采用的Z深度值
     * @return float
     */
    float clearDepthValue() const;

    /**
     * @brief
     * 设置进行Clear操作时采用的Z深度值
     * @param clearDepthValue
     */
    void setClearDepthValue(float clearDepthValue);

    /**
     * @brief
     * 返回进行Clear操作时采用的Stencil模板值
     * @return int
     */
    int clearStencilValue() const;

    /**
     * @brief
     * 设置进行Clear操作时采用的Stencil模板值
     * @param clearStencilValue
     */
    void setClearStencilValue(int clearStencilValue);

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return LiNodeChangeBasePtr
     */
    LiNodeChangeBasePtr createChangePtr() const;

Q_SIGNALS:
    /**
     * @brief
     *
     * @param attachmentPoint
     */
    void attachmentPointChanged(AttachmentPoint attachmentPoint);
    /**
     * @brief
     *
     * @param texture
     */
    void textureChanged(LiTexture *texture);
    /**
     * @brief
     *
     * @param mipLevel
     */
    void mipLevelChanged(int mipLevel);
    /**
     * @brief
     *
     * @param layer
     */
    void layerChanged(int layer);
    /**
     * @brief
     *
     * @param face
     */
    void faceChanged(LiTexture::CubeMapFace face);
    /**
     * @brief
     *
     * @param bufferType
     */
    void bufferTypeChanged(BufferType bufferType);
    /**
     * @brief
     *
     * @param color
     */
    void clearColorChanged(const QColor& color);
    /**
     * @brief
     *
     * @param clearDepthValue
     */
    void clearDepthValueChanged(float clearDepthValue);
    /**
     * @brief
     *
     * @param clearStencilValue
     */
    void clearStencilValueChanged(int clearStencilValue);

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiRenderTargetOutput(LiRenderTargetOutputPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiRenderTargetOutput)
};

Q_DECLARE_METATYPE(LiRenderTargetOutput::AttachmentPoint)

#endif // LIRENDERTARGETOUTPUT_H
