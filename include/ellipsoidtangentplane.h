#ifndef ELLIPSOIDTANGENTPLANE_H
#define ELLIPSOIDTANGENTPLANE_H

#include "licore_global.h"
#include "cartesian2.h"
#include "cartesian3.h"
#include "cartographic.h"
#include "plane.h"
#include "ellipsoid.h"

/**
 * @brief
 * 椭球切面，表达椭球上的任意点所在的水平切面。
 */
class LICORE_EXPORT EllipsoidTangentPlane
{
public:
    /**
     * @brief
     *
     * @param origin
     * @param ellipsoid
     */
    EllipsoidTangentPlane(const Cartesian3 &origin, Ellipsoid *ellipsoid = Ellipsoid::WGS84());

    /**
     * @brief
     *
     * @param cartesian
     * @return Cartesian2
     */
    Cartesian2 projectPointToNearestOnPlane(const Cartesian3 &cartesian) const;
    /**
     * @brief
     *
     * @param cartesians
     * @return QVector<Cartesian2>
     */
    QVector<Cartesian2> projectPointsToNearestOnPlane(const QVector<Cartesian3> &cartesians) const;
    /**
     * @brief
     *
     * @param cartesians
     * @return QVector<Cartesian3>
     */
    QVector<Cartesian3> projectPointsOntoEllipsoid(const QVector<Cartesian3> &cartesians) const;

    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 xAxis() const { return _xAxis; }
    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 yAxis() const { return _yAxis; }
    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 zAxis() const { return _plane.normal; }
    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 origin() const { return _origin; }
    /**
     * @brief
     *
     * @return Plane
     */
    Plane plane() const { return _plane; }

private:
    Ellipsoid *_ellipsoid; /**< TODO: describe */
    Cartesian3 _origin; /**< TODO: describe */
    Cartesian3 _xAxis; /**< TODO: describe */
    Cartesian3 _yAxis; /**< TODO: describe */
    Plane _plane; /**< TODO: describe */
};

#endif // ELLIPSOIDTANGENTPLANE_H
