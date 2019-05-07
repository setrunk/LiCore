#ifndef LITEXTUREPROJECTION_H
#define LITEXTUREPROJECTION_H

#include "ligeometryrenderer.h"

class LiTexture;
class LiTextureProjectionPrivate;

class LICORE_EXPORT LiTextureProjection : public LiGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(ProjectionType projectionType READ projectionType WRITE setProjectionType NOTIFY projectionTypeChanged)
    Q_PROPERTY(BlendMode blendMode READ blendMode WRITE setBlendMode NOTIFY blendModeChanged)
    Q_PROPERTY(SceneMode sceneMode READ sceneMode WRITE setSceneMode NOTIFY sceneModeChanged)
    Q_PROPERTY(LiTexture* texture READ texture WRITE setTexture NOTIFY textureChanged)
    Q_PROPERTY(bool textureFlip READ textureFlip WRITE setTextureFlip NOTIFY textureFlipChanged)
    Q_PROPERTY(bool showFrustum READ showFrustum WRITE setShowFrustum NOTIFY showFrustumChanged)
    Q_PROPERTY(double nearPlane READ nearPlane WRITE setNearPlane NOTIFY nearPlaneChanged)
    Q_PROPERTY(double farPlane READ farPlane WRITE setFarPlane NOTIFY farPlaneChanged)
    Q_PROPERTY(double width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(double height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(double fov READ fov WRITE setFov NOTIFY fovChanged)
    Q_PROPERTY(double aspect READ aspect WRITE setAspect NOTIFY aspectChanged)
public:
    enum ProjectionType
    {
        Orthographic,
        Perspective
    };
    Q_ENUM(ProjectionType)

    enum BlendMode
    {
        Opaque,
        AlphaBlend,
        AdditiveBlend
    };
    Q_ENUM(BlendMode)

    enum SceneMode
    {
        TerrainOnly,
        WholeScene
    };
    Q_ENUM(SceneMode)

    explicit LiTextureProjection(LiNode *parent = nullptr);

    ProjectionType projectionType() const;
    void setProjectionType(ProjectionType type);

    BlendMode blendMode() const;
    void setBlendMode(BlendMode mode);

    SceneMode sceneMode() const;
    void setSceneMode(SceneMode mode);

    LiTexture *texture() const;
    void setTexture(LiTexture *texture);

    // mirror the image vertically
    bool textureFlip() const;
    void setTextureFlip(bool flip);

    // show frustum volume
    bool showFrustum() const;
    void setShowFrustum(bool show);

    // near clip distance
    double nearPlane() const;
    void setNearPlane(double znear);

    // far clip distance
    double farPlane() const;
    void setFarPlane(double zfar);

    // for Orthographic type
    double width() const;
    void setWidth(double width);

    // for Orthographic type
    double height() const;
    void setHeight(double height);

    // for Perspective type
    double fov() const;
    void setFov(double fov);

    // for Perspective type
    double aspect() const;
    void setAspect(double aspect);

    void setOrthographicFrustum(double width, // default 10.0, in camera space
                                double height, // default 10.0, in camera space
                                double znear = -1.0, // default 1.0, in camera space, -1.0 means don't set near plane
                                double zfar = -1.0); // default 1000.0, in camera space, -1.0 means don't set far plane

    void setPerspectiveFrustum(double fov,  // the horizontal field of view in degrees, default 60
                               double aspect, // default 1.0
                               double znear = -1.0, // default 1.0, in camera space, -1.0 means don't set near plane
                               double zfar = -1.0); // default 1000.0, in camera space, -1.0 means don't set far plane

    Matrix4 viewMatrix() const;
    Matrix4 projectionMatrix() const;

signals:
    void projectionTypeChanged(ProjectionType type);
    void blendModeChanged(BlendMode blendMode);
    void sceneModeChanged(SceneMode blendMode);
    void textureChanged(LiTexture *texture);
    void textureFlipChanged(bool textureFlip);
    void showFrustumChanged(bool showFrustum);
    void nearPlaneChanged(double nearPlane);
    void farPlaneChanged(double farPlane);
    void widthChanged(double width);
    void heightChanged(double height);
    void fovChanged(double fov);
    void aspectChanged(double aspect);

private:
    Q_DECLARE_PRIVATE(LiTextureProjection)
};

#endif // LITEXTUREPROJECTION_H
