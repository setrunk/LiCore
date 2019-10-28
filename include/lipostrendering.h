#ifndef LIPOSTRENDERING_H
#define LIPOSTRENDERING_H

#include "licore_global.h"

class LiToneMapping;
class LiPostRenderingPrivate;

class LICORE_EXPORT LiPostRendering : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool adjustColorEnabled READ adjustColorEnabled WRITE setAdjustColorEnabled NOTIFY adjustColorEnabledChanged)
    Q_PROPERTY(bool adjustLevelsEnabled READ adjustLevelsEnabled WRITE setAdjustLevelsEnabled NOTIFY adjustLevelsEnabledChanged)
    Q_PROPERTY(bool filterColorEnabled READ filterColorEnabled WRITE setFilterColorEnabled NOTIFY filterColorEnabledChanged)
    Q_PROPERTY(bool selectiveColorEnabled READ selectiveColorEnabled WRITE setSelectiveColorEnabled NOTIFY selectiveColorEnabledChanged)
    Q_PROPERTY(bool colorChartEnabled READ colorChartEnabled WRITE setColorChartEnabled NOTIFY colorChartEnabledChanged)
    Q_PROPERTY(float hue READ hue WRITE setHue NOTIFY hueChanged)
    Q_PROPERTY(float saturation READ saturation WRITE setSaturation NOTIFY saturationChanged)
    Q_PROPERTY(float brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(float gamma READ gamma WRITE setGamma NOTIFY gammaChanged)
    Q_PROPERTY(QVector4D colorLevels READ colorLevels WRITE setColorLevels NOTIFY colorLevelsChanged)
    Q_PROPERTY(QColor filterColor READ filterColor WRITE setFilterColor NOTIFY filterColorChanged)
    Q_PROPERTY(float filterColorDensity READ filterColorDensity WRITE setFilterColorDensity NOTIFY filterColorDensityChanged)
    Q_PROPERTY(QColor selectiveColor READ selectiveColor WRITE setSelectiveColor NOTIFY selectiveColorChanged)
    Q_PROPERTY(QVector4D selectiveColorCMYK READ selectiveColorCMYK WRITE setSelectiveColorCMYK NOTIFY selectiveColorCMYKChanged)
    Q_PROPERTY(QVector4D filmCurve READ filmCurve WRITE setFilmCurve NOTIFY filmCurveChanged)
    Q_PROPERTY(QVector3D colorBalance READ colorBalance WRITE setColorBalance NOTIFY colorBalanceChanged)
    Q_PROPERTY(QVector2D eyeAdaption READ eyeAdaption WRITE setEyeAdaption NOTIFY eyeAdaptionChanged)
    Q_PROPERTY(bool fxaa READ fxaa WRITE setFxaa NOTIFY fxaaChanged)
    Q_PROPERTY(LiToneMapping* toneMapping READ toneMapping)
public:
    explicit LiPostRendering(QObject *parent = nullptr);

    LiToneMapping *toneMapping() const;

    QVector4D filmCurve() const;
    void setFilmCurve(const QVector4D &filmCurve);

    QVector2D eyeAdaption() const;
    void setEyeAdaption(const QVector2D &eyeAdaption);

    bool fxaa() const;
    void setFxaa(bool fxaa);

    QVector3D colorBalance() const;
    void setColorBalance(const QVector3D &colorBalance);

    // adjust color
    bool adjustColorEnabled() const;
    void setAdjustColorEnabled(bool adjustColorEnabled);

    float hue() const;
    void setHue(float hue);

    float saturation() const;
    void setSaturation(float saturation);

    float brightness() const;
    void setBrightness(float brightness);

    // adjust levels
    bool adjustLevelsEnabled() const;
    void setAdjustLevelsEnabled(bool adjustLevelsEnabled);

    float gamma() const;
    void setGamma(float gamma);

    QVector4D colorLevels() const;
    void setColorLevels(const QVector4D &colorLevels);

    // filter color
    bool filterColorEnabled() const;
    void setFilterColorEnabled(bool filterColorEnabled);

    QColor filterColor() const;
    void setFilterColor(const QColor &filterColor);

    float filterColorDensity() const;
    void setFilterColorDensity(float filterColorDensity);

    // selective color
    bool selectiveColorEnabled() const;
    void setSelectiveColorEnabled(bool selectiveColorEnabled);

    QColor selectiveColor() const;
    void setSelectiveColor(const QColor &selectiveColor);

    QVector4D selectiveColorCMYK() const;
    void setSelectiveColorCMYK(const QVector4D &selectiveColorCMYK);

    // color grading
    bool colorChartEnabled() const;
    void setColorChartEnabled(bool colorChartEnabled);

signals:
    void fxaaChanged();
    void colorBalanceChanged();
    void filmCurveChanged();
    void eyeAdaptionChanged();
    void adjustColorEnabledChanged();
    void adjustLevelsEnabledChanged();
    void filterColorEnabledChanged();
    void selectiveColorEnabledChanged();
    void colorChartEnabledChanged();
    void hueChanged();
    void saturationChanged();
    void brightnessChanged();
    void gammaChanged();
    void colorLevelsChanged();
    void filterColorChanged();
    void filterColorDensityChanged();
    void selectiveColorChanged();
    void selectiveColorCMYKChanged();

private:
    Q_DECLARE_PRIVATE(LiPostRendering)
};

#endif // LIPOSTRENDERING_H
