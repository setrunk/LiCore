#ifndef LIBOXGEOMETRY_H
#define LIBOXGEOMETRY_H

#include "ligeometry.h"
#include "boundingsphere.h"
#include "vector3.h"
#include <QQmlParserStatus>

class LiGeometry;
class LiBoxGeometryPrivate;

class LICORE_EXPORT LiBoxGeometry : public LiGeometry, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(Vector3 extent READ extent WRITE setExtent NOTIFY extentChanged)
    Q_PROPERTY(bool hasNormal READ hasNormal WRITE setHasNormal NOTIFY hasNormalChanged)
    Q_PROPERTY(bool hasTexCoord READ hasTexCoord WRITE setHasTexCoord NOTIFY hasTexCoordChanged)
public:
    explicit LiBoxGeometry(LiNode *parent = nullptr);
    explicit LiBoxGeometry(const Vector3 &extent,
                           bool hasNormal = true,
                           bool hasTexCoord = false,
                           LiNode *parent = nullptr);

    void create(const Vector3 &extent, bool hasNormal = true, bool hasTexCoord = false);
    void createLines(const Vector3 &extent);

    Vector3 extent() const;
    void setExtent(const Vector3 &extent);

    bool hasNormal() const;
    void setHasNormal(bool hasNormal);

    bool hasTexCoord() const;
    void setHasTexCoord(bool hasTexCoord);

    Q_INVOKABLE BoundingSphere boundingSphere() const;

    virtual void classBegin() {}
    virtual void componentComplete();

signals:
    void hasNormalChanged(bool hasNormal);
    void hasTexCoordChanged(bool hasTexCoord);
    void extentChanged(const Vector3 &extent);

private:
    Q_DECLARE_PRIVATE(LiBoxGeometry)
};

#endif // LIBOXGEOMETRY_H
