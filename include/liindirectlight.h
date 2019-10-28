#ifndef LIINDIRECTLIGHT_H
#define LIINDIRECTLIGHT_H

#include "lilight.h"
#include "quaternion.h"

class LiTexture;
class LiIndirectLightPrivate;

class LICORE_EXPORT LiIndirectLight : public LiLight
{
    Q_OBJECT
    Q_PROPERTY(float diffuseIntensity READ diffuseIntensity WRITE setDiffuseIntensity NOTIFY diffuseIntensityChanged)
    Q_PROPERTY(float specularIntensity READ specularIntensity WRITE setSpecularIntensity NOTIFY specularIntensityChanged)
    Q_PROPERTY(float rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
public:
    explicit LiIndirectLight(LiNode *parent = nullptr);

    float diffuseIntensity() const;
    void setDiffuseIntensity(float diffuseIntensity);

    float specularIntensity() const;
    void setSpecularIntensity(float specularIntensity);

    LiTexture *reflectionMap() const;
    LiTexture *irradianceMap() const;

    /** Set rotation [0-360] degrees
     */
    float rotation() const;
    void setRotation(float rotation);

    Q_INVOKABLE bool loadFromFile(const QString &filename);
    Q_INVOKABLE bool loadFromUrl(const QUrl &url);

signals:
    void diffuseIntensityChanged();
    void specularIntensityChanged();
    void rotationChanged();

private:
    Q_DECLARE_PRIVATE(LiIndirectLight)
};

#endif // LIINDIRECTLIGHT_H
