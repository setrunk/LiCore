#ifndef ORTHOGRAPHICFRUSTUM_H
#define ORTHOGRAPHICFRUSTUM_H

#include "licore_global.h"
#include "cullingvolume.h"
#include "matrix4.h"

/**
 * @brief
 * 正交式视锥。
 */
class LICORE_EXPORT OrthographicFrustum
{
public:
    /**
     * @brief
     *
     */
    OrthographicFrustum()
        : _left(-100.0)
        , _right(100.0)
        , _bottom(-100.0)
        , _top(100.0)
        , _znear(1.0)
        , _zfar(1000.0)
    {
    }

    // parameters are in camera space
    /**
     * @brief
     *
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param znear
     * @param zfar
     */
    OrthographicFrustum(double left, double right, double bottom, double top, double znear, double zfar)
        : _left(left)
        , _right(right)
        , _bottom(bottom)
        , _top(top)
        , _znear(znear)
        , _zfar(zfar)
    {
    }

    /**
     * @brief
     *
     * @return Matrix4
     */
    Matrix4 projectionMatrix() const;
    /**
     * @brief
     *
     * @param position
     * @param direction
     * @param up
     * @return CullingVolume
     */
    CullingVolume computeCullingVolume(const Vector3 &position, const Vector3 &direction, const Vector3 &up);
    /**
     * @brief
     *
     * @return QVector<Vector3>
     */
    QVector<Vector3> computeCorners() const;

    /**
     * @brief
     *
     * @return double
     */
    double left() const
    {
        return _left;
    }
    /**
     * @brief
     *
     * @param left
     */
    void setLeft(double left)
    {
        _left = left;
    }

    /**
     * @brief
     *
     * @return double
     */
    double right() const
    {
        return _right;
    }
    /**
     * @brief
     *
     * @param right
     */
    void setRight(double right)
    {
        _right = right;
    }

    /**
     * @brief
     *
     * @return double
     */
    double top() const
    {
        return _top;
    }
    /**
     * @brief
     *
     * @param top
     */
    void setTop(double top)
    {
        _top = top;
    }

    /**
     * @brief
     *
     * @return double
     */
    double bottom() const
    {
        return _bottom;
    }
    /**
     * @brief
     *
     * @param bottom
     */
    void setBottom(double bottom)
    {
        _bottom = bottom;
    }

    /**
     * @brief
     *
     * @return double
     */
    double znear() const
    {
        return _znear;
    }
    /**
     * @brief
     *
     * @param znear
     */
    void setZnear(double znear)
    {
        _znear = znear;
    }

    /**
     * @brief
     *
     * @return double
     */
    double zfar() const
    {
        return _zfar;
    }
    /**
     * @brief
     *
     * @param zfar
     */
    void setZfar(double zfar)
    {
        _zfar = zfar;
    }

private:
    double _left; /**< TODO: describe */
    double _right; /**< TODO: describe */
    double _top; /**< TODO: describe */
    double _bottom; /**< TODO: describe */
    double _znear; /**< TODO: describe */
    double _zfar; /**< TODO: describe */
};

#endif // ORTHOGRAPHICFRUSTUM_H
