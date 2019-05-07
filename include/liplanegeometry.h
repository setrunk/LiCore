#ifndef LIPLANEGEOMETRY_H
#define LIPLANEGEOMETRY_H

#include "ligeometry.h"

class LiPlaneGeometryPrivate;

class LICORE_EXPORT LiPlaneGeometry : public LiGeometry
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiPlaneGeometry)

public:
    explicit LiPlaneGeometry(LiNode *parent = nullptr);

    double width() const;
    void setWidth(double width);

    double height() const;
    void setHeight(double height);

    QSize resolution() const;
    void setResolution(const QSize &resolution);

    QSize tileUV() const;
    void setTileUV(const QSize &tileUV);

    void create();
};

#endif // LIPLANEGEOMETRY_H
