#ifndef PERSPECTIVEFRUSTUM_H
#define PERSPECTIVEFRUSTUM_H

#include "licore_global.h"
#include "matrix4.h"
#include "cullingvolume.h"
#include "cartesian2.h"
#include "cartesian3.h"
#include "cartesian4.h"

/**
 * @brief
 * 透视式视锥体，定义摄像机的可视范围，用于计算视锥裁切体以及透视变换矩阵。
 */
class LICORE_EXPORT PerspectiveFrustum
{
public:
    /**
     * @brief
     *
     */
    PerspectiveFrustum();
    /**
     * @brief
     *
     * @param fov
     * @param aspect
     * @param znear
     * @param zfar
     */
    PerspectiveFrustum(double fov, double aspect, double znear, double zfar);

    /**
     * @brief
     * 水平方向的可视角度，单位为度（degree）
     * @return double
     */
    double fov() const { return _fov; }

    /**
     * @brief
     * 垂直方向的可视角度，单位为度（degree）
     * @return double
     */
    double fovy() const { return _fovy; }

    /**
     * @brief
     *
     * @param fov
     */
    void setFov(double fov);

    /**
     * @brief
     *
     * @return double
     */
    double nearPlane() const { return _nearPlane; }
    /**
     * @brief
     *
     * @param nearPlane
     */
    void setNearPlane(double nearPlane);

    /**
     * @brief
     *
     * @return double
     */
    double farPlane() const { return _farPlane; }
    /**
     * @brief
     *
     * @param farPlane
     */
    void setFarPlane(double farPlane);

    /**
     * @brief
     *
     * @return double
     */
    double aspectRatio() const { return _aspectRatio; }
    /**
     * @brief
     *
     * @param aspectRatio
     */
    void setAspectRatio(double aspectRatio);

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

private:
    double _fov; /**< TODO: describe */
    double _fovy; /**< TODO: describe */
    double _aspectRatio; /**< TODO: describe */
    double _nearPlane; /**< TODO: describe */
    double _farPlane; /**< TODO: describe */
    mutable bool _dirty; /**< TODO: describe */
    mutable Matrix4 _projectionMatrix; /**< TODO: describe */
};

#endif // PERSPECTIVEFRUSTUM_H
