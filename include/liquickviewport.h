#ifndef LIQUICKVIEWPORT_H
#define LIQUICKVIEWPORT_H

#include "licore_global.h"
#include <QQuickPaintedItem>

class LiWidget;
class LiRenderSystem;
class LiQuickViewportPrivate;

class LICORE_EXPORT LiQuickViewport : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit LiQuickViewport(QQuickItem *parent = nullptr);
    virtual ~LiQuickViewport();

    void paint(QPainter *);

private:
    QScopedPointer<LiQuickViewportPrivate> d_ptr;
    friend class LiWidget;
    friend class LiRenderSystem;
};

#endif // LIQUICKVIEWPORT_H
