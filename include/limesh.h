#ifndef LIMESH_H
#define LIMESH_H

#include "ligeometryrenderer.h"

class LiMeshPrivate;

/**
 * @brief
 * LiMesh是多个LiGeometryRenderer的合集，提供物体多维材质的功能。
 */
class LICORE_EXPORT LiMesh : public LiGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<LiGeometryRenderer> renderers READ qmlRenderers)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiMesh(LiNode *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiMesh();

    /**
     * @brief
     * 添加子几何渲染器
     * @param renderer
     */
    void addRenderer(LiGeometryRenderer *renderer);

    /**
     * @brief
     * 移除子几何渲染器
     * @param renderer
     */
    void removeRenderer(LiGeometryRenderer *renderer);

    /**
     * @brief
     * 返回所有的子几何渲染器合集
     * @return QVector<LiGeometryRenderer *>
     */
    QVector<LiGeometryRenderer *> renderers() const;

    /**
     * @brief
     * 内部函数，外部不要调用
     * @return QQmlListProperty<LiGeometryRenderer>
     */
    QQmlListProperty<LiGeometryRenderer> qmlRenderers();

    /**
     * @brief
     * 返回物体的包围体（世界坐标系）
     * @return BoundingVolume
     */
    virtual BoundingVolume boundingVolume() const;

    /**
     * @brief
     * 射线与该物体进行测试，如果两者有相交，则返回true并填充相交信息
     * @param ray
     * 用于测试的射线
     * @param hit
     * 如果有相交，该对象保存相交信息
     * @return bool true有相交， false无相交
     */
    virtual bool raycast(const Ray &ray, LiRaycastHit *hit) const;

    LiGeometryRenderer *clone() const override;

private:
    Q_DECLARE_PRIVATE(LiMesh)
};

#endif // LIMESH_H
