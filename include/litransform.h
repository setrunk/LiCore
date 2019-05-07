#ifndef LITRANSFORM_H
#define LITRANSFORM_H

#include "licomponent.h"
#include "vector3.h"
#include "quaternion.h"
#include "matrix4.h"
#include "cartographic.h"

class LiTransformPrivate;

/**
 * @brief
 * LiTransform组件提供物体在三维空间中定位、旋转、缩放功能。
 */
class LICORE_EXPORT LiTransform : public LiComponent
{
    Q_OBJECT
    Q_PROPERTY(Cartographic cartographic READ cartographic WRITE setCartographic NOTIFY cartographicChanged)
    Q_PROPERTY(Matrix4 matrix READ matrix WRITE setMatrix NOTIFY matrixChanged) // local space
    Q_PROPERTY(Vector3 position READ position WRITE setPosition NOTIFY positionChanged) // local space
    Q_PROPERTY(Vector3 translation READ translation WRITE setTranslation NOTIFY translationChanged) // local space
    Q_PROPERTY(Quaternion rotation READ rotation WRITE setRotation NOTIFY rotationChanged) // local space
    Q_PROPERTY(Vector3 eulerAngles READ eulerAngles WRITE setEulerAngles NOTIFY eulerAnglesChanged) // local space
    Q_PROPERTY(double rotationX READ rotationX WRITE setRotationX NOTIFY rotationXChanged) // local space
    Q_PROPERTY(double rotationY READ rotationY WRITE setRotationY NOTIFY rotationYChanged) // local space
    Q_PROPERTY(double rotationZ READ rotationZ WRITE setRotationZ NOTIFY rotationZChanged) // local space
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged) // local space
    Q_PROPERTY(Vector3 scale3D READ scale3D WRITE setScale3D NOTIFY scale3DChanged) // local space
    Q_PROPERTY(Vector3 forward READ yaxis) // world space
    Q_PROPERTY(Vector3 up READ zaxis) // world space
    Q_PROPERTY(Vector3 right READ xaxis) // world space
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiTransform(LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiTransform();

    /**
     * @brief
     * 获取物体当前的Cartographic坐标
     * @return Cartographic
     */
    Cartographic cartographic() const;

    /**
     * @brief
     * 获取物体当前的相对坐标(相对于父物体)
     * @return Vector3
     */
    Vector3 position() const;

    /**
     * @brief
     * 获取物体当前的世界坐标
     * @return Vector3
     */
    Vector3 worldPosition() const;

    /**
     * @brief
     * 获取物体当前的相对坐标(相对于父物体)，等同于position()函数
     * @return Vector3
     */
    Vector3 translation() const;

    /**
     * @brief
     * 获取物体当前的相对方位四元组（相对于父物体）
     * @return Quaternion
     */
    Quaternion rotation() const;

    /**
     * @brief
     * 获取物体当前的相对方位欧拉角（相对于父物体）
     * @return Vector3
     */
    Vector3 eulerAngles() const;

    /**
     * @brief
     * 获取物体当前的X方向的欧拉角（相对于父物体）
     * @return double
     */
    double rotationX() const;

    /**
     * @brief
     * 获取物体当前的Y方向的欧拉角（相对于父物体）
     * @return double
     */
    double rotationY() const;

    /**
     * @brief
     * 获取物体当前的Z方向的欧拉角（相对于父物体）
     * @return double
     */
    double rotationZ() const;

    /**
     * @brief
     * 获取物体当前的相对整体缩放值（相对于父物体），等同于scale3D().x()
     * @return double
     */
    double scale() const;

    /**
     * @brief
     * 获取物体当前的相对缩放值（相对于父物体）
     * @return Vector3
     */
    Vector3 scale3D() const;

    /**
     * @brief
     * 获取物体当前的相对变换矩阵（相对于父物体）
     * @return Matrix4
     */
    Matrix4 matrix() const;

    /**
     * @brief
     * 获取物体当前的X方向矢量（世界坐标）
     * @return Vector3
     */
    Q_INVOKABLE Vector3 xaxis() const;

    /**
     * @brief
     * 获取物体当前的Y方向矢量（世界坐标）
     * @return Vector3
     */
    Q_INVOKABLE Vector3 yaxis() const;

    /**
     * @brief
     * 获取物体当前的Z方向矢量（世界坐标）
     * @return Vector3
     */
    Q_INVOKABLE Vector3 zaxis() const;

    /**
     * @brief
     * 令物体的Y轴指向center点
     * @param center
     */
    Q_INVOKABLE void lookAt(const Vector3 &center);

    /**
     * @brief
     * 获取物体的世界变换矩阵
     * @return Matrix4
     */
    Q_INVOKABLE Matrix4 worldMatrix() const;

    /**
     * @brief
     * 获取由本地坐标系到世界坐标系的变换矩阵，等同于worldMatrix()函数
     * @return Matrix4
     */
    Q_INVOKABLE Matrix4 localToWorldMatrix() const;

    /**
     * @brief
     * 获取由世界坐标系到本地坐标系的变换矩阵，等同于worldMatrix().inverted()函数
     * @return Matrix4
     */
    Q_INVOKABLE Matrix4 worldToLocalMatrix() const;

    /**
     * @brief
     * 计算绕axis轴转动angle角度的四元组
     * @param axis
     * 指定旋转的轴，长度为1的矢量
     * @param angle
     * 转动的角度，单位为度(degree)
     * @return Quaternion
     */
    Q_INVOKABLE static Quaternion fromAxisAndAngle(const Vector3 &axis, double angle);

    /**
     * @brief
     * 等同于fromAxisAndAngle(Vector3(x,y,z), angle)
     * @param x
     * @param y
     * @param z
     * @param angle
     * @return Quaternion
     */
    Q_INVOKABLE static Quaternion fromAxisAndAngle(double x, double y, double z, double angle);

    /**
     * @brief
     * 通过欧拉角计算四元组
     * @param eulerAngles
     * XYZ方向的欧拉角，单位为度(degree)
     * @return Quaternion
     */
    Q_INVOKABLE static Quaternion fromEulerAngles(const Vector3 &eulerAngles);

    /**
     * @brief
     * 等同于fromEulerAngles(Vector3(pitch, yaw, roll))
     * @param pitch
     * 围绕X轴旋转角度，也叫俯仰角
     * @param yaw
     * 围绕Z轴旋转角度，也叫偏航角
     * @param roll
     * 围绕Y轴旋转角度，也叫翻滚角
     * @return Quaternion
     */
    Q_INVOKABLE static Quaternion fromEulerAngles(double pitch, double yaw, double roll);

    /**
     * @brief
     * 计算围绕point为支点，绕axia轴旋转angle角度的变换矩阵
     * @param point
     * 旋转支点，为三维空间的点
     * @param axis
     * 旋转轴，长度为1的矢量
     * @param angle
     * 旋转角度，单位为度(degree)
     * @return Matrix4
     */
    Q_INVOKABLE static Matrix4 rotateAround(const Vector3 &point, const Vector3 &axis, double angle);

public Q_SLOTS:
    /**
     * @brief
     * 设置物体的Cartographic坐标，完成后物体的X轴指向东方，Y轴指向北方，Z轴为地面法线
     * @param cartographic
     */
    void setCartographic(const Cartographic &cartographic);

    /**
     * @brief
     * 设置物体的整体缩放值（相对于父物体）
     * @param scale
     */
    void setScale(double scale);

    /**
     * @brief
     * 设置物体的缩放值（相对于父物体）
     * @param scale
     */
    void setScale3D(const Vector3 &scale);

    /**
     * @brief
     * 设置物体的旋转角度（相对于父物体）
     * @param rotation
     */
    void setRotation(const Quaternion &rotation);

    /**
     * @brief
     * 设置物体的旋转欧拉角（相对于父物体）
     * @param eulerAngles
     */
    void setEulerAngles(const Vector3 &eulerAngles);

    /**
     * @brief
     * 设置物体的XYZ方向矢量值（世界坐标）
     * @param xAxis
     * X方向矢量，世界坐标系
     * @param yAxis
     * Y方向矢量，世界坐标系
     * @param zAxis
     * Z方向矢量，世界坐标系
     */
    void setAxes(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);

    /**
     * @brief
     * 设置物体的相对位置（相对于父物体）
     * @param position
     */
    void setPosition(const Vector3 &position);

    /**
     * @brief
     * 等同于setPosition函数
     * @param translation
     */
    void setTranslation(const Vector3 &translation);

    /**
     * @brief
     * 设置物体的世界坐标系位置
     * @param position
     */
    void setWorldPosition(const Vector3 &position);

    /**
     * @brief
     * 设置物体相对变换矩阵（相对于父物体）
     * @param matrix
     */
    void setMatrix(const Matrix4 &matrix);

    /**
     * @brief
     * 设置物体世界变换矩阵
     * @param matrix
     */
    void setWorldMatrix(const Matrix4 &matrix);

    /**
     * @brief
     * 设置物体绕X轴的转动角，单位为度(degree)
     * @param rotationX
     */
    void setRotationX(double rotationX);

    /**
     * @brief
     * 设置物体绕Y轴的转动角，单位为度(degree)
     * @param rotationY
     */
    void setRotationY(double rotationY);

    /**
     * @brief
     * 设置物体绕Z轴的转动角，单位为度(degree)
     * @param rotationZ
     */
    void setRotationZ(double rotationZ);

    /**
     * @brief
     * 设置物体位置，旋转角度，缩放值
     * @param translation
     * @param rotation
     * @param scale
     */
    void setTransform(const Vector3 &translation, const Quaternion &rotation, const Vector3 &scale);

Q_SIGNALS:
    /**
     * @brief
     * 当物体Cartographic坐标改变时，发出该信号
     * @param cartographic
     */
    void cartographicChanged(const Cartographic &cartographic);

    /**
     * @brief
     * 当物体整体缩放值发生改变时，发出该信号
     * @param scale
     */
    void scaleChanged(double scale);

    /**
     * @brief
     * 当物体缩放值发生改变时，发出该信号
     * @param scale
     */
    void scale3DChanged(const Vector3 &scale);

    /**
     * @brief
     * 当物体旋转角度发生改变时，发出该信号
     * @param rotation
     */
    void rotationChanged(const Quaternion &rotation);

    /**
     * @brief
     * 当物体旋转欧拉角发生改变时，发出该信号
     * @param eulerAngles
     */
    void eulerAnglesChanged(const Vector3 &eulerAngles);

    /**
     * @brief
     * 当物体位置发生改变时，发出该信号
     * @param position
     */
    void positionChanged(const Vector3 &position);

    /**
     * @brief
     * 当物体位置发生改变时，发出该信号
     * @param translation
     */
    void translationChanged(const Vector3 &translation);

    /**
     * @brief
     * 当物体X轴角度发生改变时，发出该信号
     * @param rotationX
     */
    void rotationXChanged(double rotationX);

    /**
     * @brief
     * 当物体Y轴角度发生改变时，发出该信号
     * @param rotationY
     */
    void rotationYChanged(double rotationY);

    /**
     * @brief
     * 当物体Z轴角度发生改变时，发出该信号
     * @param rotationZ
     */
    void rotationZChanged(double rotationZ);

    /**
     * @brief
     * 当物体相对变换矩阵发生改变时，发出该信号
     */
    void matrixChanged();

    /**
     * @brief
     * 当物体世界变换矩阵发生改变时，发出该信号
     */
    void worldMatrixChanged();

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiTransform(LiTransformPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiTransform)
    friend class LiEntity;
};

#endif // LITRANSFORM_H
