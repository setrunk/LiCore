#ifndef LITEXTUREIMAGE_H
#define LITEXTUREIMAGE_H

#include "linode.h"
#include "litexture.h"
#include "future.h"
#include <QQmlParserStatus>

class LiContentFetcher;
class LiTextureImagePrivate;

/**
 * @brief
 * LiTextureImage是对纹理图像数据的封装，属于cpu端的图像数据。数据可以是从外部文件加载，也可以从内存中创建，或者由QImage填充。
 */
class LICORE_EXPORT LiTextureImage : public LiNode, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool compressed READ compressed WRITE setCompressed NOTIFY compressedChanged)
    Q_PROPERTY(bool autoMipMaps READ autoMipMaps WRITE setAutoMipMaps NOTIFY autoMipMapsChanged)
public:
    /**
     * @brief
     * cpu端数据的缓存方式
     */
    enum DataPolicy {
        ClientCache, // cpu端保留数据备份
        GraphicOnly // cpu端不保留数据备份，在上传gpu端后，图像数据会被清除
    };

    /**
     * @brief
     * 对象内部状态
     */
    enum Status {
        None = 0, // 未初始化
        Loading, // 正在加载资源
        Ready, // 完成状态
        Error // 错误状态
    };
    Q_ENUM(Status) // LCOV_EXCL_LINE

    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiTextureImage(LiNode *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiTextureImage();

    /**
     * @brief
     * 返回当前对象内部状态
     * @return Status
     */
    Status status() const;

    /**
     * @brief
     * 返回当前对象是否完成
     * @return bool
     */
    bool isReady() const;

    /**
     * @brief
     * 返回当前对象是否完成
     * @return bool
     */
    bool isValid() const;

    /**
     * @brief
     * 返回图像的宽度
     * @return int
     */
    int width() const;

    /**
     * @brief
     * 返回图像的高度
     * @return int
     */
    int height() const;

    /**
     * @brief
     * 返回图像的深度
     * @return int
     */
    int depth() const;

    /**
     * @brief
     * 返回图像的MipMap数量
     * @return int
     */
    int mipLevels() const;

    /**
     * @brief
     * 返回图像的面数
     * @return int
     */
    int faces() const;

    /**
     * @brief
     * 返回图像的层数
     * @return int
     */
    Q_DECL_DEPRECATED int arraySize() const;

    /**
     * @brief
     * 返回图像的层数
     * @return int
     */
    int layers() const;

    /**
     * @brief
     * 设置图像的宽度
     * @param width
     */
    void setWidth(int width);

    /**
     * @brief
     * 设置图像的高度
     * @param height
     */
    void setHeight(int height);

    /**
     * @brief
     * 设置图像的深度
     * @param depth
     */
    void setDepth(int depth);

    /**
     * @brief
     * 设置图像的MipMap数量
     * @param mipLevels
     */
    void setMipLevels(int mipLevels);

    /**
     * @brief
     * 设置图像的面数
     * @param faces
     */
    void setFaces(int faces);

    /**
     * @brief
     * 设置图像的层数
     * @param arraySize
     */
    Q_DECL_DEPRECATED void setArraySize(int arraySize);

    /**
     * @brief
     * 设置图像的层数
     * @param layers
     */
    void setLayers(int layers);

    /**
     * @brief
     * 返回该图像加载的外部路径
     * @return QUrl
     */
    QUrl source() const;

    /**
     * @brief
     * 返回图像是否采用DXT压缩
     * @return bool
     */
    bool compressed() const;

    /**
     * @brief
     * 返回图像是否自动生成MipMap链
     * @return bool
     */
    bool autoMipMaps() const;

    /**
     * @brief
     * 返回图像是否有Alpha通道
     * @return bool
     */
    bool hasAlpha() const;

    /**
     * @brief
     * 设置图像加载资源的外部路径
     * @param source
     */
    void setSource(const QUrl &source);

    /**
     * @brief
     * 设置图像数据是否进行DXT压缩
     * @param compressed
     */
    void setCompressed(bool compressed);

    /**
     * @brief
     * 设置图像是否自动生成MipMap链
     * @param autoMipMaps
     */
    void setAutoMipMaps(bool autoMipMaps);

    /**
     * @brief
     * 设置图像是否有Alpha通道
     * @param hasAlpha
     */
    void setHasAlpha(bool hasAlpha);

    /**
     * @brief
     * 返回图像的目标类型，比如1D, 2D, 3D等
     * @return QOpenGLTexture::Target
     */
    QOpenGLTexture::Target target() const;

    /**
     * @brief
     * 返回图像的格式
     * @return QOpenGLTexture::TextureFormat
     */
    QOpenGLTexture::TextureFormat textureFormat() const;

    /**
     * @brief
     * 返回图像的像素格式
     * @return QOpenGLTexture::PixelFormat
     */
    QOpenGLTexture::PixelFormat pixelFormat() const;

    /**
     * @brief
     * 返回图像的像素类型
     * @return QOpenGLTexture::PixelType
     */
    QOpenGLTexture::PixelType pixelType() const;

    /**
     * @brief
     * 设置图像的目标类型
     * @param target
     */
    void setTarget(QOpenGLTexture::Target target);

    /**
     * @brief
     * 设置图像的纹理格式
     * @param textureFormat
     */
    void setTextureFormat(QOpenGLTexture::TextureFormat textureFormat);

    /**
     * @brief
     * 设置图像的像素格式
     * @param pixelFormat
     */
    void setPixelFormat(QOpenGLTexture::PixelFormat pixelFormat);

    /**
     * @brief
     * 设置图像的像素类型
     * @param pixelType
     */
    void setPixelType(QOpenGLTexture::PixelType pixelType);

    /**
     * @brief
     * 返回图像加载的等待信号，当加载完成时，该信号会变成finished状态
     * @return QFuture<void>
     */
    QFuture<void> loadingPromise() const;

    /**
     * @brief
     * 返回图像的数据缓存方式
     * @return DataPolicy
     */
    DataPolicy dataPolicy() const;

    /**
     * @brief
     * 设置图像的数据缓存方式
     * @param policy
     */
    void setDataPolicy(DataPolicy policy);

    /**
     * @brief
     * 返回图像数据
     * @return QByteArray
     */
    QByteArray data() const;

    /**
     * @brief
     * 返回图像的MipMap数据
     * @param mipLevel
     * MipMap序号
     * @param face
     * 面序号
     * @param arrayIndex
     * 层序号
     * @return QByteArray
     */
    QByteArray data(int mipLevel, int face = 0, int arrayIndex = 0) const;

    /**
     * @brief
     * 设置图像数据
     * @param data
     * 图像数据
     * @param blockSize
     * 一个像素的字节数，如果是DXT数据，代表一个DXT压缩块的字节数
     * @param isCompressed
     * 数据是否是DXT压缩数据
     */
    void setData(const QByteArray &data, int blockSize, bool isCompressed = false);

    /**
     * @brief
     * 内部函数，外部不要调用
     */
    virtual void classBegin() {}

    /**
     * @brief
     * 内部函数，外部不要调用
     */
    virtual void componentComplete();

    /**
     * @brief
     *
     * @return LiNodeChangeBasePtr
     */
    LiNodeChangeBasePtr createChangePtr() const;

    /**
     * @brief
     * 内部函数，外部不要调用
     * @param source
     */
    void clone(LiTextureImage *source);

signals:
    /**
     * @brief
     * 当图像内部状态改变时，发出该信号
     * @param status
     */
    void statusChanged(Status status);

    /**
     * @brief
     * 当图像外部资源路径改变时，发出该信号
     */
    void sourceChanged();

    /**
     * @brief
     * 当图像DXT压缩属性改变时，发出该信号
     */
    void compressedChanged();

    /**
     * @brief
     * 当图像自动生成MipMap链属性改变时，发出该信号
     */
    void autoMipMapsChanged();

    /**
     * @brief
     * 当图像数据改变时，发出该信号
     * @param textureImage
     */
    void dataChanged(LiTextureImage *textureImage);

public slots:
    /**
     * @brief
     * 加载外部图像资源，异步函数
     * @param source
     * 图像资源的路径
     * @param miorred
     * 填充前图像是否进行垂直镜像
     * @param skipMipLevels
     * 填充前将图像进行MipMap偏移
     * @return Future
     * 后台处理的等待信号
     */
    Future loadImage(const QUrl &source, bool miorred = true, int skipMipLevels = 0);

    /**
     * @brief
     * 用图像image去填充对象，异步函数
     * @param image
     * 用于填充的图像
     * @param miorred
     * 填充前图像image是否进行垂直镜像
     * @param skipMipLevels
     * 填充前将图像image进行MipMap偏移
     * @return Future
     * 后台处理的等待信号
     */
    Future setImage(const QImage &image, bool miorred = false, int skipMipLevels = 0);

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiTextureImage(LiTextureImagePrivate &dd, LiNode *parent = 0);

private:
    Q_DECLARE_PRIVATE(LiTextureImage)
};

#endif // LITEXTUREIMAGE_H
