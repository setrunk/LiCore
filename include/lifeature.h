#ifndef LIFEATURE_H
#define LIFEATURE_H

#include "linode.h"
#include "lipickid.h"

class LiFeaturePrivate;

class LICORE_EXPORT LiFeature : public LiNode
{
    Q_OBJECT
public:
    explicit LiFeature(LiNode *parent = nullptr);
    ~LiFeature();

    LiPickId pickId() const;

    virtual bool hasProperty(const QString &name) const;
    virtual QVariant getProperty(const QString &name) const;
    virtual void setProperty(const QString &name, const QVariant &property);
    virtual QStringList propertyNames() const;

private:
    Q_DECLARE_PRIVATE(LiFeature)
};

#endif // LIFEATURE_H
