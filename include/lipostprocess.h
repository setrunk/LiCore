#ifndef LIPOSTPROCESS_H
#define LIPOSTPROCESS_H

#include "ligeometryrenderer.h"
#include <QQmlListProperty>

class LiPostProcessPrivate;
class LiFullscreenQuad;

class LICORE_EXPORT LiPostProcess : public LiGeometryRenderer
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<LiFullscreenQuad> commands READ qmlCommands)
public:
    explicit LiPostProcess(LiNode *parent = nullptr);

    void addCommand(LiFullscreenQuad *command);
    void removeCommand(LiFullscreenQuad *command);
    QVector<LiFullscreenQuad*> commands() const;

    QQmlListProperty<LiFullscreenQuad> qmlCommands();

private:
    Q_DECLARE_PRIVATE(LiPostProcess)
};

#endif // LIPOSTPROCESS_H
