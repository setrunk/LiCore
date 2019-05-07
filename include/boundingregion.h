#ifndef BOUNDINGREGION_H
#define BOUNDINGREGION_H

#include "orientedboundingbox.h"
#include "rectangle.h"

class BoundingRegionPrivate;

/**
 * @brief
 * BoundingRegion定义了三维球面坐标的空间范围。
 */
class LICORE_EXPORT BoundingRegion
{
public:
    /**
     * @brief
     *
     */
    BoundingRegion();
    /**
     * @brief
     *
     * @param region
     * @param minHeight
     * @param maxHeight
     */
    BoundingRegion(const LiRectangle &region, double minHeight = 0, double maxHeight = 0);
    /**
     * @brief
     *
     * @param min
     * @param max
     */
    BoundingRegion(const Cartographic &min, const Cartographic &max);
    /**
     * @brief
     *
     * @param other
     */
    BoundingRegion(const BoundingRegion &other);
    /**
     * @brief
     *
     * @param other
     * @return BoundingRegion &operator
     */
    BoundingRegion &operator =(const BoundingRegion &other);

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
     * @return LiRectangle
     */
    LiRectangle rectangle() const;
    /**
     * @brief
     *
     * @return double
     */
    double minimumHeight() const;
    /**
     * @brief
     *
     * @return double
     */
    double maximumHeight() const;

    /**
     * @brief
     *
     * @param cartographic
     * @return bool
     */
    bool contains(const Cartographic &cartographic) const;
    /**
     * @brief
     *
     * @param o
     */
    void combine(const BoundingRegion &o);

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
     * @param source
     */
    void clone(const BoundingRegion &source);

    /**
     * @brief
     *
     * @param box
     * @return BoundingRegion
     */
    static BoundingRegion fromOrientedBoundingBox(const OrientedBoundingBox &box);

private:
    QSharedPointer<BoundingRegionPrivate> d; /**< TODO: describe */
};

Q_DECLARE_METATYPE(BoundingRegion)

#endif // BOUNDINGREGION_H
