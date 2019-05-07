#ifndef LIVIEWSHED_H
#define LIVIEWSHED_H

#include "ligeometryrenderer.h"

class LiViewshedPrivate;

class LICORE_EXPORT LiViewshed : public LiGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(Vector3 start READ start WRITE setStart NOTIFY startChanged)
    Q_PROPERTY(Vector3 end READ end WRITE setEnd NOTIFY endChanged)
    Q_PROPERTY(double radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(double verticalAngle READ verticalAngle WRITE setVerticalAngle NOTIFY verticalAngleChanged)
    Q_PROPERTY(double horizontalAngle READ horizontalAngle WRITE setHorizontalAngle NOTIFY horizontalAngleChanged)
    Q_PROPERTY(QColor visibleColor READ visibleColor WRITE setVisibleColor NOTIFY visibleColorChanged)
    Q_PROPERTY(QColor invisibleColor READ invisibleColor WRITE setInvisibleColor NOTIFY invisibleColorChanged)
    Q_PROPERTY(bool showDebugFrame READ showDebugFrame WRITE setShowDebugFrame NOTIFY showDebugFrameChanged)
public:
    explicit LiViewshed(LiNode *parent = nullptr);
    ~LiViewshed();

    Vector3 start() const;
    void setStart(const Vector3 &start);

    Vector3 end() const;
    void setEnd(const Vector3 &end);

    double radius() const;
    void setRadius(double radius);

    double verticalAngle() const; // degrees
    void setVerticalAngle(double angle);

    double horizontalAngle() const; // degrees
    void setHorizontalAngle(double angle);

    QColor visibleColor() const;
    void setVisibleColor(const QColor &color);

    QColor invisibleColor() const;
    void setInvisibleColor(const QColor &color);

    bool showDebugFrame() const;
    void setShowDebugFrame(bool show);

signals:
    void startChanged(const Vector3 &start);
    void endChanged(const Vector3 &end);
    void radiusChanged(double radius);
    void verticalAngleChanged(double angle);
    void horizontalAngleChanged(double angle);
    void visibleColorChanged(const QColor &color);
    void invisibleColorChanged(const QColor &color);
    void showDebugFrameChanged(bool show);

private:
    Q_DECLARE_PRIVATE(LiViewshed)
};

#endif // LIVIEWSHED_H
