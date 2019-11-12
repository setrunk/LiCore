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
    enum Option {
        GenVertexNormals    = (1 << 0),
        ForceTwoSided       = (1 << 1),
        FlipTextureUV       = (1 << 2),
        IgnoreDiffuseColor  = (1 << 3)
    };
    Q_ENUM(Option)

    enum Error {
        NoError,
        TryAgain,
        FileNotFound
    };
    Q_ENUM(Error)

    explicit LiSceneLoader(QObject *parent = 0) : QObject(parent) {}
    virtual ~LiSceneLoader() {}

    Q_INVOKABLE virtual bool isFileTypeSupported(const QUrl &source) const = 0;
    Q_INVOKABLE virtual Future load(const QUrl &source, uint32_t options = 0) = 0;
    Q_INVOKABLE virtual Future fromBinaryData(const QByteArray &data, uint32_t options = 0) = 0;
    Q_INVOKABLE virtual LiEntity *scene(int id = 0) = 0;
    Q_INVOKABLE virtual Error error() const { return NoError; }

signals:
    void finished();
};

#endif // LISCENELOADER_H
