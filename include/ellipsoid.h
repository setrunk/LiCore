#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "licore_global.h"
#include "cartesian3.h"
#include "cartographic.h"
#include "quaternion.h"

/**
 * @brief
 * 三维椭球体，椭球体上的任意点(x,y,z)符合公式<code>(x / a)^2 + (y / b)^2 + (z / c)^2 = 1</code>。
 * 用来表达地球的几何形状，以及WGS84坐标的定义。
 */
class LICORE_EXPORT Ellipsoid : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Vector3 radii READ radii)
    Q_PROPERTY(Vector3 radiiSquared READ radiiSquared)
    Q_PROPERTY(Vector3 radiiToTheFourth READ radiiToTheFourth)
    Q_PROPERTY(Vector3 oneOverRadii READ oneOverRadii)
    Q_PROPERTY(Vector3 oneOverRadiiSquared READ oneOverRadiiSquared)
    Q_PROPERTY(double minimumRadius READ minimumRadius)
    Q_PROPERTY(double maximumRadius READ maximumRadius)
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit Ellipsoid(QObject *parent = 0);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param z
     * @param parent
     */
    Ellipsoid(double x, double y, double z, QObject *parent = 0);

    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 radii() const;
    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 radiiSquared() const;
    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 radiiToTheFourth() const;
    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 oneOverRadii() const;
    /**
     * @brief
     *
     * @return Cartesian3
     */
    Cartesian3 oneOverRadiiSquared() const;
    /**
     * @brief
     *
     * @return double
     */
    double minimumRadius() const;
    /**
     * @brief
     *
     * @return double
     */
    double maximumRadius() const;

    /**
     * @brief
     *
     * @param cartographic
     * @return Cartesian3
     */
    Q_INVOKABLE Cartesian3 cartographicToCartesian(const Cartographic &cartographic) const;
    /**
     * @brief
     *
     * @param cartesian
     * @return Cartographic
     */
    Q_INVOKABLE Cartographic cartesianToCartographic(const Cartesian3 &cartesian) const;

    /**
     * @brief
     *
     * @param cartographic
     * @return Cartesian3
     */
    Q_INVOKABLE Cartesian3 geodeticSurfaceNormalCartographic(const Cartographic &cartographic) const;
    /**
     * @brief
     *
     * @param position
     * @return Cartesian3
     */
    Q_INVOKABLE Cartesian3 transformPositionToScaledSpace(const Cartesian3 &position) const;
    /**
     * @brief
     *
     * @param cartesian
     * @return Cartesian3
     */
    Q_INVOKABLE Cartesian3 scaleToGeocentricSurface(const Cartesian3 &cartesian) const;
    /**
     * @brief
     *
     * @param position
     * @param buffer
     * @return Cartesian3
     */
    Q_INVOKABLE Cartesian3 getSurfaceNormalIntersectionWithZAxis(const Cartesian3 &position, double buffer = 0) const;
    /**
     * @brief
     *
     * @param cartesian
     * @return Cartesian3
     */
    Q_INVOKABLE Cartesian3 geodeticSurfaceNormal(const Cartesian3 &cartesian) const;
    /**
     * @brief
     *
     * @param cartesian
     * @param oneOverRadii
     * @param oneOverRadiiSquared
     * @param centerToleranceSquared
     * @return Cartesian3
     */
    Q_INVOKABLE Cartesian3 scaleToGeodeticSurface(const Cartesian3 &cartesian,
                                                  const Cartesian3 &oneOverRadii,
                                                  const Cartesian3 &oneOverRadiiSquared,
                                                  double centerToleranceSquared) const;

    /**
     * @brief
     *
     * @param cartographics
     * @return QVector<Cartesian3>
     */
    QVector<Cartesian3> cartographicArrayToCartesianArray(const QVector<Cartographic> &cartographics) const;
    /**
     * @brief
     *
     * @param cartographic
     * @return Quaternion
     */
    Quaternion cartographicToRotation(const Cartographic &cartographic) const;

    /**
     * @brief
     *
     * @return Ellipsoid
     */
    static Ellipsoid *WGS84();
    /**
     * @brief
     *
     * @param cartesian
     * @return Ellipsoid
     */
    static Ellipsoid *fromCartesian3(const Cartesian3 &cartesian);

private:
    Cartesian3 _radii; /**< TODO: describe */
    Cartesian3 _radiiSquared; /**< TODO: describe */
    Cartesian3 _radiiToTheFourth; /**< TODO: describe */
    Cartesian3 _oneOverRadii; /**< TODO: describe */
    Cartesian3 _oneOverRadiiSquared; /**< TODO: describe */
    double _minimumRadius; /**< TODO: describe */
    double _maximumRadius; /**< TODO: describe */
    double _centerToleranceSquared; /**< TODO: describe */
    double _sqauredXOverSquaredZ; /**< TODO: describe */
};

#endif // ELLIPSOID_H
