#ifndef LIGEOMETRYRENDERER_H
#define LIGEOMETRYRENDERER_H

#include "licomponent.h"
#include "boundingvolume.h"
#include "ray.h"

class LiGeometry;
class LiInstanceAttributes;
class LiMaterial;
class LiBuffer;
class LiMesh;
class LiRaycastHit;
class LiRenderSystem;
class LiGeometryRendererPrivate;
class LiBatchTable;
class LiFeature;

/**
 * @brief
 * LiGeometryRenderer是对几何体（LiGeometry）进行渲染的信息合集，包括用什么材质，
 * 渲染几何体的哪一部分顶点数据，图元方式（点、线、面），渲染顺序等。
 */
class LICORE_EXPORT LiGeometryRenderer : public LiComponent
{
    Q_OBJECT
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(PrimitiveType primitiveType READ primitiveType WRITE setPrimitiveType NOTIFY primitiveTypeChanged)
    Q_PROPERTY(LiGeometry * geometry READ geometry WRITE setGeometry NOTIFY geometryChanged)
    Q_PROPERTY(LiMaterial * material READ material WRITE setMaterial NOTIFY materialChanged)
    Q_PROPERTY(int instanceCount READ instanceCount WRITE setInstanceCount NOTIFY instanceCountChanged)
    Q_PROPERTY(int primitiveCount READ primitiveCount WRITE setPrimitiveCount NOTIFY primitiveCountChanged)
    Q_PROPERTY(int indexOffset READ indexOffset WRITE setIndexOffset NOTIFY indexOffsetChanged)
    Q_PROPERTY(int firstInstance READ firstInstance WRITE setFirstInstance NOTIFY firstInstanceChanged)
    Q_PROPERTY(int firstVertex READ firstVertex WRITE setFirstVertex NOTIFY firstVertexChanged)
    Q_PROPERTY(BoundingVolume boundingVolume READ boundingVolume NOTIFY boundingVolumeChanged)
    Q_PROPERTY(bool castShadow READ castShadow WRITE setCastShadow NOTIFY castShadowChanged)
    Q_PROPERTY(bool receiveShadow READ receiveShadow WRITE setReceiveShadow NOTIFY receiveShadowChanged)
public:
    /**
     * @brief
     * 渲染顺序类型，一帧的渲染是按照以下类型的顺序进行渲染
     */
    enum Type
    {
        PreProcess,         // 正式渲染前，进行一些前期计算，如影像图的校正
        Environment,        // 渲染环境，如星空背景（Skybox）、太阳、大气层等
        Globe,              // 渲染地球
        Opaque,             // 渲染场景中不透明的物体
        Translucent,        // 渲染场景中透明的物体
        GeometryProjection, // 渲染几何投影
        Symbol,             // 渲染标签类物体，如地标、线等
        TextureProjection,  // 渲染纹理投影
        PostProcess,        // 场景渲染完成后，进行特效渲染，后期调色等
        GUI                 // 2D界面渲染
    };
    Q_ENUM(Type)

    /**
     * @brief
     * 图元类型
     */
    enum PrimitiveType
    {
        PointList       = 0x0000, // 每一个顶点数据渲染成一个点
        LineList        = 0x0001, // 每2个顶点数据渲染成一条线
        LineLoop        = 0x0002, // 每2个顶点数据渲染成一条线，最后一个顶点和第一个顶点渲染成一条线
        LineStrip       = 0x0003, // 按0-1, 1-2, 2-3 ...的方式渲染成线
        TriangleList    = 0x0004, // 每3个顶点数据渲染成一个三角面
        TriangleStrip   = 0x0005, // 按0-1-2, 1-3-2, 2-3-4, 3-5-4 ...的方式渲染三角面
        TriangleFan     = 0x0006, // 按0-1-2, 0-2-3, 0-3-4 ...的方式渲染三角面
    };
    Q_ENUM(PrimitiveType)

    /**
     * @brief
     * 摄像机视锥裁切时采用的计算方式
     */
    enum CullMode
    {
        NoCull,                 // 不要进行裁切，一直渲染
        CullByBoundingSphere,   // 根据包围球进行裁切
        CullByBoundingBox       // 根据包围盒进行裁切
    };
    Q_ENUM(CullMode)

    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiGeometryRenderer(LiNode *parent = 0);

    /**
     * @brief
     * 构造函数
     * @param geometry
     * 渲染用的几何体对象
     * @param primitiveCount
     * 进行渲染的顶点数量或者索引数量
     * @param indexOffset
     * 顶点或者索引偏移值
     * @param firstVertex
     * 从第几个顶点开始渲染
     * @param firstInstance
     * 从第几个Instance开始渲染
     * @param type
     * 图元类型
     * @param parent
     */
    LiGeometryRenderer(LiGeometry *geometry,
                       int primitiveCount,
                       int indexOffset = 0,
                       int firstVertex = 0,
                       int firstInstance = 0,
                       PrimitiveType type = TriangleList,
                       LiNode *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiGeometryRenderer();

    /**
     * @brief
     * 返回物体渲染的顺序类型
     * @return Type
     */
    Type type() const;

    /**
     * @brief
     * 返回渲染用的几何体对象
     * @return LiGeometry
     */
    LiGeometry *geometry() const;

    /**
     * @brief
     * 返回渲染用的材质对象
     * @return LiMaterial
     */
    LiMaterial *material() const;

    /**
     * @brief
     * 返回渲染的图元类型
     * @return PrimitiveType
     */
    PrimitiveType primitiveType() const;

    /**
     * @brief
     * 返回渲染的顶点或索引数量
     * @return int
     */
    int primitiveCount() const;

    /**
     * @brief
     * 返回渲染的顶点或索引偏移值
     * @return int
     */
    int indexOffset() const;

    /**
     * @brief
     * 返回渲染的顶点开始值
     * @return int
     */
    int firstVertex() const;

    /**
     * @brief
     * 返回渲染的Instance数量
     * @return int
     */
    int instanceCount() const;

    /**
     * @brief
     * 返回渲染的Instance开始值
     * @return int
     */
    int firstInstance() const;

    /**
     * @brief
     * 返回该物体是否投射阴影
     * @return bool
     */
    bool castShadow() const;

    /**
     * @brief
     * 设置该物体是否投射阴影
     * @param cast
     */
    void setCastShadow(bool cast);

    /**
     * @brief
     * 返回该物体是否接受阴影
     * @return bool
     */
    bool receiveShadow() const;

    /**
     * @brief
     * 设置该物体是否接受阴影
     * @param receive
     */
    void setReceiveShadow(bool receive);

    QVector<float> morphWeights() const;
    void setMorphWeights(const QVector<float> &morphWeights);

    /**
     * @brief
     * 返回渲染用的Instance属性对象
     * @return LiInstanceAttributes
     */
    LiInstanceAttributes *instanceAttributes() const;

    /**
     * @brief
     * 设置渲染用的Instance属性对象
     * @param attributes
     */
    void setInstanceAttributes(LiInstanceAttributes *attributes);

    /**
     * @brief
     * 返回渲染用的属性表
     * @return LiBatchTable
     */
    LiBatchTable *batchTable() const;

    /**
     * @brief
     * 设置渲染用的属性表
     * @param batchTable
     */
    void setBatchTable(LiBatchTable *batchTable);

    LiFeature *feature() const;
    void setFeature(LiFeature *feature);

    QVector<Matrix4> bones() const;
    void setBones(const QVector<Matrix4> &bones);

    /**
     * @brief
     * 返回该物体的裁切方式
     * @return CullMode
     */
    CullMode cullMode() const;

    /**
     * @brief
     * 设置该物体的裁切方式
     * @param mode
     */
    virtual void setCullMode(CullMode mode);

    /**
     * @brief
     * 返回该物体的渲染优先级
     * @return int 按优先级大小进行渲染
     */
    int priority() const;

    /**
     * @brief
     * 设置该物体的渲染优先级
     * @param priority
     */
    void setPriority(int priority);

    /**
     * @brief
     * 返回物体的相对轴对称包围盒（相对父物体坐标系）
     * @return AxisAlignedBoundingBox
     */
    AxisAlignedBoundingBox localBoundingBox() const;

    /**
     * @brief
     * 设置物体的相对轴对称包围盒（相对父物体坐标系）
     * @param box
     */
    void setLocalBoundingBox(const AxisAlignedBoundingBox &box);

    /**
     * @brief
     * 返回物体的相对包围球（相对父物体坐标系）
     * @return BoundingSphere
     */
    BoundingSphere localBoundingSphere() const;

    /**
     * @brief
     * 设置物体的相对包围球（相对父物体坐标系）
     * @param sphere
     */
    void setLocalBoundingSphere(const BoundingSphere &sphere);

    /**
     * @brief
     * 返回物体的包围体（世界坐标系）
     * @return BoundingVolume
     */
    virtual BoundingVolume boundingVolume() const;

    /**
     * @brief
     * 设置物体的包围体（世界坐标系）
     * @param boundingVolume
     */
    void setBoundingVolume(const BoundingVolume &boundingVolume);

    /**
     * @brief
     * 当几何顶点数据发生改变时，调用该函数重新计算包围盒
     */
    void computeBoundingVolume();

    /**
     * @brief
     * 返回是否显示物体的包围盒
     * @return bool
     */
    bool debugBoundingVolume() const;

    /**
     * @brief
     * 设置是否显示物体的包围盒
     * @param debug
     */
    void setDebugBoundingVolume(bool debug);

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

    virtual LiGeometryRenderer *clone() const;

public slots:
    /**
     * @brief
     * 设置渲染顺序类型
     * @param type
     */
    void setType(Type type);

    /**
     * @brief
     * 设置渲染用的几何体
     * @param geometry
     */
    void setGeometry(LiGeometry *geometry);

    /**
     * @brief
     * 设置渲染用的材质
     * @param material
     */
    void setMaterial(LiMaterial *material);

    /**
     * @brief
     * 设置渲染图元类型
     * @param primitiveType
     */
    void setPrimitiveType(PrimitiveType primitiveType);

    /**
     * @brief
     *
     * @param primitiveCount
     */
    void setPrimitiveCount(int primitiveCount);

    /**
     * @brief
     * 设置渲染的顶点或索引偏移值
     * @param indexOffset
     */
    void setIndexOffset(int indexOffset);

    /**
     * @brief
     * 设置渲染的开始顶点或索引值
     * @param firstVertex
     */
    void setFirstVertex(int firstVertex);

    /**
     * @brief
     * 设置渲染的开始Instance数量
     * @param instanceCount
     */
    void setInstanceCount(int instanceCount);

    /**
     * @brief
     * 设置渲染的开始Instance值
     * @param firstInstance
     */
    void setFirstInstance(int firstInstance);

signals:
    void typeChanged();
    void geometryChanged();
    void materialChanged();
    void primitiveTypeChanged();
    void primitiveCountChanged();
    void indexOffsetChanged();
    void firstVertexChanged();
    void instanceCountChanged();
    void firstInstanceChanged();
    void localBoundingBoxChanged();
    void localBoundingSphereChanged();
    void boundingVolumeChanged();
    void castShadowChanged();
    void receiveShadowChanged();

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    LiGeometryRenderer(LiGeometryRendererPrivate &dd, LiNode *parent = 0);

private:
    Q_DECLARE_PRIVATE(LiGeometryRenderer)
    friend class LiRenderSystem;
};

#endif // LIGEOMETRYRENDERER_H
