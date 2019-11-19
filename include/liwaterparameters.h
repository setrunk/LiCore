#ifndef WATERPARAMETERS_P_H
#define WATERPARAMETERS_P_H

#include "licore_global.h"

class LiTexture;
class LiBuffer;
class LiUniformBlock;

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

    LiUniformBlock *uniformBlock();

    LiTexture *envMapSamplerRefl() const
    {
        return m_envMapSamplerRefl;
    }

    LiTexture *oceanBumpMapSampler() const
    {
        return m_oceanBumpMapSampler;
    }

    LiTexture *foamSampler() const
    {
        return m_foamSampler;
    }

    LiTexture *foamSampler2() const
    {
        return m_foamSampler2;
    }

    LiTexture *waterGlossMapSampler() const
    {
        return m_waterGlossMapSampler;
    }

    bool ready() const
    {
        return m_oceanBumpMapSampler &&
               m_foamSampler &&
                m_foamSampler2 &&
               m_waterGlossMapSampler;
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
    float m_reflectionAmount = 0.75f;
    float m_reflectionNoise = 0.038f;
    float m_whiteCapsAmount = 0.05f;
    float m_sunMultiplier = 1.0f;
    float m_fresnelScale = 1.5f;
    QColor m_waterColor = QColor(5, 26, 31);
//    QColor m_waterColor = QColor(31, 82, 88);

    LiUniformBlock *m_uniformBlock = nullptr;
    LiTexture *m_envMapSamplerRefl = nullptr;
    LiTexture *m_oceanBumpMapSampler = nullptr;
    LiTexture *m_foamSampler = nullptr;
    LiTexture *m_foamSampler2 = nullptr;
    LiTexture *m_waterGlossMapSampler = nullptr;
};

#endif // WATERPARAMETERS_P_H
