#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include "licore_global.h"
#include "vector3.h"
#include "matrix4.h"

/**
 * @brief
 * 轴对齐包围盒AABB
 */
class LICORE_EXPORT AxisAlignedBoundingBox
{
public:
    AxisAlignedBoundingBox() {}

    /**
     * @brief
     * 构造函数
     * @param min
     * 最小坐标点
     * @param max
     * 最大坐标点
     * @param center
     * 指定中心点，如果不指定，中心点会被自动计算
     */
    AxisAlignedBoundingBox(const Vector3 &min, const Vector3 &max, const Vector3 &center = Vector3());

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator==(const AxisAlignedBoundingBox &other) const
    {
        return minimum == other.minimum &&
               maximum == other.maximum &&
               _center == other._center;
    }

    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    bool operator!=(const AxisAlignedBoundingBox &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief
     * 返回包围盒是否未被初始化
     * @return bool 未初始化返回true，否则返回false
     */
    bool isNull() const { return minimum.isNull() && maximum.isNull(); }

    /**
     * @brief
     * 返回包围盒是否可用
     * @return bool
     */
    bool isValid() const { return !isNull(); }

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 center() const { return _center.isNull() ? (maximum + minimum) * 0.5 : _center; }
    /**
     * @brief
     *
     * @param center
     */
    void setCenter(const Vector3 &center) { _center = center; }

    /**
     * @brief
     *
     * @return Vector3
     */
    Vector3 extent() const { return maximum - minimum; }

    /**
     * @brief
     *
     * @param points
     */
    void update(const QVector<Vector3> &points);
    /**
     * @brief
     *
     * @param p
     */
    void merge(const Vector3 &p);
    /**
     * @brief
     *
     * @param points
     */
    void merge(const QVector<Vector3> &points);
    /**
     * @brief
     *
     * @param other
     */
    void merge(const AxisAlignedBoundingBox &other);
    /**
     * @brief
     *
     * @param m
     */
    void transform(const Matrix4 &m);

    /**
     * @brief
     *
     * @param p
     * @return bool
     */
    bool contains(const Vector3 &p) const;
    /**
     * @brief
     *
     * @return QVector<Vector3>
     */
    QVector<Vector3> corners() const;

    /**
     * @brief
     *
     * @param points
     * @return AxisAlignedBoundingBox
     */
    static AxisAlignedBoundingBox fromPoints(const QVector<Cartesian3> &points);
    /**
     * @brief
     *
     * @param points
     * @return AxisAlignedBoundingBox
     */
    static AxisAlignedBoundingBox fromPoints(const QVector<Vector3> &points);

public:
    Vector3 minimum; /**< TODO: describe */
    Vector3 maximum; /**< TODO: describe */
    Vector3 _center; /**< TODO: describe */
};

typedef AxisAlignedBoundingBox AABB;

Q_DECLARE_METATYPE(AxisAlignedBoundingBox)

#endif // AXISALIGNEDBOUNDINGBOX_H
