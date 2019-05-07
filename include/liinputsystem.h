#ifndef LIINPUTSYSTEM_H
#define LIINPUTSYSTEM_H

#include "liabstractsystem.h"

class LiInputSystemPrivate;
class LiWidget;

class LICORE_EXPORT LiInputSystem : public LiAbstractSystem
{
    Q_OBJECT
    Q_PROPERTY(bool leftMouseButton READ leftMouseButton)
    Q_PROPERTY(bool rightMouseButton READ rightMouseButton)
    Q_PROPERTY(bool middleMouseButton READ middleMouseButton)
    Q_PROPERTY(bool anyKey READ anyKey)
    Q_PROPERTY(QPoint mousePosition READ mousePosition)
public:
    explicit LiInputSystem(QObject *parent = nullptr);

    bool leftMouseButton() const;
    bool rightMouseButton() const;
    bool middleMouseButton() const;
    bool anyKey() const;
    QPoint mousePosition() const;

    void setSource(LiWidget *widget);

signals:
    void leftButtonDown();
    void leftButtonUp();
    void rightButtonDown();
    void rightButtonUp();
    void middleButtonDown();
    void middleButtonUp();
    void leftButtonDoubleClick();
    void middleButtonWheelUp();
    void middleButtonWheelDown();
    void mouseMoving(int x, int y);
    void mouseWheeling(int deltaX, int deltaY);
    void keyUp(int k); // TODO: k rename to key
    void keyDown(int k); // TODO: k rename to key

public slots:
    bool getMouseButton(int button) const;
    bool getMouseButtonDown(int button) const;
    bool getKey(int key) const;

private slots:
    void mousePress(QMouseEvent *e);
    void mouseRelease(QMouseEvent *e);
    void mouseDoubleClick(QMouseEvent *e);
    void mouseWheel(QWheelEvent *e);
    void mouseMove(QMouseEvent *e);
    void keyPress(QKeyEvent *e);
    void keyRelease(QKeyEvent *e);

private:
    void endFrame();
    Q_DECLARE_PRIVATE(LiInputSystem)
};

#endif // LIINPUTSYSTEM_H
