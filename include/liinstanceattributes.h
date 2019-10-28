#ifndef LIINSTANCEATTRIBUTES_H
#define LIINSTANCEATTRIBUTES_H

#include "linode.h"
#include "matrix4.h"

class LiBuffer;
class LiGeometry;
class LiGeometryAttribute;
class LiInstanceAttributesPrivate;

class LICORE_EXPORT LiInstanceAttributes : public LiNode
{
    Q_OBJECT
public:
    explicit LiInstanceAttributes(LiNode *parent = nullptr);

    LiGeometryAttribute *transformAttribute() const;
    void setTransformAttribute(LiGeometryAttribute *attribute);

    LiGeometryAttribute *colorAttribute() const;
    void setColorAttribute(LiGeometryAttribute *attribute);

    LiGeometryAttribute *showAttribute() const;
    void setShowAttribute(LiGeometryAttribute *attribute);

    LiGeometryAttribute *attribute(const QString &name) const;
    QVector<LiGeometryAttribute*> attributes() const;

    void addAttribute(LiGeometryAttribute *attribute);

    QVector<LiBuffer *> vertexBuffers() const;
    QVector<Matrix4> transfoms() const;

    virtual LiNodeChangeBasePtr createChangePtr() const;

Q_SIGNALS:
    void attributesChanged(const QString &name, const QVariantList &value);

private:
    Q_DECLARE_PRIVATE(LiInstanceAttributes)
};

#endif // LIINSTANCEATTRIBUTES_H
