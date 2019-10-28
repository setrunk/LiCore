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

/**
 * @brief
 * 摄像机类型，用于场景渲染的可视范围。
 */
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

    /**
     * @brief
     * 投影类型
     */
    enum ProjectionType {
        OrthographicProjection, //!< 正投投影
        PerspectiveProjection,  //!< 透视投影
        FrustumProjection,      //!< 视锥投影
        CustomProjection        //!< 自定义投影
    };
    Q_ENUM(ProjectionType)

    /**
     * @brief
     * 返回当前的投影类型
     * @return ProjectionType
     */
    ProjectionType projectionType() const;

    /**
     * @brief
     * 返回当前的近裁切距离
     * @return double
     */
    double nearPlane() const;

    /**
     * @brief
     * 返回当前的远裁切距离
     * @return double
     */
    double farPlane() const;

    /**
     * @brief
     * 返回当前的水平视锥角度
     * @return double 单位为度（degree）
     */
    double fieldOfView() const;

    /**
     * @brief
     * 返回当前的垂直视锥角度
     * @return double 单位为度（degree）
     */
    double fovy() const;

    /**
     * @brief
     * 返回当前的视口比例
     * @return double 等于视口宽度/视口高度
     */
    double aspectRatio() const;

    /**
     * @brief
     * 返回在摄像机坐标系中的左边空间距离（近裁切面）
     * @return double
     */
    double left() const;

    /**
     * @brief
     * 返回在摄像机坐标系中的右边空间距离（近裁切面）
     * @return double
     */
    double right() const;

    /**
     * @brief
     * 返回在摄像机坐标系中的下部空间距离（近裁切面）
     * @return double
     */
    double bottom() const;

    /**
     * @brief
     * 返回在摄像机坐标系中的上部空间距离（近裁切面）
     * @return double
     */
    double top() const;

    /**
     * @brief
     *
     * @return double
     */
    double sseDenominator() const;

    /**
     * @brief
     * 返回当前视口的像素宽度
     * @return int
     */
    Q_INVOKABLE int canvasWidth() const;

    /**
     * @brief
     * 返回当前视口的像素高度
     * @return int
     */
    Q_INVOKABLE int canvasHeight() const;

    /**
     * @brief
     * 返回当前视口的像素尺寸
     * @return QSize
     */
    Q_INVOKABLE QSize canvasSize() const;

    /**
     * @brief
     * 设置当前视口的像素尺寸
     * @param size
     */
    void setCanvasSize(const QSize &size);

    /**
     * @brief
     * 设置当前视口的像素尺寸
     * @param width
     * @param height
     */
    void setCanvasSize(int width, int height);

    /**
     * @brief
     * 返回当前的摄像机变换矩阵，从世界坐标系到摄像机坐标系的变换矩阵
     * @return Matrix4
     */
    Q_INVOKABLE Matrix4 viewMatrix() const;

    /**
     * @brief
     * 同viewMatrix()
     * @return Matrix4
     */
    Q_INVOKABLE Matrix4 worldToCameraMatrix() const;

    /**
     * @brief
     * 返回从当前摄像机坐标系到世界坐标系的变换矩阵
     * @return Matrix4
     */
    Q_INVOKABLE Matrix4 cameraToWorldMatrix() const;

    /**
     * @brief
     * 返回当前的摄像机的投影变换矩阵
     * @return Matrix4
     */
    Q_INVOKABLE Matrix4 projectionMatrix() const;

    /**
     * @brief
     * 返回当前的摄像机的视口正投变换矩阵
     * @return Matrix4
     */
    Q_INVOKABLE Matrix4 viewportOrthographic() const;

    /**
     * @brief
     * 返回包围球在视口中的像素大小
     * @param boundingSphere
     * @param drawingBufferWidth
     * @param drawingBufferHeight
     * @return double
     */
    Q_INVOKABLE double getPixelSize(const BoundingSphere &boundingSphere, int drawingBufferWidth, int drawingBufferHeight) const;

    /**
     * @brief
     * 返回三维空间的点经过投影变换后，在视口中的像素大小
     * @param drawingBufferWidth 视口宽度
     * @param drawingBufferHeight 视口高度
     * @param distance 距离摄像机近裁切面的空间距离
     * @return Cartesian2 在水平和垂直方向上的像素尺寸
     */
    Q_INVOKABLE Cartesian2 getPixelDimensions(int drawingBufferWidth, int drawingBufferHeight, double distance) const;

    /**
     * @brief
     * 飞到目标点
     * @param destination 三维空间的目标点
     * @param duration 飞行时间，单位为秒
     * @param heading 最终状态的转向角，单位为度
     * @param pitch 最终状态的俯仰角，单位为度
     * @param roll 最终状态的翻滚角，单位为度
     */
    Q_INVOKABLE void flyTo(const Vector3 &destination,
                           double duration = Math::EPSILON20,
                           double heading = 0,
                           double pitch = -90,
                           double roll = 0);
    /**
     * @brief
     * 飞到目标点
     * @param destination 制图空间的目标点
     * @param duration 飞行时间，单位为秒
     * @param heading 最终状态的转向角，单位为度
     * @param pitch 最终状态的俯仰角，单位为度
     * @param roll 最终状态的翻滚角，单位为度
     */
    Q_INVOKABLE void flyTo(const Cartographic &destination,
                           double duration = Math::EPSILON20,
                           double heading = 0,
                           double pitch = -90,
                           double roll = 0);
    /**
     * @brief
     * 飞到目标点，令摄像机可以观看一定的范围
     * @param destination 最终状态的摄像机观看范围
     * @param duration 飞行时间，单位为秒
     * @param heading 最终状态的转向角，单位为度
     * @param pitch 最终状态的俯仰角，单位为度
     * @param roll 最终状态的翻滚角，单位为度
     */
    Q_INVOKABLE void flyTo(const LiRectangle &destination,
                           double duration = Math::EPSILON20,
                           double heading = 0,
                           double pitch = -90,
                           double roll = 0);

    /**
     * @brief
     * 计算从摄像机位置到屏幕点的射线
     * @param x 屏幕点的X坐标
     * @param y 屏幕点的Y坐标
     * @return Ray 射线
     */
    Q_INVOKABLE Ray screenPointToRay(int x, int y) const;

    /**
     * @brief
     * 同screenPointToRay(int x, int y)
     * @param position
     * @return Ray
     */
    Q_INVOKABLE Ray screenPointToRay(const QPoint &position) const;

    /**
     * @brief
     * 计算屏幕点对应的世界坐标
     * @param position 屏幕点，Z值为深度值
     * @return Vector3 世界坐标点
     */
    Q_INVOKABLE Vector3 screenToWorldPoint(const Vector3 &position) const;

    /**
     * @brief
     * 计算世界坐标点在视口屏幕上的坐标
     * @param position 世界坐标点
     * @return Vector3 屏幕点，Z值为深度值
     */
    Q_INVOKABLE Vector3 worldToScreenPoint(const Vector3 &position) const;

    /**
     * @brief
     * 计算当前摄像机的裁切视锥
     * @return CullingVolume
     */
    CullingVolume computeCullingVolume() const;

    /**
     * @brief
     * 返回setCameraController函数设置的对象
     * @return LiCameraController
     */
    LiCameraController *cameraController() const;

    /**
     * @brief
     * 设置摄像机的控制对象
     * @param cameraController
     */
    void setCameraController(LiCameraController *cameraController);

    /**
     * @brief
     * 返回当前用于渲染的摄像机
     * @return LiCamera
     */
    static LiCamera *current();

    /**
     * @brief
     * 返回场景的主摄像机
     * @return LiCamera
     */
    static LiCamera *main();

    /**
     * @brief
     * 返回场景所有的摄像机合集
     * @return QList<LiCamera *>
     */
    static QList<LiCamera*> allCameras();

public Q_SLOTS:
    /**
     * @brief
     * 设置摄像机投影类型
     * @param projectionType
     */
    void setProjectionType(ProjectionType projectionType);

    /**
     * @brief
     * 设置摄像机的近裁切距离
     * @param nearPlane
     */
    void setNearPlane(double nearPlane);

    /**
     * @brief
     * 设置摄像机的远裁切距离
     * @param farPlane
     */
    void setFarPlane(double farPlane);

    /**
     * @brief
     * 设置摄像机的水平视角，单位为度
     * @param fieldOfView
     */
    void setFieldOfView(double fieldOfView);

    /**
     * @brief
     * 设置摄像机的渲染视口宽高比，当渲染视口大小改变时，必须调用此函数设置宽高比
     * @param aspectRatio 视口宽度/视口高度
     */
    void setAspectRatio(double aspectRatio);

    /**
     * @brief
     * 设置摄像机的近裁切面的左距离
     * @param left
     */
    void setLeft(double left);

    /**
     * @brief
     * 设置摄像机的近裁切面的右距离
     * @param right
     */
    void setRight(double right);

    /**
     * @brief
     * 设置摄像机的近裁切面的下距离
     * @param bottom
     */
    void setBottom(double bottom);

    /**
     * @brief
     * 设置摄像机的近裁切面的上距离
     * @param top
     */
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
