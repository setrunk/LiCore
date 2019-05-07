#ifndef LIBEHAVIOR_H
#define LIBEHAVIOR_H

#include "licomponent.h"
#include <QQmlParserStatus>

class LiBehaviorPrivate;
class LiLogicSystem;

/**
 * @brief
 * LiBehavior是ECS架构的核心类，是二次开发的重要入口。开发者可以从该类继承出自定义component，然后添加到
 * LiEntity中，就可以在特定的时间段运行想要的代码。LiBehavior最重要的函数有start(), update()，start函数
 * 在系统启动的时候执行一次，update函数会在每次渲染前执行一次。
 */
class LICORE_EXPORT LiBehavior : public LiComponent, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiBehavior(LiNode *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    virtual ~LiBehavior();

    /**
     * @brief
     * 在系统被唤醒时执行（将来实现）
     */
    virtual void awake();

    /**
     * @brief
     * 在系统初始化时执行，而且只执行一次
     */
    virtual void start();

    /**
     * @brief
     * 在系统开始一帧计算前执行
     */
    virtual void beginFrame();

    /**
     * @brief
     * 在帧渲染前执行
     */
    virtual void update();

    /**
     * @brief
     * 在系统结束一帧后执行
     */
    virtual void endFrame();

    /**
     * @brief
     * 内部函数，外部不要调用
     */
    virtual void classBegin() {}

    /**
     * @brief
     * 内部函数，外部不要调用
     */
    virtual void componentComplete();

    /**
     * @brief
     * 通过一个qml文件创建LiBehavior对象
     * @param url
     * qml文件的url
     * @return LiBehavior
     */
    static LiBehavior *create(const QUrl &url);

protected:
    /**
     * @brief
     * 内部构造函数
     * @param dd
     * @param parent
     */
    explicit LiBehavior(LiBehaviorPrivate &dd, LiNode *parent = nullptr);

private:
    Q_DECLARE_PRIVATE(LiBehavior)
    friend class LiLogicSystem;
};

#endif // LIBEHAVIOR_H
