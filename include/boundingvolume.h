#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include "licore_global.h"
#include "boundingsphere.h"
#include "orientedboundingbox.h"
#include "boundingregion.h"
#include "intersect.h"

class BoundingVolumePrivate;
class CullingVolume;

/**
 * @brief
 * BoundingVolume包围体，是为了统一BoundingSphere, BoundingBox, BoundingRegion的接口。
 * 可以通过这三种方式之一来定义包围体，当用于计算的时候，会自动使用构造体去计算。
 */
class LICORE_EXPORT BoundingVolume
{
public:
    /**
     * @brief
     *
     */
    BoundingVolume();
    /**
     * @brief
     *
     * @param sphere
     */
    explicit BoundingVolume(const BoundingSphere &sphere);
    /**
     * @brief
     *
     * @param box
     */
    explicit BoundingVolume(const OrientedBoundingBox &box);
    /**
     * @brief
     *
     * @param region
     */
    explicit BoundingVolume(const BoundingRegion &region);
    /**
     * @brief
     *
     * @param region
     * @param minHeight
     * @param maxHeight
     */
    BoundingVolume(const LiRectangle &region, double minHeight = 0, double maxHeight = 0);
    /**
     * @brief
     *
     * @param o
     */
    BoundingVolume(const BoundingVolume &o);
    /**
     * @brief
     *
     * @param o
     * @return BoundingVolume &operator
     */
    BoundingVolume &operator =(const BoundingVolume &o);

    /**
     * @brief
     *
     * @param box
     */
    void reset(const OrientedBoundingBox &box);
    /**
     * @brief
     *
     * @param region
     */
    void reset(const BoundingRegion &region);
    /**
     * @brief
     *
     * @param region
     * @param minHeight
     * @param maxHeight
     */
    void reset(const LiRectangle &region, double minHeight = 0, double maxHeight = 0);

    /**
     * @brief
     *
     * @return BoundingSphere
     */
    BoundingSphere boundingSphere() const;
    /**
     * @brief
     *
     * @return OrientedBoundingBox
     */
    OrientedBoundingBox orientedBoundingBox() const;
    /**
     * @brief
     *
     * @return BoundingRegion
     */
    BoundingRegion boundingRegion() const;
    /**
     * @brief
     *
     * @return LiRectangle
     */
    LiRectangle rectangle() const;
    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 center() const;

    /**
     * @brief
     *
     * @return bool
     */
    bool isNull() const;
    /**
     * @brief
     *
     * @return bool
     */
    bool isValid() const;

    /**
     * @brief
     *
     * @return bool
     */
    bool isFromSphere() const;
    /**
     * @brief
     *
     * @return bool
     */
    bool isFromBox() const;
    /**
     * @brief
     *
     * @return bool
     */
    bool isFromRegion() const;

    /**
     * @brief
     *
     * @param o
     */
    void merge(const BoundingVolume &other);

    /**
     * @brief
     *
     * @param positionCartesian
     * @param positionCartographic
     * @return double
     */
    double distanceTo(const Cartesian3 &positionCartesian,
                      const Cartographic &positionCartographic) const;

    /**
     * @brief
     *
     * @param plane
     * @return Intersect::Result
     */
    Intersect::Result intersectPlane(const Plane &plane) const;
    /**
     * @brief
     *
     * @param cullingVolume
     * @return Intersect::Result
     */
    Intersect::Result computeVisibility(const CullingVolume &cullingVolume) const;

    /**
     * @brief
     *
     * @param source
     */
    void clone(const BoundingVolume &source);

private:
    QSharedPointer<BoundingVolumePrivate> d; /**< TODO: describe */
};

Q_DECLARE_METATYPE(BoundingVolume)

#endif // BOUNDINGVOLUME_H
