#ifndef LISCENELOADER_H
#define LISCENELOADER_H

#include "licore_global.h"
#include "future.h"

class LiEntity;

class LICORE_EXPORT LiSceneLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LiEntity* scene READ scene)
public:
    enum Error {
        NoError,
        TryAgain,
        FileNotFound
    };
    Q_ENUM(Error)

    explicit LiSceneLoader(QObject *parent = 0) : QObject(parent) {}
    virtual ~LiSceneLoader() {}

    Q_INVOKABLE virtual bool isFileTypeSupported(const QUrl &source) const = 0;
    Q_INVOKABLE virtual Future load(const QUrl &source, const QVariantMap &options = QVariantMap()) = 0;
    Q_INVOKABLE virtual Future fromBinaryData(const QByteArray &data, const QVariantMap &options = QVariantMap()) = 0;
    Q_INVOKABLE virtual LiEntity *scene(int id = 0) = 0;
    Q_INVOKABLE virtual Error error() const { return NoError; }

signals:
    void finished();
};

#endif // LISCENELOADER_H
