#ifndef LIBATCHTABLE_H
#define LIBATCHTABLE_H

#include "linode.h"
#include "vector4.h"

class LiTexture;
class LiBatchTablePrivate;

class LICORE_EXPORT LiBatchTable : public LiNode
{
    Q_OBJECT
public:
    enum ComponentDataType
    {
        Color,
        Float,
        Vec2,
        Vec3,
        Vec4
    };
    Q_ENUM(ComponentDataType)

    explicit LiBatchTable(LiNode *parent = nullptr);

    int width() const;
    int height() const;
    int stride() const;
    Vector4 textureStep() const;
    LiTexture *texture() const;

    int numberOfInstances() const;
    void setNumberOfInstances(int instances);

    void addAttribute(ComponentDataType componentDataType);

    QVariant getBatchedAttribute(int instanceIndex, int attributeIndex) const;
    void setBatchedAttribute(int instanceIndex, int attributeIndex, const QVariant &value); // value can be float/Vector2/Vector3/Vector4

private:
    Q_DECLARE_PRIVATE(LiBatchTable)
};

#endif // LIBATCHTABLE_H
