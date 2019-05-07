#ifndef LIELLIPSOIDGEOMETRY_H
#define LIELLIPSOIDGEOMETRY_H

#include "ligeometry.h"
#include "vector3.h"

class LiEllipsoidGeometryPrivate;

class LICORE_EXPORT LiEllipsoidGeometry : public LiGeometry
{
    Q_OBJECT
public:
    explicit LiEllipsoidGeometry(LiNode *parent = nullptr);
    explicit LiEllipsoidGeometry(const Vector3 &radii,
                                 int stackPartitions = 64,
                                 int slicePartitions = 64,
                                 LiNode *parent = nullptr);

    Vector3 radii() const;
    void setRadii(const Vector3 &radii);

    int stackPartitions() const;
    void setStackPartitions(int stackPartitions);

    int slicePartitions() const;
    void setSlicePartitions(int slicePartitions);

    void create();

signals:
    void radiiChanged();
    void stackPartitionsChanged();
    void slicePartitionsChanged();

private:
    Q_DECLARE_PRIVATE(LiEllipsoidGeometry)
};

#endif // LIELLIPSOIDGEOMETRY_H
