#ifndef OCCLUDER_H
#define OCCLUDER_H

#include "licore_global.h"
#include "cartesian3.h"
#include "boundingsphere.h"
#include "intersect.h"
#include "rectangle.h"

class Ellipsoid;

/**
 * @brief
 * 遮挡体。
 */
class LICORE_EXPORT Occluder
{
public:
    /**
     * @brief
     *
     */
    Occluder();
    /**
     * @brief
     *
     * @param occluderBoundingSphere
     * @param cameraPosition
     */
    Occluder(const BoundingSphere &occluderBoundingSphere, const Cartesian3 &cameraPosition);

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
    bool isPointVisible(const Cartesian3 &occludee);
    /**
     * @brief
     *
     * @param occludee
     * @return bool
     */
    bool isBoundingSphereVisible(const BoundingSphere &occludee);
    /**
     * @brief
     *
     * @param occludeeBS
     * @return Intersect::Result
     */
    Intersect::Result computeVisibility(const BoundingSphere &occludeeBS);

    /**
     * @brief
     *
     * @param occluderBoundingSphere
     * @param occludeePosition
     * @param positions
     * @param result
     * @return bool
     */
    static bool computeOccludeePoint(const BoundingSphere &occluderBoundingSphere,
                                     const Cartesian3 &occludeePosition,
                                     const QVector<Cartesian3> &positions,
                                     Cartesian3 *result);
    /**
     * @brief
     *
     * @param rectangle
     * @param ellipsoid
     * @return bool
     */
    static bool computeOccludeePointFromRectangle(const LiRectangle &rectangle, Ellipsoid *ellipsoid);

    /**
     * @brief
     *
     * @param occluderPosition
     * @param occluderPlaneNormal
     * @param occluderPlaneD
     * @return Cartesian3
     */
    static Cartesian3 anyRotationVector(const Cartesian3 &occluderPosition,
                                        const Cartesian3 &occluderPlaneNormal,
                                        double occluderPlaneD);
    /**
     * @brief
     *
     * @param occluderPosition
     * @param occluderPlaneNormal
     * @param position
     * @param anyRotationVector
     * @return Cartesian3
     */
    static Cartesian3 rotationVector(const Cartesian3 &occluderPosition,
                                     const Cartesian3 &occluderPlaneNormal,
                                     const Cartesian3 &position,
                                     const Cartesian3 &anyRotationVector);
    /**
     * @brief
     *
     * @param occluderBS
     * @param occluderPlaneNormal
     * @param anyRotationVector
     * @param position
     * @return double
     */
    static double horizonToPlaneNormalDotProduct(const BoundingSphere &occluderBS,
                                                 const Cartesian3 &occluderPlaneNormal,
                                                 const Cartesian3 &anyRotationVector,
                                                 const Cartesian3 &position);

private:
    Cartesian3 _occluderPosition; /**< TODO: describe */
    double _occluderRadius; /**< TODO: describe */
    double _horizonDistance; /**< TODO: describe */
    Cartesian3 _horizonPlaneNormal; /**< TODO: describe */
    Cartesian3 _horizonPlanePosition; /**< TODO: describe */
    Cartesian3 _cameraPosition; /**< TODO: describe */
};

#endif // OCCLUDER_H
