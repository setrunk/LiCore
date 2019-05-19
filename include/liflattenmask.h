#ifndef LIFLATTENMASK_H
#define LIFLATTENMASK_H

#include "linode.h"
#include "vector3.h"
#include "cartographic.h"
#include "rectangle.h"

class LiFlattenMaskPrivate;

class LICORE_EXPORT LiFlattenMask : public LiNode
{
    Q_OBJECT
public:
    explicit LiFlattenMask(LiNode *parent = nullptr);

    QVector<Vector3> points() const;
    void setPoints(const QVector<Vector3> &points);

    double maskHeight() const;
    void setMaskHeight(double maskHeight);

    LiRectangle extent() const;
    QVector<Cartographic> cartographicPositions() const;

    bool showDebugOutline() const;
    void setShowDebugOutline(bool show);

signals:
    void pointsChanged();
    void maskHeightChanged(double height);

public slots:
    /**
     * @brief
     * 在qml/js中设置点数据，类型为Array, 如：
     * var flattenMask;
     * // ... 初始化flattenMask
     * var points = [x0, y0, z0, x1, y1, z1, x2, y2, z2 ...];
     * flattenMask.setData(points);
     */
    void setData(const QJSValue &data);

private:
    Q_DECLARE_PRIVATE(LiFlattenMask)
};

#endif // LIFLATTENMASK_H
