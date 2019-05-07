#ifndef LICAMERACONTROLLER_H
#define LICAMERACONTROLLER_H

#include "libehavior.h"
#include "cartographic.h"
#include "ray.h"
#include "rectangle.h"

/**
 * @brief 根据窗口的鼠标输入修改相机位置和方向
 *
 */
class LICORE_EXPORT LiCameraController : public LiBehavior
{
    Q_OBJECT
    Q_PROPERTY(bool enableInputs READ enableInputs WRITE setEnableInputs)
    Q_PROPERTY(bool enableZoom READ enableZoom WRITE setEnableZoom)
    Q_PROPERTY(bool enableRotate READ enableRotate WRITE setEnableRotate)
    Q_PROPERTY(bool enableTilt READ enableTilt WRITE setEnableTilt)
    Q_PROPERTY(bool enableLook READ enableLook WRITE setEnableLook)
    Q_PROPERTY(bool enableUnderGround READ enableUnderGround WRITE setEnableUnderGround)
    Q_PROPERTY(bool enablePan READ enablePan WRITE setEnablePan)
    Q_PROPERTY(bool minimumCollisionTerrainHeight READ minimumCollisionTerrainHeight WRITE setMinimumCollisionTerrainHeight)
    Q_PROPERTY(Vector3 positionWC READ positionWC)
    Q_PROPERTY(Vector3 rightWC READ rightWC)
    Q_PROPERTY(Vector3 directionWC READ directionWC)
    Q_PROPERTY(Vector3 upWC READ upWC)
    Q_PROPERTY(Cartographic positionCartographic READ positionCartographic)
    Q_PROPERTY(double heading READ heading)
    Q_PROPERTY(double pitch READ pitch)
    Q_PROPERTY(double roll READ roll)

public:
    /**
     * @brief 构造函数
     *
     * @param parent 父类指针
     */
    explicit LiCameraController(LiNode *parent = nullptr);

    /**
     * @brief 返回ScreenSpaceCameraController的成员变量 _enableInputs
     *
     * @return bool true: _enableInputs为true, false: _enableInputs为false
     */
    virtual bool enableInputs() const;

    /**
     * @brief 开启或禁用相机的所有鼠标操作
     *
     * @param enable true: 开启, false: 禁用
     */
    virtual void setEnableInputs(bool enable);

    /**
     * @brief 返回ScreenSpaceCameraController的成员变量 _enableZoom
     *
     * @return bool true: _enableZoom为true, false: _enableZoom为false
     */
    virtual bool enableZoom() const;

    /**
     * @brief 开启或禁用相机的缩放操作
     *
     * @param enable true: 开启, false: 禁用
     */
    virtual void setEnableZoom(bool enable);

    /**
     * @brief 返回ScreenSpaceCameraController的成员变量 _enableRotate
     *
     * @return bool true: _enableRotate为true, false: _enableRotate为false
     */
    virtual bool enableRotate() const;

    /**
     * @brief 开启或禁用相机的旋转操作
     *
     * @param enable true: 开启, false: 禁用
     */
    virtual void setEnableRotate(bool enable);

    /**
     * @brief 返回ScreenSpaceCameraController的成员变量 _enableTilt
     *
     * @return bool true: _enableTilt为true, false: _enableTilt为false
     */
    virtual bool enableTilt() const;

    /**
     * @brief 开启或禁用相机的倾斜操作
     *
     * @param enable true: 开启, false: 禁用
     */
    virtual void setEnableTilt(bool enable);

    /**
     * @brief 返回ScreenSpaceCameraController的成员变量 _enableLook
     *
     * @return bool true: _enableLook为true, false: _enableLook为false
     */
    virtual bool enableLook() const;

    /**
     * @brief 开启或禁用相机的环视操作
     *
     * @param enable true: 开启, false: 禁用
     */
    virtual void setEnableLook(bool enable);

    /**
     * @brief 返回ScreenSpaceCameraController的成员变量 _enableUnderGround
     *
     * @return bool true: _enableUnderGround为true, false: _enableUnderGround为false
     */
    virtual bool enableUnderGround() const;

    /**
     * @brief 开启或禁用相机的地下操作
     *
     * @param enable true: 开启, false: 禁用
     */
    virtual void setEnableUnderGround(bool enable);

    /**
     * @brief 返回ScreenSpaceCameraController的成员变量 _enablePan
     *
     * @return bool true: _enablePan为true, false: _enablePan为false
     */
    virtual bool enablePan() const;

    /**
     * @brief 开启或禁用相机的平移操作
     *
     * @param enable true: 开启, false: 禁用
     */
    virtual void setEnablePan(bool enable);

    /**
     * @brief 返回ScreenSpaceCameraController的成员变量 _minimumCollisionTerrainHeight
     *
     * @return double 返回测试与地形碰撞前相机必须达到的最小高度
     */
    virtual double minimumCollisionTerrainHeight() const;

    /**
     * @brief 设置测试与地形碰撞前相机必须达到的最小高度
     *
     * @param minimumCollisionTerrainHeight 测试与地形碰撞前相机必须达到的最小高度
     */
    virtual void setMinimumCollisionTerrainHeight(double minimumCollisionTerrainHeight);

    /**
     * @brief 获取相机更新后的世界坐标
     *
     * @return Vector3 返回Vector3类型
     */
    virtual Vector3 positionWC();

    /**
     * @brief 获取相机更新后的y轴方向
     *
     * @return Vector3 返回Vector3类型
     */
    virtual Vector3 directionWC();

    /**
     * @brief 获取相机更新后的z轴方向
     *
     * @return Vector3 返回Vector3类型
     */
    virtual Vector3 upWC();

    /**
     * @brief 获取相机更新后的x轴方向
     *
     * @return Vector3 返回Vector3类型
     */
    virtual Vector3 rightWC();

    /**
     * @brief 获取相机更新后的Cartographic坐标
     *
     * @return Cartographic 返回Cartographic类型
     */
    virtual Cartographic positionCartographic();

    /**
     * @brief 获取相机的 heading
     *
     * @return double 返回double类型
     */
    virtual double heading();

    /**
     * @brief 获取相机的 pitch
     *
     * @return double 返回double类型
     */
    virtual double pitch();

    /**
     * @brief 获取相机的 roll
     *
     * @return double 返回double类型
     */
    virtual double roll();

    /**
     * @brief 从相机向一个屏幕点(x, y)发射一条射线 (相机拾取)
     *
     * @param x 屏幕坐标的 x
     * @param y 屏幕坐标的 y
     * @return Ray 射线
     */
    Q_INVOKABLE virtual Ray getPickRay(double x, double y);

    /**
     * @brief 改变相机的状态(位置, 偏转角度等)
     *
     * @param destination 目标点
     * @param heading 相机的heading
     * @param pitch 相机的pitch
     * @param roll 相机的roll
     */
    Q_INVOKABLE virtual void setView(const Cartesian3 &destination, double heading, double pitch, double roll);

    /**
     * @brief 相机围绕axis轴旋转
     *
     * @param axis 围绕轴
     * @param angle 旋转角度 (弧度)
     */
    Q_INVOKABLE virtual void rotate(const Vector3 &axis, double angle);

    /**
     * @brief 相机围绕自身中心点向上旋转
     *
     * @param angle 旋转角度 (弧度)
     */
    Q_INVOKABLE virtual void rotateUp(double angle);

    /**
     * @brief 相机围绕自身中心点向下旋转
     *
     * @param angle 旋转角度 (弧度)
     */
    Q_INVOKABLE virtual void rotateDown(double angle);

    /**
     * @brief 相机围绕自身中心点向右旋转
     *
     * @param angle 旋转角度 (弧度)
     */
    Q_INVOKABLE virtual void rotateRight(double angle);

    /**
     * @brief 相机围绕自身中心点向左旋转
     *
     * @param angle 旋转角度 (弧度)
     */
    Q_INVOKABLE virtual void rotateLeft(double angle);

    /**
     * @brief 相机沿着dir方向平移
     *
     * @param dir 平移的方向
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void move(const Vector3 &dir, double amount);

    /**
     * @brief 相机沿着y轴方向平移
     *
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void moveForward(double amount);

    /**
     * @brief 相机沿着y轴反方向平移
     *
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void moveBackward(double amount);

    /**
     * @brief 相机沿着z轴方向平移
     *
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void moveUp(double amount);

    /**
     * @brief 相机沿着z轴反方向平移
     *
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void moveDown(double amount);

    /**
     * @brief 相机沿着x轴方向平移
     *
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void moveRight(double amount);

    /**
     * @brief 相机沿着x轴反方向平移
     *
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void moveLeft(double amount);

    /**
     * @brief 相机的每一个方向(x、y、z)分别围绕axis轴旋转
     *
     * @param axis 围绕轴
     * @param angle 旋转角度 (弧度)
     */
    Q_INVOKABLE virtual void look(const Vector3 &axis, double angle);

    /**
     * @brief 相机围绕x轴旋转
     *
     * @param amount
     */
    Q_INVOKABLE virtual void lookUp(double amount);

    /**
     * @brief 相机围绕x轴反方向旋转
     *
     * @param amount 旋转量 (弧度)
     */
    Q_INVOKABLE virtual void lookDown(double amount);

    /**
     * @brief 相机围绕z轴旋转
     *
     * @param amount 旋转量 (弧度)
     */
    Q_INVOKABLE virtual void lookRight(double amount);

    /**
     * @brief 相机围绕z轴反方向旋转
     *
     * @param amount 旋转量 (弧度)
     */
    Q_INVOKABLE virtual void lookLeft(double amount);

    /**
     * @brief 相机沿着y轴方向平移
     *
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void zoomIn(double amount);

    /**
     * @brief 相机沿着y轴反方向平移
     *
     * @param amount 平移量
     */
    Q_INVOKABLE virtual void zoomOut(double amount);

    /**
     * @brief 相机飞到目标点 (Vector3类型)
     *
     * @param destination 目标点
     * @param duration 飞行时间 (秒)
     * @param heading 飞到目标点后, 更新相机的heading
     * @param pitch 飞到目标点后, 更新相机的pitch
     * @param roll 飞到目标点后, 更新相机的roll
     */
    Q_INVOKABLE virtual void flyTo(const Vector3 &destination, double duration = Math::EPSILON20, double heading = 0, double pitch = -90, double roll = 0);

    /**
     * @brief 相机飞到目标点 (Cartographic类型)
     *
     * @param destination 目标点
     * @param duration 飞行时间 (秒)
     * @param heading 飞到目标点后, 更新相机的heading
     * @param pitch 飞到目标点后, 更新相机的pitch
     * @param roll 飞到目标点后, 更新相机的roll
     */
    Q_INVOKABLE virtual void flyTo(const Cartographic &destination, double duration = Math::EPSILON20, double heading = 0, double pitch = -90, double roll = 0);

    /**
     * @brief 相机飞到目标点 (LiRectangle类型)
     *
     * @param destination 目标点
     * @param duration 飞行时间 (秒)
     * @param heading 飞到目标点后, 更新相机的heading
     * @param pitch 飞到目标点后, 更新相机的pitch
     * @param roll 飞到目标点后, 更新相机的roll
     */
    Q_INVOKABLE virtual void flyTo(const LiRectangle &destination, double duration = Math::EPSILON20, double heading = 0, double pitch = -90, double roll = 0);

    /**
     * @brief 拾取, 同样适用于地下模式的拾取
     *
     * @param mousePosition 屏幕坐标点
     * @return Cartesian3 世界坐标点
     */
    Q_INVOKABLE virtual Cartesian3 pickGlobe(const Vector2 &mousePosition) const;
};

#endif // LICAMERACONTROLLER_H
