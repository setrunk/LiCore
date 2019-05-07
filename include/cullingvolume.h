#ifndef CULLINGVOLUME_H
#define CULLINGVOLUME_H

#include "licore_global.h"
#include "plane.h"
#include "intersect.h"
#include "boundingsphere.h"
#include "axisalignedboundingbox.h"
#include "orientedboundingbox.h"
#include "boundingvolume.h"

/**
 * @brief
 * 裁切体，用于渲染前摄像机视锥对场景物体是否可见的计算。
 * CullingVolume由六个面（Plane）组成，可以计算各种包围体的可见性。
 */
class LICORE_EXPORT CullingVolume
{
public:
    /**
     * @brief
     *
     */
    enum Mask
    {
        MASK_OUTSIDE = 0xffffffff,
        MASK_INSIDE = 0x00000000,
        MASK_INDETERMINATE = 0x7fffffff
    };

    /**
     * @brief
     *
     */
    CullingVolume();

    /**
     * @brief
     *
     * @return QVector<Plane>
     */
    QVector<Plane> planes() const { return _planes; }
    /**
     * @brief
     *
     * @param plane
     */
    void addPlane(const Plane &plane) { _planes.push_back(plane); }
    /**
     * @brief
     *
     * @param i
     * @param plane
     */
    void setPlane(int i, const Plane &plane) { _planes[i] = plane; }
    /**
     * @brief
     *
     * @param planes
     */
    void setPlanes(const QVector<Plane> &planes) { _planes = planes; }

    /**
     * @brief
     *
     * @param sphere
     * @return Intersect::Result
     */
    Intersect::Result computeVisibility(const BoundingSphere &sphere) const;
    /**
     * @brief
     *
     * @param box
     * @return Intersect::Result
     */
    Intersect::Result computeVisibility(const AxisAlignedBoundingBox &box) const;
    /**
     * @brief
     *
     * @param box
     * @return Intersect::Result
     */
    Intersect::Result computeVisibility(const OrientedBoundingBox &box) const;

    /**
     * @brief
     *
     * @param boundingVolume
     * @param parentPlaneMask
     * @return uint
     */
    uint computeVisibilityWithPlaneMask(const BoundingVolume &boundingVolume, uint parentPlaneMask) const;

    /**
     * @brief
     *
     * @param sphere
     * @return bool
     */
    bool isVisible(const BoundingSphere &sphere) const;
    /**
     * @brief
     *
     * @param box
     * @return bool
     */
    bool isVisible(const AxisAlignedBoundingBox &box) const;
    /**
     * @brief
     *
     * @param box
     * @return bool
     */
    bool isVisible(const OrientedBoundingBox &box) const;

private:
    QVector<Plane> _planes; /**< TODO: describe */
};

#endif // CULLINGVOLUME_H
