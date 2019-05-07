#ifndef LIBOXOUTLINERENDERER_H
#define LIBOXOUTLINERENDERER_H

#include "ligeometryrenderer.h"

class LiBoxOutlineRendererPrivate;

class LiBoxOutlineRenderer : public LiGeometryRenderer
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiBoxOutlineRenderer)

public:
    explicit LiBoxOutlineRenderer(LiNode *parent = nullptr);

    Vector3 minimum() const;
    void setMinimum(const Vector3 &v);

    Vector3 maximum() const;
    void setMaximum(const Vector3 &v);

    void setPoints(const QVector<Vector3> &points);

    QColor color() const;
    void setColor(const QColor &color);
};

#endif // LIBOXOUTLINERENDERER_H
