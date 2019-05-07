#ifndef LIHEATMAP_H
#define LIHEATMAP_H

#include "ligeometryrenderer.h"

class LiHeatmapPrivate;

class LICORE_EXPORT LiHeatmap : public LiGeometryRenderer
{
    Q_OBJECT
public:
    explicit LiHeatmap(LiNode *parent = nullptr);

    double minValue() const;
    void setMinValue(double minValue);

    double maxValue() const;
    void setMaxValue(double maxValue);

    double radius() const;
    void setRadius(double radius);

    double cellSize() const;
    void setCellSize(double cellSize);

    LiRectangle rectangle() const;
    void setRectangle(const LiRectangle &rect);

    QVector<Vector4> data() const;
    void setData(const QVector<Vector4> &data);

    QColor color() const;
    void setColor(const QColor &color);

private:
    Q_DECLARE_PRIVATE(LiHeatmap)
};

#endif // LIHEATMAP_H
