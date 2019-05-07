#ifndef LIFRUSTUMGEOMETRY_H
#define LIFRUSTUMGEOMETRY_H

#include "ligeometry.h"
#include "perspectivefrustum.h"
#include "orthographicfrustum.h"

class LICORE_EXPORT LiFrustumGeometry : public LiGeometry
{
    Q_OBJECT
public:
    enum Type
    {
        Lines = 0x01,
        Planes = 0x02,
        LinesAndPlanes = 0x03
    };

    explicit LiFrustumGeometry(LiNode *parent = nullptr);

    void createLines(double fov, double aspect, double nearPlane, double farPlane);
    void createLines(const PerspectiveFrustum &frustum);
    void createLines(const OrthographicFrustum &frustum);
};

#endif // LIFRUSTUMGEOMETRY_H
