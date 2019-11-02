#ifndef LICLIPVOLUME_H
#define LICLIPVOLUME_H

#include "licomponent.h"
#include "vector3.h"

class LiClipVolumePrivate;

///
// 裁切体，系统最多支持8个裁切体
///
class LICORE_EXPORT LiClipVolume : public LiComponent
{
    Q_OBJECT
    Q_PROPERTY(Shape shape READ shape WRITE setShape NOTIFY shapeChanged)
    Q_PROPERTY(ClipFlag clipFlag READ clipFlag WRITE setClipFlag NOTIFY clipFlagChanged)
    Q_PROPERTY(Vector3 size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(bool showDebugVolume READ showDebugVolume WRITE setShowDebugVolume NOTIFY showDebugVolumeChanged)
public:
    enum Shape
    {
        Cube,
        Sphere,
        Cylinder
    };
    Q_ENUM(Shape)

    enum ClipFlag
    {
        ClipGlobe = 0x01,
        ClipScene = 0x02,
        ClipAll = ClipGlobe | ClipScene
    };
    Q_ENUM(ClipFlag)

    explicit LiClipVolume(LiNode *parent = nullptr);
    ~LiClipVolume();

    // 裁切体的类型，目前只支持Cube类型，其它类型无效
    Shape shape() const;
    void setShape(Shape shape);

    ClipFlag clipFlag() const; // default is ClipAll
    void setClipFlag(ClipFlag clipFlag);

    // 裁切体的长宽高
    Vector3 size() const;
    void setSize(const Vector3 &size);

    // 是否显示裁切体的包围盒
    bool showDebugVolume() const;
    void setShowDebugVolume(bool show);

signals:
    void shapeChanged();
    void clipFlagChanged();
    void sizeChanged();
    void showDebugVolumeChanged();

private:
    Q_DECLARE_PRIVATE(LiClipVolume)
};

#endif // LICLIPVOLUME_H
