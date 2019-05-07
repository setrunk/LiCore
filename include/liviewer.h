#ifndef LIVIEWER_H
#define LIVIEWER_H

#include "licore_global.h"
#include <QJSValue>

class LiEngine;
class LiScene;
class LiWidget;
class LiFeatureSystem;
class LiViewerPrivate;

/**
 * @brief
 * LiViewer是系统的入口模块，通过创建LiViewer对象来创建整个系统内部模块，
 * 当该对象被创建后，LiEngine, LiWidget, LiScene等对象可通过相应的API获取。
 */
class LICORE_EXPORT LiViewer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LiScene* scene READ scene)
    Q_PROPERTY(LiWidget* canvas READ widget)
public:
    /**
     * @brief
     * 构造函数
     * @param parent
     */
    explicit LiViewer(QObject *parent = nullptr);

    /**
     * @brief
     * 析构函数
     */
    ~LiViewer();

    /**
     * @brief
     * 获取LiWidget模块对象，该对象是系统内部自动创建的OpenGL渲染视窗
     * @return LiWidget
     */
    LiWidget *widget() const;

    /**
     * @brief
     * 获取LiEngine模块对象
     * @return LiEngine
     */
    LiEngine *engine() const;

    /**
     * @brief
     * 获取LiScene模块对象
     * @return LiScene
     */
    LiScene *scene() const;

    /**
     * @brief
     * FeatureSystem
     * @return LiFeatureSystem
     */
    LiFeatureSystem *featureSystem() const;

    /**
     * @brief
     * 启动系统并显示视窗，当LiViewer对象被创建后，必须调用该函数来启动系统
     */
    void show();

    /**
     * @brief
     * 查询系统是否即将退出
     * @return bool
     */
    bool aboutToQuit() const;

public slots:
    /**
     * @brief
     * 在JS/QML中添加事件回调函数，该函数是模拟JavaScript的addEventListener函数，包括调用参数也是一样的
     * @param type
     * 事件类型，有效的类型有：update, mousedown, mouseup, mousemove
     * @param listener
     * JavaScript的function
     * @param useCapture
     * 暂时无用
     */
    void addEventListener(const QString &type, const QJSValue &listener, bool useCapture = false);

    /**
     * @brief
     * 在JS/QML中删除事件回调函数
     * @param type
     * 事件类型，有效的类型有：update, mousedown, mouseup, mousemove
     * @param listener
     * JavaScript的function
     * @param useCapture
     * 暂时无用
     */
    void removeEventListener(const QString &type, const QJSValue &listener, bool useCapture = false);

private slots:
    /**
     * @brief
     * 内部函数，退出系统
     */
    void shutdown();

private:
    QSharedPointer<LiViewerPrivate> d;
};

/**
 * @brief
 * 获取LiViewer对象的全局函数，可在任何地方调用
 * @return LiViewer
 */
LICORE_EXPORT LiViewer* GlobalViewer();

#endif // LIVIEWER_H
