#ifndef LIWIDGET_H
#define LIWIDGET_H

#include "licore_global.h"
#include <QWidget>
#include <QQuickWidget>
#include <QMouseEvent>
#include <QJSEngine>
#include <QJSValue>

class LiEngine;
class LiScene;
class LiEntity;
class LiRenderSystem;
class LiWidgetPrivate;

class LICORE_EXPORT LiWidget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x READ x)
    Q_PROPERTY(int y READ y)
    Q_PROPERTY(int width READ width)
    Q_PROPERTY(int height READ height)
    Q_PROPERTY(int clientWidth READ width)
    Q_PROPERTY(int clientHeight READ height)
    Q_PROPERTY(bool disableRootEvents READ disableRootEvents)
public:
    explicit LiWidget(QObject *parent = 0);
    ~LiWidget();

    int x() const;
    int y() const;
    int width() const;
    int height() const;

    void show();

    QWidget *widget() const;
    QWindow *window() const;
    QQmlEngine *qmlEngine() const;
    bool disableRootEvents() const;

    // mousedown, mouseup, mousemove, mousewheel, dblclick
    Q_INVOKABLE void addEventListener(const QString &type, const QJSValue &listener, bool useCapture = false);
    Q_INVOKABLE void removeEventListener(const QString &type, const QJSValue &listener, bool useCapture = false);

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void mousePress(QMouseEvent *);
    void mouseRelease(QMouseEvent *);
    void mouseDoubleClick(QMouseEvent *);
    void mouseMove(QMouseEvent *);
    void mouseWheel(QWheelEvent *);
    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);

private:
    Q_DECLARE_PRIVATE(LiWidget)
    friend class LiRenderSystem;
};

#endif // LIWIDGET_H
