#ifndef LIABSTRACTSYSTEM_H
#define LIABSTRACTSYSTEM_H

#include "licore_global.h"

class LiAbstractSystemPrivate;
class LiEngine;
class LiScene;
class LiEntity;

/**
 * @brief
 * LiAbstractSystem是ECS架构的基础类，衍生类有LiInputSystem, LiLogicSystem, LiRenderSystem, LiTimeSystem等
 */
class LICORE_EXPORT LiAbstractSystem : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiAbstractSystem(QObject *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiAbstractSystem();

    /**
     * @brief
     * 获取engine对象
     * @return LiEngine
     */
    LiEngine *engine() const;

    /**
     * @brief
     * 获取scene对象
     * @return LiScene
     */
    LiScene *scene() const;

    /**
     * @brief
     * 获取场景图的根entity
     * @return LiEntity
     */
    LiEntity *rootEntity() const;

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiAbstractSystem(LiAbstractSystemPrivate &dd, QObject *parent = nullptr);

private:
    /**
     * @brief
     * 当system被注册到engine时，该函数被调用
     */
    virtual void onRegistered();

    /**
     * @brief
     * 当system从engine中注销时，该函数被调用
     */
    virtual void onUnregistered();

    /**
     * @brief
     * 当engine启动初始化时，该函数被调用
     */
    virtual void onEngineStartup();

    /**
     * @brief
     * 当engine即将退出时，该函数被调用
     */
    virtual void onEngineShutdown();

    /**
     * @brief
     * 当一帧即将开始前调用，调用顺序为beginFrame, update, endFrame
     */
    virtual void beginFrame();

    /**
     * @brief
     * 每帧更新时都会被调用
     */
    virtual void update();

    /**
     * @brief
     * 当一帧被渲染完成后调用，调用顺序为beginFrame, update, endFrame
     */
    virtual void endFrame();

    Q_DECLARE_PRIVATE(LiAbstractSystem)

    friend class LiEngine;
};


#endif // LIABSTRACTSYSTEM_H
