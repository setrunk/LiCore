#ifndef ELLIPSOIDALOCCLUDER_H
#define ELLIPSOIDALOCCLUDER_H

#include "licore_global.h"
#include "cartesian3.h"
#include "rectangle.h"

class Ellipsoid;

/**
 * @brief
 * 椭球遮挡体，用于快速计算地球上的物体是否被摄像机可见。
 */
class LICORE_EXPORT EllipsoidalOccluder
{
public:
    /**
     * @brief
     *
     * @param ellipsoid
     */
    EllipsoidalOccluder(Ellipsoid *ellipsoid);

    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 cameraPosition() const { return _cameraPosition; }
    /**
     * @brief
     *
     * @param position
     */
    void setCameraPosition(const Cartesian3 &position);

    /**
     * @brief
     *
     * @param occludee
     * @return bool
     */
    bool isPointVisible(const Cartesian3 &occludee) const;
    /**
     * @brief
     *
     * @param occludeeScaledSpacePosition
     * @return bool
     */
    bool isScaledSpacePointVisible(const Cartesian3 &occludeeScaledSpacePosition) const;

    /**
     * @brief
     *
     * @param directionToPoint
     * @param positions
     * @return Cartesian3
     */
    Cartesian3 computeHorizonCullingPoint(const Cartesian3 &directionToPoint, const QVector<Cartesian3> &positions) const;
    /**
     * @brief
     *
     * @param directionToPoint
     * @param vertices
     * @param stride
     * @param center
     * @return Cartesian3
     */
    Cartesian3 computeHorizonCullingPointFromVertices(const Cartesian3 &directionToPoint, const QVector<double> &vertices, int stride, const Cartesian3 &center) const;
    /**
     * @brief
     *
     * @param rectangle
     * @return Cartesian3
     */
    Cartesian3 computeHorizonCullingPointFromRectangle(const LiRectangle &rectangle) const;
    /**
     * @brief
     *
     * @param directionToPoint
     * @return Cartesian3
     */
    Cartesian3 computeScaledSpaceDirectionToPoint(const Cartesian3 &directionToPoint) const;
    /**
     * @brief
     *
     * @param scaledSpaceDirectionToPoint
     * @param resultMagnitude
     * @return Cartesian3
     */
    Cartesian3 magnitudeToPoint(const Cartesian3 &scaledSpaceDirectionToPoint, double resultMagnitude) const;
    /**
     * @brief
     *
     * @param position
     * @param scaledSpaceDirectionToPoint
     * @return double
     */
    double computeMagnitude(const Cartesian3 &position, const Cartesian3 &scaledSpaceDirectionToPoint) const;

private:
    Ellipsoid *_ellipsoid; /**< TODO: describe */
    Cartesian3 _cameraPosition; /**< TODO: describe */
    Cartesian3 _cameraPositionInScaledSpace; /**< TODO: describe */
    double _distanceToLimbInScaledSpaceSquared; /**< TODO: describe */
};

#endif // ELLIPSOIDALOCCLUDER_H
