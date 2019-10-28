#ifndef LITREEMATERIAL_H
#define LITREEMATERIAL_H

#include "licore_global.h"

class LICORE_EXPORT LiTreeMaterial : public QObject
{
    Q_OBJECT
public:
    explicit LiTreeMaterial(QObject *parent = nullptr);

    QColor specularColor() const { return m_specularColor; }
    float glossiness() const { return m_glossiness; }
    float thickness() const { return m_thickness; }
    float subsurfacePower() const { return m_subsurfacePower; }

    void setSpecularColor(const QColor &color);
    void setGlossiness(float value);
    void setThickness(float value);
    void setSubsurfacePower(float value);

signals:
    void specularColorChanged();
    void glossinessChanged();
    void thicknessChanged();
    void subsurfacePowerChanged();

private:
    QColor m_specularColor = Qt::white;
    float m_glossiness = 0.5f;
    float m_thickness = 0.5f;
    float m_subsurfacePower = 1.f;
};

#endif // LITREEMATERIAL_H
