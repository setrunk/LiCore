#ifndef LIPOSTRENDERING_H
#define LIPOSTRENDERING_H

#include "linode.h"

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
public:
    explicit LiPostRendering(QObject *parent = nullptr);

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
