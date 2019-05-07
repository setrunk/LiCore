#ifndef PERSPECTIVEOFFCENTERFRUSTUM_H
#define PERSPECTIVEOFFCENTERFRUSTUM_H

#include "licore_global.h"
#include "matrix4.h"
#include "cartesian3.h"

class CullingVolume;

class LICORE_EXPORT PerspectiveOffCenterFrustum
{
public:
    PerspectiveOffCenterFrustum();

    double left() const { return _left; }
    void setLeft(double left) { _left = left; _dirty = true; }

    double right() const { return _right; }
    void setRight(double right) { _right = right; _dirty = true; }

    double top() const { return _top; }
    void setTop(double top) { _top = top; _dirty = true; }

    double bottom() const { return _bottom; }
    void setBottom(double bottom) { _bottom = bottom; _dirty = true; }

    double nearPlane() const { return _nearPlane; }
    void setNearPlane(double nearPlane) { _nearPlane = nearPlane; _dirty = true; }

    double farPlane() const { return _farPlane; }
    void setFarPlane(double farPlane) { _farPlane = farPlane; _dirty = true; }

    Matrix4 projectionMatrix() const;
    Matrix4 infiniteProjectionMatrix() const;

    Cartesian2 getPixelDimensions(int drawingBufferWidth, int drawingBufferHeight, double distance) const;

    void update();
    void computeCullingVolume(const Cartesian3 &position, const Cartesian3 &direction, const Cartesian3 &up);

private:
    double _left;
    double _right;
    double _top;
    double _bottom;
    double _nearPlane;
    double _farPlane;
    mutable Matrix4 _perspectiveMatrix;
    mutable Matrix4 _infinitePerspective;
    mutable bool _dirty;
};

#endif // PERSPECTIVEOFFCENTERFRUSTUM_H
