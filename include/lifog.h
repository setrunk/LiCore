#ifndef LIFOG_H
#define LIFOG_H

#include "licore_global.h"

class LiFogPrivate;

class LICORE_EXPORT LiFog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(double density READ density WRITE setDensity NOTIFY densityChanged)
public:
    explicit LiFog(QObject *parent = nullptr);

    bool enabled() const;
    void setEnabled(bool enabled);

    QColor color() const;
    void setColor(const QColor &color);

    double density() const;
    void setDensity(double density);

signals:
    void enabledChanged();
    void colorChanged();
    void densityChanged();

private:
    Q_DECLARE_PRIVATE(LiFog)
};

#endif // LIFOG_H
