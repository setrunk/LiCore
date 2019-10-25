#ifndef LIGEOMETRY_H
#define LIGEOMETRY_H

#include "linode.h"

class LiBuffer;
class LiGeometryAttribute;
class LiGeometryPrivate;

/**
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

    explicit LiGeometry(LiNode *parent = 0);
    virtual ~LiGeometry();

    /**
     * 添加几何属性对象，添加的顺序必须与Shader里绑定的顺序一致
     */
    Q_INVOKABLE void addAttribute(LiGeometryAttribute *attribute);

    /**
     * 添加多个几何属性对象
     */
    Q_INVOKABLE void addAttributes(const QVector<LiGeometryAttribute *> &attributes);

    /**
     * 移除几何属性对象，被移除的对象并不会自动删除，需要手动删除释放内存
     */
    Q_INVOKABLE void removeAttribute(LiGeometryAttribute *attribute);

    /**
     * 查询是否存在类型为attributeType(LiGeometryAttribute::AttributeType)的几何属性
     */
    Q_INVOKABLE bool hasAttribute(int attributeType) const;

    /**
     * 查询是否存在名称为name的几何属性
     */
    Q_INVOKABLE bool hasAttribute(const QString &name) const;

    /**
     * 返回所有的几何属性合集
     */
    QVector<LiGeometryAttribute *> attributes() const;

    /**
     * 返回变形动画的目标几何体
     */
    QVector<LiGeometry *> morphTargets() const;
    void setMorphTargets(const QVector<LiGeometry *> &morphTargets);
    bool hasMorphing() const;

    /**
     * 返回变形动画目标几何的权重，数量与变形目标数量一致
     */
    QVector<float> morphWeights() const;
    void setMorphWeights(const QVector<float> &morphWeights);

    /**
     * 返回几何体所用到的所有顶点缓存（LiBuffer）合集
     */
    QVector<LiBuffer*> vertexBuffers() const;

    /**
     * 返回索引缓存对象
     */
    LiBuffer *indexBuffer() const;

    /**
     * 设置索引缓存对象
     */
    void setIndexBuffer(LiBuffer *buffer);

    /**
     * 返回内置的几何属性对象
     */
    Q_INVOKABLE LiGeometryAttribute *positionAttribute() const;
    Q_INVOKABLE LiGeometryAttribute *normalAttribute() const;
    Q_INVOKABLE LiGeometryAttribute *tangentAttribute() const;
    Q_INVOKABLE LiGeometryAttribute *texCoordAttribute() const;

    /**
     * 返回名称为name的几何属性对象
     */
    Q_INVOKABLE LiGeometryAttribute *attribute(const QString &name) const;

    /**
     * 返回类型为attributeType(LiGeometryAttribute::AttributeType)的几何属性对象
     */
    Q_INVOKABLE LiGeometryAttribute *attribute(int attributeType) const;

    /**
     * 返回用于全屏视口渲染的几何体对象
     */
    static LiGeometry *viewportQuad();

    /**
     * 内部函数，外部不要调用
     */
    LiNodeChangeBasePtr createChangePtr() const;
    QQmlListProperty<LiGeometryAttribute> qmlAttributes();

signals:
    /**
     * 当索引缓存对象发生改变时，发出该信号
     */
    void indexBufferChanged();

protected:
    explicit LiGeometry(LiGeometryPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiGeometry)
};

#endif // LIGEOMETRY_H
