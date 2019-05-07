#ifndef LIBUFFER_H
#define LIBUFFER_H

#include "linode.h"
#include "vector3.h"

class LiBufferPrivate;

/**
 * @brief
 * LiBuffer是渲染模块的核心类，是对OpenGL中的Buffer的封装，
 * 提供接口在GPU中创建一块缓存，比如顶点缓存、索引缓存、Shader变量缓存等。
 */
class LICORE_EXPORT LiBuffer : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(BufferType bufferType READ bufferType WRITE setBufferType NOTIFY bufferTypeChanged)
    Q_PROPERTY(UsageType usageType READ usageType WRITE setUsageType NOTIFY usageTypeChanged)
    Q_PROPERTY(AccessType accessType READ accessType WRITE setAccessType NOTIFY accessTypeChanged)
    Q_PROPERTY(int strideBytes READ strideBytes WRITE setStrideBytes NOTIFY strideBytesChanged)
    Q_PROPERTY(QVariant data READ bufferData WRITE setBufferData NOTIFY dataChanged)
public:
    /**
     * @brief
     * Buffer类型，在Buffer被创建的时候，必须指定类型：定点缓存、索引缓存、Shader变量等
     * 具体涵义请参考OpenGL的文档 https://www.khronos.org/opengl/wiki/Main_Page
     */
    enum BufferType
    {
        VertexBuffer        = 0x8892, // GL_ARRAY_BUFFER
        IndexBuffer         = 0x8893, // GL_ELEMENT_ARRAY_BUFFER
        PixelPackBuffer     = 0x88EB, // GL_PIXEL_PACK_BUFFER
        PixelUnpackBuffer   = 0x88EC, // GL_PIXEL_UNPACK_BUFFER
        UniformBuffer       = 0x8A11, // GL_UNIFORM_BUFFER
        ShaderStorageBuffer = 0x90D2, // GL_SHADER_STORAGE_BUFFER
        DrawIndirectBuffer  = 0x8F3F  // GL_DRAW_INDIRECT_BUFFER
    };
    Q_ENUM(BufferType)

    /**
     * @brief
     * Buffer的用途，不同用途的Buffer，会在不同的内存空间创建
     * 具体涵义请参考OpenGL的文档 https://www.khronos.org/opengl/wiki/Main_Page
     */
    enum UsageType
    {
        StreamDraw          = 0x88E0, // GL_STREAM_DRAW
        StreamRead          = 0x88E1, // GL_STREAM_READ
        StreamCopy          = 0x88E2, // GL_STREAM_COPY
        StaticDraw          = 0x88E4, // GL_STATIC_DRAW
        StaticRead          = 0x88E5, // GL_STATIC_READ
        StaticCopy          = 0x88E6, // GL_STATIC_COPY
        DynamicDraw         = 0x88E8, // GL_DYNAMIC_DRAW
        DynamicRead         = 0x88E9, // GL_DYNAMIC_READ
        DynamicCopy         = 0x88EA  // GL_DYNAMIC_COPY
    };
    Q_ENUM(UsageType) // LCOV_EXCL_LINE

    /**
     * @brief
     * cpu端的读写权限
     */
    enum AccessType {
        ReadOnly            = 0x88B8, // GL_READ_ONLY
        WriteOnly           = 0x88B9, // GL_WRITE_ONLY
        ReadWrite           = 0x88BA  // GL_READ_WRITE
    };
    Q_ENUM(AccessType) // LCOV_EXCL_LINE

    /**
     * @brief
     * cpu端的部分范围读写权限
     */
    enum RangeAccessFlag
    {
        RangeRead             = 0x0001, // GL_MAP_READ_BIT
        RangeWrite            = 0x0002, // GL_MAP_WRITE_BIT
        RangeInvalidate       = 0x0004, // GL_MAP_INVALIDATE_RANGE_BIT
        RangeInvalidateBuffer = 0x0008, // GL_MAP_INVALIDATE_BUFFER_BIT
        RangeFlushExplicit    = 0x0010, // GL_MAP_FLUSH_EXPLICIT_BIT
        RangeUnsynchronized   = 0x0020  // GL_MAP_UNSYNCHRONIZED_BIT
    };
    Q_DECLARE_FLAGS(RangeAccessFlags, RangeAccessFlag)

    /**
     * @brief
     * 构造函数
     * @param parent 父节点
     */
    explicit LiBuffer(LiNode *parent = 0);

    /**
     * @brief
     * 构造函数
     * @param type 类型（顶点、索引、Shader变量）
     * @param data 需要填充Buffer的用户数据
     * @param stride 字节步长，比如一个顶点或者一个索引值的字节数
     * @param usage 用途，cpu端的读写权限
     * @param parent 父节点
     */
    LiBuffer(BufferType type,
             const QByteArray &data,
             int stride,
             UsageType usage = StaticDraw,
             LiNode *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiBuffer();

    /**
     * @brief
     * 返回Buffer的类型
     * @return BufferType
     */
    BufferType bufferType() const;

    /**
     * @brief
     * 设置Buffer的类型
     * @param type
     */
    void setBufferType(BufferType type);

    /**
     * @brief
     * 返回Buffer的用途
     * @return UsageType
     */
    UsageType usageType() const;

    /**
     * @brief
     * 设置Buffer的用途
     * @param usage
     */
    void setUsageType(UsageType usage);

    /**
     * @brief
     * 返回Buffer的cpu端读写权限
     * @return AccessType
     */
    AccessType accessType() const;

    /**
     * @brief
     * 设置Buffer的cpu端读写权限
     * @param access
     */
    void setAccessType(AccessType access);

    /**
     * @brief
     * 返回Buffer元素的步长（字节）
     * @return int
     */
    int strideBytes() const;

    /**
     * @brief
     * 设置Buffer元素的步长（字节）
     * @param stride
     */
    void setStrideBytes(int stride);

    /**
     * @brief
     * 返回Buffer的用户填充数据
     * @return QByteArray
     */
    QByteArray data() const;

    /**
     * @brief
     * 设置Buffer的用户填充数据
     * @param data
     */
    void setData(const QByteArray &data);

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return QVariant
     */
    QVariant bufferData() const;

    /**
     * @brief
     * 内部函数，外部不要调用
     * @param bufferData
     */
    void setBufferData(const QVariant &bufferData);

    /**
     * @brief
     * Buffer的大小（字节）
     * @return int in bytes
     */
    Q_INVOKABLE int size() const;

    /**
     * @brief
     * Buffer的元素数量
     * @return int = size() / strideBytes()
     */
    Q_INVOKABLE int count() const;

    /**
     * @brief
     * Buffer的元素数量，等同于count()函数
     * @return int
     */
    Q_INVOKABLE int elements() const;

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return LiNodeChangeBasePtr
     */
    LiNodeChangeBasePtr createChangePtr() const Q_DECL_OVERRIDE;

    /**
     * @brief
     * 获取Vector2类型的元素
     * @param index 元素的序号
     * @param offsetInBytes 在元素中的字节偏移
     * @return Vector2
     */
    Vector2 getVector2(int index, int offsetInBytes) const;

    /**
     * @brief
     * 获取Vector3类型的元素
     * @param index 元素的序号
     * @param offsetInBytes 在元素中的字节偏移
     * @return Vector3
     */
    Vector3 getVector3(int index, int offsetInBytes) const;

    /**
     * @brief
     * 获取索引缓存(IndexBuffer)中第index个的值
     * @param index 索引缓存的偏移个数
     * @return uint
     */
    uint getIndex(int index) const;

    /**
     * @brief
     * 创建顶点缓存
     * @param data 顶点数据
     * @param strideInBytes 单个顶点数据的字节数
     * @param usage Buffer用途
     * @param parent 父节点
     * @return LiBuffer
     */
    static LiBuffer *createVertexBuffer(const QByteArray &data,
                                        int strideInBytes,
                                        UsageType usage = StaticDraw,
                                        LiNode *parent = 0);

    /**
     * @brief
     * 创建索引缓存
     * @param data 索引数据
     * @param strideInBytes 单个索引数据的字节数
     * @param usage Buffer用途
     * @param parent 父节点
     * @return LiBuffer
     */
    static LiBuffer *createIndexBuffer(const QByteArray &data,
                                       int strideInBytes,
                                       UsageType usage = StaticDraw,
                                       LiNode *parent = 0);

signals:
    /**
     * @brief
     * Buffer类型改变时，发出该信号
     */
    void bufferTypeChanged();

    /**
     * @brief
     * Buffer用途类型改变时，发出该信号
     */
    void usageTypeChanged();

    /**
     * @brief
     * Buffer读写权限改变时，发出该信号
     */
    void accessTypeChanged();

    /**
     * @brief
     * Buffer元素步长改变时，发出该信号
     */
    void strideBytesChanged();

    /**
     * @brief
     * Buffer填充数据改变时，发出该信号
     */
    void dataChanged();

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiBuffer(LiBufferPrivate &dd, LiNode *parent = 0);

private:
    Q_DECLARE_PRIVATE(LiBuffer)
};

#endif // LIBUFFER_H
