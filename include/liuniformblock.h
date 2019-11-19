#ifndef LIUNIFORMBUFFER_H
#define LIUNIFORMBUFFER_H

#include "libuffer.h"
#include "liparameter.h"
#include <QQmlListProperty>

class LiUniformBlockPrivate;

class LICORE_EXPORT LiUniformBlock : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<LiParameter> parameters READ qmlParameters)
public:
    explicit LiUniformBlock(LiNode *parent = nullptr);
    ~LiUniformBlock();

    QString name() const;
    void setName(const QString &name);

    QByteArray data() const;
    void setData(const QByteArray &data);

    QVariant parameter(const QString &name) const;
    void setParameter(const QString &name, const QVariant &value);

    QQmlListProperty<LiParameter> qmlParameters();

    LiNodeChangeBasePtr createChangePtr() const Q_DECL_OVERRIDE;

private:
    Q_DECLARE_PRIVATE(LiUniformBlock)
};

#endif // LIUNIFORMBUFFER_H
