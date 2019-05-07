#ifndef LIFOREST_H
#define LIFOREST_H

#include "ligeometryrenderer.h"
#include "vector3.h"

class LiForestPrivate;

class LICORE_EXPORT LiForest : public LiGeometryRenderer
{
    Q_OBJECT
public:
    enum HeightMode
    {
        None = 0,
        ClampToGround = 1,
        RelativeToGround = 2
    };

    explicit LiForest(LiNode *parent = nullptr);
    virtual ~LiForest();

    HeightMode heightMode() const;
    void setHeightMode(HeightMode heightMode);

    double altitude() const;
    void setAltitude(double altitude);

    double scale() const;
    void setScale(double scale);

    void add(const QString &name, int count, const Cartographic *pos, const double *rotation, const double *scale);

    Q_INVOKABLE void setBaseUrl(const QUrl &url);
    Q_INVOKABLE bool load(const QUrl &url);

private:
    Q_DECLARE_PRIVATE(LiForest)
};

#endif // LIFOREST_H
