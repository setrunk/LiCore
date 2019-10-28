#ifndef LIUNIFORMBUFFER_H
#define LIUNIFORMBUFFER_H

#include "libuffer.h"
#include "liparameter.h"
#include <QQmlListProperty>

class LiUniformBufferPrivate;

class LICORE_EXPORT LiUniformBuffer : public LiBuffer
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<LiParameter> parameters READ qmlParameters)
public:
    explicit LiUniformBuffer(LiNode *parent = nullptr);

    QVariant parameter(const QString &name) const;
    void setParameter(const QString &name, const QVariant &value);

    QQmlListProperty<LiParameter> qmlParameters();

signals:

public slots:

private:
    Q_DECLARE_PRIVATE(LiUniformBuffer)
};

#endif // LIUNIFORMBUFFER_H
