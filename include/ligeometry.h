#ifndef LIGEOMETRY_H
#define LIGEOMETRY_H

#include "linode.h"

class LiGeometryAttribute;
class LiGeometryPrivate;
class LiBuffer;
class LiRenderSystem;

/**
 * @brief
 * LiGeometry是对几何体顶点数据以及索引数据的封装，是由索引缓存（LiBuffer）
 * 和一组几何属性（LiGeometryAttribute）组成，提供给LiGeometryRenderer使用。
 * 如果几何属性列表中包含有LiGeometryAttribute::defaultPositionAttributeName属性，
 * 就能够被自动计算包围盒。
 */
class LICORE_EXPORT LiGeometry : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(LiBuffer* indexBuffer READ indexBuffer WRITE setIndexBuffer NOTIFY indexBufferChanged)
    Q_PROPERTY(QQmlListProperty<LiGeometryAttribute> attributes READ qmlAttributes)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiGeometry(LiNode *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiGeometry();

    /**
     * @brief
     * 添加几何属性对象
     * @param attribute
     */
    Q_INVOKABLE void addAttribute(LiGeometryAttribute *attribute);

    /**
     * @brief
     * 添加一组几何属性对象
     * @param attributes
     */
    Q_INVOKABLE void addAttributes(const QVector<LiGeometryAttribute *> &attributes);

    /**
     * @brief
     * 移除几何属性对象，被移除的对象并不会自动删除，需要手动删除释放内存
     * @param attribute
     */
    Q_INVOKABLE void removeAttribute(LiGeometryAttribute *attribute);

    /**
     * @brief
     * 返回所有的几何属性合集
     * @return QVector<LiGeometryAttribute *>
     */
    QVector<LiGeometryAttribute *> attributes() const;

    /**
     * @brief
     * 返回几何体所用到的所有顶点缓存（LiBuffer）合集
     * @return QVector<LiBuffer *>
     */
    QVector<LiBuffer*> vertexBuffers() const;

    /**
     * @brief
     * 返回索引缓存对象
     * @return LiBuffer
     */
    LiBuffer *indexBuffer() const;

    /**
     * @brief
     * 设置索引缓存对象
     * @param buffer
     */
    void setIndexBuffer(LiBuffer *buffer);

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return QQmlListProperty<LiGeometryAttribute>
     */
    QQmlListProperty<LiGeometryAttribute> qmlAttributes();

    /**
     * @brief
     * 返回名称为LiGeometryAttribute::defaultPositionAttributeName的几何属性对象
     * @return LiGeometryAttribute
     */
    Q_INVOKABLE LiGeometryAttribute *positionAttribute() const;

    /**
     * @brief
     * 返回名称为LiGeometryAttribute::defaultTexCoordAttributeName的几何属性对象
     * @return LiGeometryAttribute
     */
    Q_INVOKABLE LiGeometryAttribute *texCoordAttribute() const;

    /**
     * @brief
     * 返回名称为LiGeometryAttribute::defaultTextureIdAttributeName的几何属性对象
     * @return LiGeometryAttribute
     */
    Q_INVOKABLE LiGeometryAttribute *textureIdAttribute() const;

    /**
     * @brief
     * 返回名称为LiGeometryAttribute::defaultNormalAttributeName的几何属性对象
     * @return LiGeometryAttribute
     */
    Q_INVOKABLE LiGeometryAttribute *normalAttribute() const;

    /**
     * @brief
     * 返回名称为LiGeometryAttribute::defaultTangentAttributeName的几何属性对象
     * @return LiGeometryAttribute
     */
    Q_INVOKABLE LiGeometryAttribute *tangentAttribute() const;

    /**
     * @brief
     * 返回名称为LiGeometryAttribute::defaultBinormalAttributeName的几何属性对象
     * @return LiGeometryAttribute
     */
    Q_INVOKABLE LiGeometryAttribute *binormalAttribute() const;

    /**
     * @brief
     * 返回名称为name的几何属性对象
     * @param name
     * @return LiGeometryAttribute
     */
    Q_INVOKABLE LiGeometryAttribute *attribute(const QString &name) const;

    bool calculateTangents();

    /**
     * @brief
     * 返回用于全屏视口渲染的几何体对象
     * @return LiGeometry
     */
    static LiGeometry *viewportQuad();

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return LiNodeChangeBasePtr
     */
    LiNodeChangeBasePtr createChangePtr() const;

signals:
    /**
     * @brief
     * 当索引缓存对象发生改变时，发出该信号
     */
    void indexBufferChanged();

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiGeometry(LiGeometryPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiGeometry)
    friend class LiRenderSystem;
};

#endif // LIGEOMETRY_H
