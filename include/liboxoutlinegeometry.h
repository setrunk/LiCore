#ifndef LIBOXOUTLINEGEOMETRY_H
#define LIBOXOUTLINEGEOMETRY_H

#include "ligeometry.h"
#include "vector3.h"

class LiBoxOutlineGeometryPrivate;

class LICORE_EXPORT LiBoxOutlineGeometry : public LiGeometry
{
    Q_OBJECT
public:
    explicit LiBoxOutlineGeometry(LiNode *parent = nullptr);
    explicit LiBoxOutlineGeometry(const Vector3 &minimum, const Vector3 &maximum, LiNode *parent = nullptr);

    Vector3 minimum() const;
    void setMinimum(const Vector3 &v);

    Vector3 maximum() const;
    void setMaximum(const Vector3 &v);

    void create();

private:
    Q_DECLARE_PRIVATE(LiBoxOutlineGeometry)
};

#endif // LIBOXOUTLINEGEOMETRY_H
