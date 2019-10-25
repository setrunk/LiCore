#ifndef LICOMPONENT_H
#define LICOMPONENT_H

#include "linode.h"

class LiEntity;
class LiAnimation;
class LiAudio;
class LiCamera;
class LiCollider;
class LiLight;
class LiGeometryRenderer;
class LiMesh;
class LiRigidbody;
class LiTransform;
class LiSkin;
class LiComponentPrivate;
class LiAnimator;

/**
 * @brief
 * LiComponent是ECS架构的基础类，是其它功能模块组件的基类，实现了一些基本函数，该类本身并不会实体化。
 */
class LICORE_EXPORT LiComponent : public LiNode
{
    Q_OBJECT
    Q_PROPERTY(LiEntity* entity READ entity)
    Q_PROPERTY(LiTransform* transform READ transform)
    Q_PROPERTY(LiGeometryRenderer* renderer READ renderer)
    Q_PROPERTY(LiCamera* camera READ camera)
    Q_PROPERTY(LiLight* light READ light)
    Q_PROPERTY(LiSkin* skin READ skin)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiComponent(LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiComponent();

    /**
     * @brief
     * 获取该Component依附的Entity
     * @return LiEntity
     */
    LiEntity *entity() const;

    /**
     * @brief
     * 获取entity中的transform组件，等同于entity()->transform()函数
     * @return LiTransform
     */
    LiTransform *transform() const;

    /**
     * @brief
     * 获取entity中的renderer组件，等同于entity()->renderer()函数
     * @return LiGeometryRenderer
     */
    LiGeometryRenderer *renderer() const;

    /**
     * @brief
     * 获取entity中的skin组件，等同于entity()->skin()函数
     * @return LiSkin
     */
    LiSkin *skin() const;

    /**
     * @brief
     * 获取entity中的camera组件，等同于entity()->camera()函数
     * @return LiCamera
     */
    LiCamera *camera() const;

    /**
     * @brief
     * 获取entity中的light组件，等同于entity()->light()函数
     * @return LiLight
     */
    LiLight *light() const;

    // TODO ...
    /**
     * @brief
     * 获取entity中的animation组件，等同于entity()->animation()函数
     * @return LiAnimation
     */
    LiAnimation *animation() const;

    LiAnimator *animator() const;

    /**
     * @brief
     * 获取entity中的audio组件，等同于entity()->audio()函数
     * @return LiAudio
     */
    LiAudio *audio() const;

    /**
     * @brief
     * 获取entity中的collider组件，等同于entity()->collider()函数
     * @return LiCollider
     */
    LiCollider *collider() const;

    /**
     * @brief
     * 获取entity中的rigidbody组件，等同于entity()->rigidbody()函数
     * @return LiRigidbody
     */
    LiRigidbody *rigidbody() const;

    /**
     * @brief
     * 在entity中添加component组件，等同于entity()->addComponent(...)函数
     * @param component
     */
    Q_INVOKABLE void addComponent(LiComponent *component);

Q_SIGNALS:
    /**
     * @brief
     * 当该component被加到新的entity中的时候，会发出该信号
     * @param entity
     */
    void addedToEntity(LiEntity *entity);

    /**
     * @brief
     * 当该component被移除的时候，会发出该信号
     * @param entity
     */
    void removedFromEntity(LiEntity *entity);

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiComponent(LiComponentPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiComponent)
};

#endif // LICOMPONENT_H
