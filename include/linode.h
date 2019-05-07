#ifndef LINODE_H
#define LINODE_H

#include "linodeid.h"
#include "linodechange.h"
#include <QQmlListProperty>

class LiNode;
class LiNodePrivate;

typedef QVector<LiNode *> LiNodeVector;
typedef QSharedPointer<LiNode> LiNodePtr;

/**
 * @brief
 * LiNode是系统内部的基类，继承于QObject，提供了id，enabled，tag等属性。另外，在qml环境中提供层级嵌套功能
 */
class LICORE_EXPORT LiNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LiNode *parent READ parentNode WRITE setParent NOTIFY parentChanged)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString tag READ tag WRITE setTag NOTIFY tagChanged)
    Q_PROPERTY(QQmlListProperty<QObject> data READ data)
    Q_CLASSINFO("DefaultProperty", "data")
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     * 层级关系的父节点
     */
    explicit LiNode(LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiNode();

    /**
     * @brief
     * 返回节点的唯一id值，id值是系统内部自动分配，是节点对象的唯一标识
     * @return LiNodeId
     */
    LiNodeId id() const;

    /**
     * @brief
     * 该节点是否有效
     * @return bool
     */
    bool isEnabled() const;

    /**
     * @brief
     * 返回节点的标签，新创建的节点的tag初始值为空，除非主动设置tag名称，用于方便查找节点。
     * @return QString
     */
    QString tag() const;

    /**
     * @brief
     * 返回父节点对象
     * @return LiNode
     */
    LiNode *parentNode() const;

    /**
     * @brief
     * 返回所有的子节点合集
     * @return LiNodeVector
     */
    LiNodeVector childNodes() const;

    /**
     * @brief
     * 在子节点中查找名称为name的节点，如果有多个重名的子节点，则返回第一个节点，如果没有该名称的节点，则返回空
     * @param name
     * @return LiNode
     */
    LiNode *findChildWithName(const QString &name) const;

    /**
     * @brief
     * 通过tag名称查找节点，如果有多个节点的tag相同，则返回第一个节点。该函数比findChildWithName要高效
     * @param tag
     * 需要查找的tag名称
     * @return LiNode
     */
    static LiNode *findWithTag(const QString &tag);

    /**
     * @brief
     * 内部函数，外部不应该调用
     * @return QQmlListProperty<QObject>
     */
    QQmlListProperty<QObject> data();

    /**
     * @brief
     * 内部函数，外部不应该调用
     * @return LiNodeChangeBasePtr
     */
    virtual LiNodeChangeBasePtr createChangePtr() const;

public Q_SLOTS:
    /**
     * @brief
     * 设置节点的父节点
     * @param parent
     */
    void setParent(LiNode *parent);

    /**
     * @brief
     * 设置节点的tag标签
     * @param tag
     */
    void setTag(const QString &tag);

    /**
     * @brief
     * 设置节点对象是否有效
     * @param enabled
     */
    void setEnabled(bool enabled);

    /**
     * @brief
     * 等同于deletaLater函数，供qml环境中调用。调用该函数不会马上释放节点，而是在以后某个合适的时间节点释放
     */
    void destroy();

Q_SIGNALS:
    /**
     * @brief
     * 当父节点对象改变时，发出该信号
     * @param parent
     * 新的父节点对象
     */
    void parentChanged(QObject *parent);

    /**
     * @brief
     * enabled属性发生改变时，发出该信号
     * @param enabled
     * 新的enabled值
     */
    void enabledChanged(bool enabled);

    /**
     * @brief
     * 当节点的tag标签值发生改变时，发出该信号
     * @param tag
     * 节点新的tag标签值
     */
    void tagChanged(const QString &tag);

    /**
     * @brief
     * 在该节点被释放前，发出该信号。在信号被发出后，节点以及所有的子节点会马上被释放
     * @param node
     * 即将被释放的节点对象
     */
    void nodeDestroyed(LiNode *node);

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiNode(LiNodePrivate &dd, LiNode *parent = nullptr);

private:
    /**
     * @brief
     * 该类已经重写setParent(LiNode*)函数，如果输入参数为LiNode类型时，不希望QObject版本的setParent函数被调用
     * @param
     */
    void setParent(QObject *) Q_DECL_EQ_DELETE;

    Q_DECLARE_PRIVATE(LiNode)
};

inline LiNodeId nodeId(LiNode *n) { return n ? n->id() : LiNodeId(); }

#endif // LINODE_H
