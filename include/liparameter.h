#ifndef LIPARAMETER_H
#define LIPARAMETER_H

#include "linode.h"

class LiParameterPrivate;

class LICORE_EXPORT LiParameter : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit LiParameter(LiNode *parent = nullptr);
    LiParameter(const QString &name, const QVariant &value, LiNode *parent = nullptr);
    ~LiParameter();

    QString name() const;
    QVariant value() const;

public Q_SLOTS:
    void setName(const QString &name);
    void setValue(const QVariant &dv);

Q_SIGNALS:
    void nameChanged(const QString &name);
    void valueChanged(const QVariant &value);

protected:
    LiParameter(LiParameterPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiParameter)
};

typedef QSharedPointer<LiParameter> LiParameterPtr;

#endif // LIPARAMETER_H
