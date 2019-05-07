#ifndef LICONTEXT_H
#define LICONTEXT_H

#include "linode.h"

class LiEnginePrivate;
class LiAbstractSystem;
class LiTimeSystem;
class LiInputSystem;
class LiRenderSystem;
class LiLogicSystem;
class LiScene;
class LiEntity;

/**
 * @brief
 * LiEngine是ECS架构的核心类，其作用为管理system的注册、注销、运行，是整个系统的大脑，系统的运行调度都发生在LiEngine中。
 * 一般开发用户不需访问LiEngine，除非需要设计自己的system。
 * 这时可以从LiAbstractSystem继承一个新的system并实现自己的功能，然后调用registerSystem函数注册到LiEngine中。
 */
class LICORE_EXPORT LiEngine : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *构造函数
     * @param parent
     */
    explicit LiEngine(QObject *parent = 0);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiEngine();

    /**
     * @brief
     * 获取timeSystem对象
     * @return LiTimeSystem
     */
    LiTimeSystem *timeSystem() const;

    /**
     * @brief
     * 获取renderSystem对象
     * @return LiRenderSystem
     */
    LiRenderSystem *renderSystem() const;

    /**
     * @brief
     * 获取logicSystem对象
     * @return LiLogicSystem
     */
    LiLogicSystem *logicSystem() const;

    /**
     * @brief
     * 获取inputSystem对象
     * @return LiInputSystem
     */
    LiInputSystem *inputSystem() const;

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

    /**
     * @brief
     * 注册一个新的system，如果system没有父物体，该engine就会变成system的父物体
     * @param system
     */
    void registerSystem(LiAbstractSystem *system);

    /**
     * @brief
     * 注销system，system被注销后并不会被删除释放，需要手动删除释放
     * @param system
     */
    void unregisterSystem(LiAbstractSystem *system);

    /**
     * @brief
     * 内部函数，启动运行engine
     */
    void startup();

    /**
     * @brief
     * 查询engine是否已经启动运行
     * @return bool
     */
    bool isStartup() const;

    /**
     * @brief
     * 内部函数，关闭engine
     */
    void shutdown();

public slots:
    /**
     * @brief
     * 帧运行函数，没调用一次就会渲染一帧。
     * 该函数会自动运行，不要手动调用。
     */
    void run();

private:
    Q_DECLARE_PRIVATE(LiEngine)
};

#endif // LICONTEXT_H
