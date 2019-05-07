#ifndef WATERPARAMETERS_P_H
#define WATERPARAMETERS_P_H

#include "licore_global.h"

class LiTexture;

class LICORE_EXPORT LiWaterParameters : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float softIntersectionFactor READ softIntersectionFactor WRITE setSoftIntersectionFactor NOTIFY softIntersectionFactorChanged)
    Q_PROPERTY(float reflectionAmount READ reflectionAmount WRITE setReflectionAmount NOTIFY reflectionAmountChanged)
    Q_PROPERTY(float reflectionNoise READ reflectionNoise WRITE setReflectionNoise NOTIFY reflectionNoiseChanged)
    Q_PROPERTY(float whiteCapsAmount READ whiteCapsAmount WRITE setWhiteCapsAmount NOTIFY whiteCapsAmountChanged)
    Q_PROPERTY(float sunMultiplier READ sunMultiplier WRITE setSunMultiplier NOTIFY sunMultiplierChanged)
    Q_PROPERTY(float fresnelScale READ fresnelScale WRITE setFresnelScale NOTIFY fresnelScaleChanged)
    Q_PROPERTY(QColor waterColor READ waterColor WRITE setWaterColor NOTIFY waterColorChanged)
public:
    explicit LiWaterParameters(QObject *parent = nullptr);

    float softIntersectionFactor() const;
    float reflectionAmount() const;
    float reflectionNoise() const;
    float whiteCapsAmount() const;
    float sunMultiplier() const;
    float fresnelScale() const;
    QColor waterColor() const;

    LiTexture *envMapSamplerRefl() const
    {
        return _envMapSamplerRefl;
    }

    LiTexture *oceanBumpMapSampler() const
    {
        return _oceanBumpMapSampler;
    }

    LiTexture *foamSampler() const
    {
        return _foamSampler;
    }

    LiTexture *foamSampler2() const
    {
        return _foamSampler2;
    }

    LiTexture *waterGlossMapSampler() const
    {
        return _waterGlossMapSampler;
    }

    bool ready() const
    {
        return _oceanBumpMapSampler &&
               _foamSampler &&
                _foamSampler2 &&
               _waterGlossMapSampler;
    }

public slots:
    void setSoftIntersectionFactor(float softIntersectionFactor);
    void setReflectionAmount(float reflectionAmount);
    void setReflectionNoise(float reflectionNoise);
    void setWhiteCapsAmount(float whiteCapsAmount);
    void setSunMultiplier(float sunMultiplier);
    void setFresnelScale(float fresnelScale);
    void setWaterColor(const QColor &waterColor);

signals:
    void softIntersectionFactorChanged();
    void reflectionAmountChanged();
    void reflectionNoiseChanged();
    void whiteCapsAmountChanged();
    void sunMultiplierChanged();
    void fresnelScaleChanged();
    void waterColorChanged();

private:
    float m_softIntersectionFactor = 1.0f;
    float m_reflectionAmount = 0.7f;
    float m_reflectionNoise = 0.075f;
    float m_whiteCapsAmount = 1.0f;
    float m_sunMultiplier = 2.0f;
    float m_fresnelScale = 2.5f;
    QColor m_waterColor = QColor(18, 75, 102);
//    QColor m_waterColor = QColor(31, 82, 88);

    LiTexture *_envMapSamplerRefl = nullptr;
    LiTexture *_oceanBumpMapSampler = nullptr;
    LiTexture *_foamSampler = nullptr;
    LiTexture *_foamSampler2 = nullptr;
    LiTexture *_waterGlossMapSampler = nullptr;
};

#endif // WATERPARAMETERS_P_H
