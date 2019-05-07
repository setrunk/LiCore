#ifndef TILEBOUNDINGBOX_H
#define TILEBOUNDINGBOX_H

#include "licore_global.h"
#include "rectangle.h"
#include "cartesian3.h"
#include "cartographic.h"
#include "boundingsphere.h"

/**
 * @brief
 * 制图空间的包围盒，由一个经纬度范围值（LiRectangle）和最低高度以及最高高度值组成。
 */
class LICORE_EXPORT TileBoundingBox
{
public:
    /**
     * @brief
     *
     */
    TileBoundingBox() : minimumHeight(0), maximumHeight(0) {}
    /**
     * @brief
     *
     * @param rect
     * @param minHeight
     * @param maxHeight
     */
    TileBoundingBox(const LiRectangle &rect, double minHeight = 0, double maxHeight = 0);

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const { return rectangle.isNull(); }
    /**
     * @brief
     *
     * @return bool
     */
    bool isValid() const { return !rectangle.isNull(); }

    /**
     * @brief
     *
     * @return BoundingSphere
     */
    BoundingSphere boundingSphere() const;
    /**
     * @brief
     *
     * @param cameraCartesianPosition
     * @param cameraCartographicPosition
     * @return double
     */
    double distanceToCamera(const Cartesian3 &cameraCartesianPosition, const Cartographic &cameraCartographicPosition) const;

public:
    LiRectangle rectangle; /**< TODO: describe */
    double minimumHeight; /**< TODO: describe */
    double maximumHeight; /**< TODO: describe */
    Cartesian3 westNormal; /**< TODO: describe */
    Cartesian3 southNormal; /**< TODO: describe */
    Cartesian3 eastNormal; /**< TODO: describe */
    Cartesian3 northNormal; /**< TODO: describe */
    Cartesian3 southwestCornerCartesian; /**< TODO: describe */
    Cartesian3 northeastCornerCartesian; /**< TODO: describe */
};

#endif // TILEBOUNDINGBOX_H
