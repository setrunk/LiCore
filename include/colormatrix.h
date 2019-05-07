#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include "licore_global.h"
#include "vector4.h"

/**
 * @brief
 * 颜色转换矩阵。
 */
class LICORE_EXPORT ColorMatrix
{
public:
    /**
     * @brief
     *
     */
    ColorMatrix();

    /**
     * @brief
     *
     * @param i
     * @return float &operator
     */
    float &operator[](int i) { return m[i]; }
    /**
     * @brief
     *
     * @param i
     * @return float operator
     */
    float operator[](int i) const { return m[i]; }

    /**
     * @brief
     *
     * @param i
     * @return Vector4
     */
    Vector4 row(int i) const;

    /**
     * @brief
     *
     * @param rotDegrees
     */
    void setRotation(const QVector3D &rotDegrees);
    /**
     * @brief
     *
     * @param sat
     */
    void setSaturation(float sat);
    /**
     * @brief
     *
     * @param scale
     * @param aScale
     */
    void setScale(const QVector3D &scale, float aScale = 1.f);
    /**
     * @brief
     *
     * @param rScale
     * @param gScale
     * @param bScale
     * @param aScale
     */
    void setScale(float rScale, float gScale, float bScale, float aScale = 1.f);
    /**
     * @brief
     *
     * @param r
     * @param g
     * @param b
     */
    void setTranslation(float r, float g, float b);
    /**
     * @brief
     *
     */
    void reset();

    /**
     * @brief
     *
     * @param matrix
     * @param color
     * @return QColor operator
     */
    friend QColor operator* (const ColorMatrix &matrix, const QColor &color);
    /**
     * @brief
     *
     * @param m1
     * @param m2
     * @return ColorMatrix operator
     */
    friend ColorMatrix operator* (const ColorMatrix &m1, const ColorMatrix &m2);

private:
    /**
     * @brief
     *
     * @param channel
     * @param degrees
     */
    void setRotation(int channel, float degrees);
    float m[20]; /**< TODO: describe */
};

#endif // COLOR_MATRIX_H
