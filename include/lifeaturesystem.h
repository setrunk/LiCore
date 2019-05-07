#ifndef LIFEATURESYSTEM_H
#define LIFEATURESYSTEM_H

#include "liabstractsystem.h"

class LiNode;
class LiFeatureSystemPrivate;

typedef uint LiFeatureId;

class LICORE_EXPORT LiFeatureSystem : public LiAbstractSystem
{
    Q_OBJECT
public:
    explicit LiFeatureSystem(QObject *parent = nullptr);
    virtual ~LiFeatureSystem();

    LiFeatureId registerFeature(LiNode *node);
    void unregisterFeature(LiNode *node);
    LiNode *lookupFeature(LiFeatureId id) const;

signals:
    void featurePicked(LiFeatureId id);

private:
    Q_DECLARE_PRIVATE(LiFeatureSystem)
};

#endif // LIFEATURESYSTEM_H
