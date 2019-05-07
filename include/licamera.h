#ifndef LICAMERA_H
#define LICAMERA_H

#include "licomponent.h"
#include "matrix4.h"
#include "boundingsphere.h"
#include "cullingvolume.h"
#include "rectangle.h"
#include "ray.h"

class CullingVolume;
class LiCameraPrivate;
class LiCameraController;

class LICORE_EXPORT LiCamera : public LiComponent
{
    Q_OBJECT
    Q_PROPERTY(ProjectionType projectionType READ projectionType WRITE setProjectionType NOTIFY projectionTypeChanged)
    Q_PROPERTY(double nearPlane READ nearPlane WRITE setNearPlane NOTIFY nearPlaneChanged)
    Q_PROPERTY(double farPlane READ farPlane WRITE setFarPlane NOTIFY farPlaneChanged)
    Q_PROPERTY(double fieldOfView READ fieldOfView WRITE setFieldOfView NOTIFY fieldOfViewChanged)
    Q_PROPERTY(double fov READ fieldOfView WRITE setFieldOfView NOTIFY fieldOfViewChanged)
    Q_PROPERTY(double fovy READ fovy)
    Q_PROPERTY(double aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)
    Q_PROPERTY(double left READ left WRITE setLeft NOTIFY leftChanged)
    Q_PROPERTY(double right READ right WRITE setRight NOTIFY rightChanged)
    Q_PROPERTY(double bottom READ bottom WRITE setBottom NOTIFY bottomChanged)
    Q_PROPERTY(double top READ top WRITE setTop NOTIFY topChanged)
    Q_PROPERTY(Matrix4 projectionMatrix READ projectionMatrix NOTIFY projectionMatrixChanged)
    Q_PROPERTY(LiCameraController *cameraController READ cameraController)
public:
    explicit LiCamera(LiNode *parent = nullptr);
    ~LiCamera();

    enum ProjectionType {
        OrthographicProjection,
        PerspectiveProjection,
        FrustumProjection,
        CustomProjection
    };
    Q_ENUM(ProjectionType)

    ProjectionType projectionType() const;
    double nearPlane() const;
    double farPlane() const;
    double fieldOfView() const; // degrees
    double fovy() const; // degrees
    double aspectRatio() const;
    double left() const;
    double right() const;
    double bottom() const;
    double top() const;
    double sseDenominator() const;

    Q_INVOKABLE int canvasWidth() const;
    Q_INVOKABLE int canvasHeight() const;
    Q_INVOKABLE QSize canvasSize() const;
    void setCanvasSize(const QSize &size);
    void setCanvasSize(int width, int height);

    Q_INVOKABLE Matrix4 viewMatrix() const;
    Q_INVOKABLE Matrix4 worldToCameraMatrix() const; // same as viewMatrix()
    Q_INVOKABLE Matrix4 cameraToWorldMatrix() const;
    Q_INVOKABLE Matrix4 projectionMatrix() const;
    Q_INVOKABLE Matrix4 viewportOrthographic() const;

    Q_INVOKABLE double getPixelSize(const BoundingSphere &boundingSphere, int drawingBufferWidth, int drawingBufferHeight) const;
    Q_INVOKABLE Cartesian2 getPixelDimensions(int drawingBufferWidth, int drawingBufferHeight, double distance) const;

    Q_INVOKABLE void flyTo(const Vector3 &destination, double duration  = Math::EPSILON20, double heading = 0, double pitch = -90, double roll = 0);
    Q_INVOKABLE void flyTo(const Cartographic &destination, double duration  = Math::EPSILON20, double heading = 0, double pitch = -90, double roll = 0);
    Q_INVOKABLE void flyTo(const LiRectangle &destination, double duration  = Math::EPSILON20, double heading = 0, double pitch = -90, double roll = 0);

    Q_INVOKABLE Ray screenPointToRay(int x, int y) const;
    Q_INVOKABLE Ray screenPointToRay(const QPoint &position) const;
    Q_INVOKABLE Vector3 screenToWorldPoint(const Vector3 &position) const;
    Q_INVOKABLE Vector3 worldToScreenPoint(const Vector3 &position) const;

    CullingVolume computeCullingVolume() const;

    LiCameraController *cameraController() const;
    void setCameraController(LiCameraController *cameraController);

    static LiCamera *current();
    static LiCamera *main();
    static QList<LiCamera*> allCameras();

public Q_SLOTS:
    void setProjectionType(ProjectionType projectionType);
    void setNearPlane(double nearPlane);
    void setFarPlane(double farPlane);
    void setFieldOfView(double fieldOfView);
    void setAspectRatio(double aspectRatio);
    void setLeft(double left);
    void setRight(double right);
    void setBottom(double bottom);
    void setTop(double top);

Q_SIGNALS:
    void projectionTypeChanged(LiCamera::ProjectionType projectionType);
    void nearPlaneChanged(double nearPlane);
    void farPlaneChanged(double farPlane);
    void fieldOfViewChanged(double fieldOfView);
    void aspectRatioChanged(double aspectRatio);
    void leftChanged(double left);
    void rightChanged(double right);
    void bottomChanged(double bottom);
    void topChanged(double top);
    void projectionMatrixChanged(const Matrix4 &projectionMatrix);
    void completeFlight();

protected:
    explicit LiCamera(LiCameraPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiCamera)
};

#endif // LICAMERA_H
