#ifndef LIFEATURE_H
#define LIFEATURE_H

#include "linode.h"

class LiFeaturePrivate;

class LICORE_EXPORT LiFeature : public LiNode
{
    Q_OBJECT
public:
    explicit LiFeature(LiNode *parent = nullptr);
    ~LiFeature();

    virtual bool hasProperty(const QString &name) const;
    virtual QVariant getProperty(const QString &name) const;
    virtual QStringList propertyNames() const;

private:
    Q_DECLARE_PRIVATE(LiFeature)
};

#endif // LIFEATURE_H
