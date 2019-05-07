#ifndef LISKYBOX_H
#define LISKYBOX_H

#include "ligeometryrenderer.h"

class LiSkyboxPrivate;

class LICORE_EXPORT LiSkybox : public LiGeometryRenderer
{
    Q_OBJECT
public:
    explicit LiSkybox(LiNode *parent = nullptr);

    Q_INVOKABLE void setPositiveX(const QString &url);
    Q_INVOKABLE void setNegativeX(const QString &url);
    Q_INVOKABLE void setPositiveY(const QString &url);
    Q_INVOKABLE void setNegativeY(const QString &url);
    Q_INVOKABLE void setPositiveZ(const QString &url);
    Q_INVOKABLE void setNegativeZ(const QString &url);

private:
    Q_DECLARE_PRIVATE(LiSkybox)
};

#endif // LISKYBOX_H
