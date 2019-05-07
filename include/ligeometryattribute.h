#ifndef LIGEOMETRYATTRIBUTE_H
#define LIGEOMETRYATTRIBUTE_H

#include "linode.h"

class LiBuffer;
class LiGeometryAttributePrivate;
class LiGeometryAttribute;
typedef QVector<LiGeometryAttribute*> LiGeometryAttributeCollection;

/**
 * @brief
 * LiGeometryAttribute描述如何从LiBuffer中读取数据，绑定到OpenGL渲染管线中的顶点数据单元。
 * 最常见的顶点数据包含Position, Normal, TexCoord数据属性。
 */
class LICORE_EXPORT LiGeometryAttribute : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(LiBuffer * buffer READ buffer WRITE setBuffer NOTIFY bufferChanged)
    Q_PROPERTY(int offsetBytes READ offsetBytes WRITE setOffsetBytes NOTIFY offsetBytesChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(ComponentDataType componentDataType READ componentDataType WRITE setComponentDataType NOTIFY componentDataTypeChanged)
    Q_PROPERTY(int components READ components WRITE setComponents NOTIFY componentsChanged)
    Q_PROPERTY(int instanceDataStep READ instanceDataStep WRITE setInstanceDataStep NOTIFY instanceDataStepChanged)
public:
    /**
     * @brief
     * 顶点数据单个通道的数据类型
     */
    enum ComponentDataType
    {
        SINT8,
        UINT8,
        SINT16,
        UINT16,
        SINT32,
        UINT32,
        FLOAT32,
        FLOAT64
    };
    Q_ENUM(ComponentDataType)

    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiGeometryAttribute(LiNode *parent = 0);

    /**
     * @brief
     * 构造函数
     * @param buffer
     * 顶点数据缓存
     * @param offsetBytes
     * 数据读取的字节偏移量
     * @param name
     * 顶点属性的名称
     * @param components
     * 顶点属性的通道数
     * @param parent
     */
    LiGeometryAttribute(LiBuffer *buffer,
                        int offsetBytes,
                        const QString &name,
                        int components,
                        LiNode *parent = nullptr);
    /**
     * @brief
     * 析构函数
     */
    virtual ~LiGeometryAttribute();

    /**
     * @brief
     * 返回该顶点属性所读取的缓存
     * @return LiBuffer
     */
    LiBuffer *buffer() const;

    /**
     * @brief
     * 返回数据读取的字节偏移量
     * @return int
     */
    int offsetBytes() const;

    /**
     * @brief
     * 返回顶点属性的名称
     * @return QString 比如POSITION, NORMAL, TEXCOORD等
     */
    QString name() const;

    /**
     * @brief
     * 返回数据通道的类型
     * @return ComponentDataType
     */
    ComponentDataType componentDataType() const;

    /**
     * @brief
     * 返回属性的通道数量
     * @return int
     */
    int components() const;

    /**
     * @brief
     * 如果是Instance属性，返回每个Instance占用数据的步长
     * @return int 0表示该属性不是Instance属性，1表示该属性是Instance属性，
     * 并且每一个Instance读取一个元素数据
     */
    int instanceDataStep() const;

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return LiNodeChangeBasePtr
     */
    LiNodeChangeBasePtr createChangePtr() const;

    /**
     * @brief
     * 创建Position顶点数据属性
     * @param buffer
     * 顶点数据缓存
     * @param offsetBytes
     * 在顶点数据缓存中的字节偏移量
     * @param components
     * 顶点属性的通道数量
     * @return LiGeometryAttribute
     */
    static LiGeometryAttribute *createPositionAttribute(LiBuffer *buffer,
                                                        int offsetBytes,
                                                        int components);
    /**
     * @brief
     * 创建Normal顶点数据属性
     * @param buffer
     * 顶点数据缓存
     * @param offsetBytes
     * 在顶点数据缓存中的字节偏移量
     * @param components
     * 顶点属性的通道数量
     * @return LiGeometryAttribute
     */
    static LiGeometryAttribute *createNormalAttribute(LiBuffer *buffer,
                                                      int offsetBytes,
                                                      int components);
    /**
     * @brief
     * 创建Tangent顶点数据属性
     * @param buffer
     * 顶点数据缓存
     * @param offsetBytes
     * 在顶点数据缓存中的字节偏移量
     * @param components
     * 顶点属性的通道数量
     * @return LiGeometryAttribute
     */
    static LiGeometryAttribute *createTangentAttribute(LiBuffer *buffer,
                                                       int offsetBytes,
                                                       int components);
    /**
     * @brief
     * 创建Binormal顶点数据属性
     * @param buffer
     * 顶点数据缓存
     * @param offsetBytes
     * 在顶点数据缓存中的字节偏移量
     * @param components
     * 顶点属性的通道数量
     * @return LiGeometryAttribute
     */
    static LiGeometryAttribute *createBinormalAttribute(LiBuffer *buffer,
                                                        int offsetBytes,
                                                        int components);
    /**
     * @brief
     * 创建TexCoord顶点数据属性
     * @param buffer
     * 顶点数据缓存
     * @param offsetBytes
     * 在顶点数据缓存中的字节偏移量
     * @param components
     * 顶点属性的通道数量
     * @return LiGeometryAttribute
     */
    static LiGeometryAttribute *createTexCoordAttribute(LiBuffer *buffer,
                                                        int offsetBytes,
                                                        int components);

    /**
     * @brief
     * 返回默认的Position属性的名称
     * @return QString
     */
    Q_INVOKABLE static QString defaultPositionAttributeName();

    /**
     * @brief
     * 返回默认的TexCoord属性的名称
     * @return QString
     */
    Q_INVOKABLE static QString defaultTexCoordAttributeName();

    /**
     * @brief
     * 返回默认的TextureId属性的名称
     * @return QString
     */
    Q_INVOKABLE static QString defaultTextureIdAttributeName();

    /**
     * @brief
     * 返回默认的Normal属性的名称
     * @return QString
     */
    Q_INVOKABLE static QString defaultNormalAttributeName();

    /**
     * @brief
     * 返回默认的Tangent属性的名称
     * @return QString
     */
    Q_INVOKABLE static QString defaultTangentAttributeName();

    /**
     * @brief
     * 返回默认的Binormal属性的名称
     * @return QString
     */
    Q_INVOKABLE static QString defaultBinormalAttributeName();

signals:
    void bufferChanged();
    void offsetBytesChanged();
    void nameChanged();
    void componentDataTypeChanged();
    void componentsChanged();
    void instanceDataStepChanged();
    void attributeChanged();

public slots:
    /**
     * @brief
     * 设置该属性所读取的顶点缓存
     * @param buffer
     */
    void setBuffer(LiBuffer *buffer);

    /**
     * @brief
     * 设置该属性从顶点缓存中读取数据的字节偏移量
     * @param offset
     */
    void setOffsetBytes(int offset);

    /**
     * @brief
     * 设置该属性的名称
     * @param name
     */
    void setName(const QString &name);

    /**
     * @brief
     * 设置该属性的通道数据类型
     * @param type
     */
    void setComponentDataType(ComponentDataType type);

    /**
     * @brief
     * 设置该属性通道数量
     * @param components
     */
    void setComponents(int components);

    /**
     * @brief
     * 设置该属性每个Instance所占用的数据元素步长
     * @param step 默认为0
     */
    void setInstanceDataStep(int step);

private:
    Q_DECLARE_PRIVATE(LiGeometryAttribute)
};

#endif // LIGEOMETRYATTRIBUTE_H
