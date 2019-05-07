#ifndef LIENTITY_H
#define LIENTITY_H

#include "linode.h"

class LiEntityPrivate;
class LiComponent;
class LiTransform;
class LiGeometryRenderer;
class LiComputeRenderer;
class LiCamera;
class LiLight;
class LiAnimation;
class LiAudio;
class LiCollider;
class LiRigidbody;

class LiEntity;
typedef QVector<LiEntity*> LiEntityList;
typedef QVector<LiComponent *> LiComponentVector;

/**
 * @brief
 * LiEntity是ECS架构的核心类，是component组件的容器，一个LiEntity拥有什么样的component组件，就拥有什么样的功能。
 * LiEntity默认只有一个LiTransform组件。
 * 场景是由不同的entity组成，而LiEntity是由不同的LiComponent组成。
 * LiEntity有父子层级结构，LiScene场景默认有一个根Entity，任何添加到场景的Entity，都会成为根Entity的子Entity。
 */
class LICORE_EXPORT LiEntity : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(LiTransform* transform READ transform)
    Q_PROPERTY(LiGeometryRenderer* renderer READ renderer WRITE setRenderer NOTIFY rendererChanged)
    Q_PROPERTY(LiCamera* camera READ camera)
    Q_PROPERTY(LiLight* light READ light)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiEntity(LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiEntity();

    /**
     * @brief
     * 查询该entity在场景图中是否有效。
     * 一个entity如果被setEnabled(false)，那么它本身以及所有的子entity都会无效。
     * @return bool
     */
    bool activeInHierarchy() const;

    /**
     * @brief
     * 获取父entity对象
     * @return LiEntity
     */
    LiEntity *parentEntity() const;

    /**
     * @brief
     * 获取所有的子entity合集，该函数有一定的消耗，尽量不要在每帧更新里调用
     * @return LiEntityList
     */
    LiEntityList childEntities() const;

    /**
     * @brief
     * 添加一个新的component组件，如果该component已经存在，则不会被再次添加。
     * 如果component没有父物体，该entity会变成component的父物体。
     * @param component
     */
    Q_INVOKABLE void addComponent(LiComponent *component);

    /**
     * @brief
     * 获取该entity所有的component合集，该函数不会有消耗，可以随时调用
     * @return LiComponentVector
     */
    LiComponentVector components() const;

    /**
     * @brief
     * 返回transform组件
     * @return LiTransform
     */
    LiTransform *transform() const;

    /**
     * @brief
     * 返回renderer组件
     * @return LiGeometryRenderer
     */
    LiGeometryRenderer *renderer() const;

    /**
     * @brief
     * 返回camera组件
     * @return LiCamera
     */
    LiCamera *camera() const;

    /**
     * @brief
     * 返回light组件
     * @return LiLight
     */
    LiLight *light() const;


    // TODO ...
    /**
     * @brief
     * 返回animation组件
     * @return LiAnimation
     */
    LiAnimation *animation() const;

    /**
     * @brief
     * 返回audio组件
     * @return LiAudio
     */
    LiAudio *audio() const;

    /**
     * @brief
     * 返回collider组件
     * @return LiCollider
     */
    LiCollider *collider() const;

    /**
     * @brief
     * 返回rigidbody组件
     * @return LiRigidbody
     */
    LiRigidbody *rigidbody() const;

    template<class T>
    /**
     * @brief
     * 模板函数，不能直接调用
     * @return T
     */
    T *addComponent();

    /**
     * @brief
     * 模板函数，不能直接调用
     * @return T
     */
    template<class T>
    T *component() const;

    /**
     * @brief
     * 返回场景图的根entity
     * @return LiEntity
     */
    Q_INVOKABLE static LiEntity *root();

Q_SIGNALS:
    /**
     * @brief
     * 当renderer组件发生改变时，发出该信号
     * @param renderer
     */
    void rendererChanged(LiGeometryRenderer *renderer);

public slots:
    /**
     * @brief
     * 移除component，component被移除并不会被删除释放，需要手动删除释放
     * @param component
     */
    void removeComponent(LiComponent *component);

    /**
     * @brief
     * 设置新的renderer组件，一个entity只能有一个renderer，新的renderer会替代旧的renderer，
     * 同时旧renderer会从component合集中移除，等同于
     * entity->removeComponent(oldRenderer);
     * entity->addComponent(newRenderer);
     * @param renderer
     */
    void setRenderer(LiGeometryRenderer *renderer);

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiEntity(LiEntityPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiEntity)
};

template<>
LICORE_EXPORT LiCamera *LiEntity::addComponent<LiCamera>();

template<>
LICORE_EXPORT LiLight *LiEntity::addComponent<LiLight>();

template<>
LICORE_EXPORT LiGeometryRenderer *LiEntity::addComponent<LiGeometryRenderer>();

template<>
LICORE_EXPORT LiTransform *LiEntity::component<LiTransform>() const;

template<>
LICORE_EXPORT LiCamera *LiEntity::component<LiCamera>() const;

template<>
LICORE_EXPORT LiLight *LiEntity::component<LiLight>() const;

template<>
LICORE_EXPORT LiGeometryRenderer *LiEntity::component<LiGeometryRenderer>() const;

template<>
LICORE_EXPORT LiComputeRenderer *LiEntity::component<LiComputeRenderer>() const;

#endif // LIENTITY_H
