#ifndef LISCENEIOFACTORY_H
#define LISCENEIOFACTORY_H

#include "licore_global.h"

class LiEntity;
class LiSceneLoader;

class LICORE_EXPORT LiSceneIOFactory : public QObject
{
    Q_OBJECT
public:
    explicit LiSceneIOFactory(QObject *parent = 0);

    Q_INVOKABLE static LiSceneLoader *createSceneLoader(const QUrl &url);
    Q_INVOKABLE static LiSceneLoader *fromFormat(const QString &format);

signals:

public slots:
};

#endif // LISCENEIOFACTORY_H
