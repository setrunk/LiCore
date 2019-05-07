#ifndef LIGEOMETRYINSTANCE_H
#define LIGEOMETRYINSTANCE_H

#include "linode.h"
#include "matrix4.h"

class LiGeometry;
class LiGeometryAttribute;
class LiGeometryInstancePrivate;

typedef quint64 InstanceId;

class LICORE_EXPORT LiGeometryInstance : public LiNode
{
    Q_OBJECT
public:
    explicit LiGeometryInstance(LiNode *parent = nullptr);
    explicit LiGeometryInstance(const QVariantMap &attributes, LiNode *parent = nullptr);

    Matrix4 modelMatrix() const;
    void setModelMatrix(const Matrix4 &matrix);

    QColor color() const;
    void setColor(const QColor &color);

    bool show() const;
    void setShow(bool show);

    QVariant attribute(const QString &attributeName) const;
    void setAttribute(const QString &attributeName, const QVariant &value);

    QVariantMap attributes() const;
    void setAttributes(const QVariantMap &attributes);

private:
    Q_DECLARE_PRIVATE(LiGeometryInstance)
};

#endif // LIGEOMETRYINSTANCE_H
