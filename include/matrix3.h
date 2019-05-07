#ifndef MATRIX3_H
#define MATRIX3_H

#include "licore_global.h"
#include "vector3.h"

class Matrix4;
class Quaternion;

/**
 * @brief
 * 双精度浮点3阶矩阵。
 */
class LICORE_EXPORT Matrix3
{
public:
    /**
     * @brief
     *
     */
    inline Matrix3() { setToIdentity(); }
    /**
     * @brief
     *
     * @param column0Row0
     * @param column1Row0
     * @param column2Row0
     * @param column0Row1
     * @param column1Row1
     * @param column2Row1
     * @param column0Row2
     * @param column1Row2
     * @param column2Row2
     */
    inline Matrix3(double column0Row0, double column1Row0, double column2Row0,
                   double column0Row1, double column1Row1, double column2Row1,
                   double column0Row2, double column1Row2, double column2Row2);
    /**
     * @brief
     *
     * @param values
     */
    explicit Matrix3(const double *values);

    /**
     * @brief
     *
     * @param row
     * @param column
     * @return const double &operator
     */
    inline const double& operator()(int row, int column) const;
    /**
     * @brief
     *
     * @param row
     * @param column
     * @return double &operator
     */
    inline double& operator()(int row, int column);

    /**
     * @brief
     *
     * @param i
     * @return const double &operator
     */
    inline const double& operator[](int i) const;
    /**
     * @brief
     *
     * @param i
     * @return double &operator
     */
    inline double& operator[](int i);

    /**
     * @brief
     *
     * @param factor
     * @return Matrix3 &operator
     */
    inline Matrix3& operator*=(double factor);

    /**
     * @brief
     *
     * @param scale
     * @return Matrix3
     */
    inline Matrix3& multiplyByScale(const Vector3 &scale);
    /**
     * @brief
     *
     * @return Vector3
     */
    inline Vector3 getScale() const;

    /**
     * @brief
     *
     * @param index
     * @return Vector3
     */
    inline Vector3 column(int index) const;
    /**
     * @brief
     *
     * @param index
     * @param value
     */
    inline void setColumn(int index, const Vector3& value);

    /**
     * @brief
     *
     * @param index
     * @return Vector3
     */
    inline Vector3 row(int index) const;
    /**
     * @brief
     *
     * @param index
     * @param value
     */
    inline void setRow(int index, const Vector3& value);

    /**
     * @brief
     *
     * @return double
     */
    inline double *data() { return *m; }
    /**
     * @brief
     *
     * @return const double
     */
    inline const double *data() const { return *m; }
    /**
     * @brief
     *
     * @return const double
     */
    inline const double *constData() const { return *m; }

    /**
     * @brief
     *
     */
    inline void setToIdentity();
    /**
     * @brief
     *
     * @return bool
     */
    inline bool isIdentity() const;
    /**
     * @brief
     *
     * @return Matrix3
     */
    inline Matrix3 transposed() const;

    /**
     * @brief
     *
     * @return operator
     */
    operator QMatrix3x3() const;

    /**
     * @brief
     *
     * @param matrix
     * @param vector
     * @return Vector3 operator
     */
    friend Vector3 operator*(const Matrix3& matrix, const Vector3& vector);
    /**
     * @brief
     *
     * @param left
     * @param right
     * @return Matrix3 operator
     */
    friend Matrix3 operator*(const Matrix3& left, const Matrix3& right);

    /**
     * @brief
     *
     * @param m
     * @param Q
     * @param D
     * @param U
     */
    static void decomposeMatrix3(const Matrix3 &m, Matrix3 &Q, Vector3 &D, Vector3 &U);

private:
    double m[3][3];          // Column-major order to match OpenGL. /**< TODO: describe */

    // Construct without initializing identity matrix.
    /**
     * @brief
     *
     * @param int
     */
    explicit Matrix3(int) { }

    friend class Matrix4;
    friend class Quaternion;
};

Q_DECLARE_METATYPE(Matrix3)
Q_DECLARE_TYPEINFO(Matrix3, Q_PRIMITIVE_TYPE);

/**
 * @brief
 *
 * @param column0Row0
 * @param column1Row0
 * @param column2Row0
 * @param column0Row1
 * @param column1Row1
 * @param column2Row1
 * @param column0Row2
 * @param column1Row2
 * @param column2Row2
 */
inline Matrix3::Matrix3(double column0Row0, double column1Row0, double column2Row0,
                        double column0Row1, double column1Row1, double column2Row1,
                        double column0Row2, double column1Row2, double column2Row2)
{
    m[0][0] = column0Row0;
    m[0][1] = column0Row1;
    m[0][2] = column0Row2;
    m[1][0] = column1Row0;
    m[1][1] = column1Row1;
    m[1][2] = column1Row2;
    m[2][0] = column2Row0;
    m[2][1] = column2Row1;
    m[2][2] = column2Row2;
}

/**
 * @brief
 *
 * @param values
 */
inline Matrix3::Matrix3(const double *values)
{
    memcpy(data(), values, sizeof(double)*9);
}

/**
 * @brief
 *
 * @param i
 * @return const double &Matrix3::operator
 */
inline const double& Matrix3::operator[](int i) const
{
    Q_ASSERT(i >= 0 && i < 9);
    return constData()[i];
}

/**
 * @brief
 *
 * @param i
 * @return double &Matrix3::operator
 */
inline double& Matrix3::operator[](int i)
{
    Q_ASSERT(i >= 0 && i < 9);
    return data()[i];
}

/**
 * @brief
 *
 */
inline void Matrix3::setToIdentity()
{
    m[0][0] = 1.0;
    m[0][1] = 0.0;
    m[0][2] = 0.0;
    m[1][0] = 0.0;
    m[1][1] = 1.0;
    m[1][2] = 0.0;
    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;
}

/**
 * @brief
 *
 * @return bool
 */
inline bool Matrix3::isIdentity() const
{
    return  m[0][0] == 1.0 &&
            m[0][1] == 0.0 &&
            m[0][2] == 0.0 &&
            m[1][0] == 0.0 &&
            m[1][1] == 1.0 &&
            m[1][2] == 0.0 &&
            m[2][0] == 0.0 &&
            m[2][1] == 0.0 &&
            m[2][2] == 1.0;
}

/**
 * @brief
 *
 * @return Matrix3
 */
inline Matrix3 Matrix3::transposed() const
{
    Matrix3 result(1); // The "1" says to not load the identity.
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            result.m[col][row] = m[row][col];
        }
    }
    return result;
}

/**
 * @brief
 *
 * @param aRow
 * @param aColumn
 * @return const double &Matrix3::operator
 */
inline const double& Matrix3::operator()(int aRow, int aColumn) const
{
    Q_ASSERT(aRow >= 0 && aRow < 3 && aColumn >= 0 && aColumn < 3);
    return m[aColumn][aRow];
}

/**
 * @brief
 *
 * @param aRow
 * @param aColumn
 * @return double &Matrix3::operator
 */
inline double& Matrix3::operator()(int aRow, int aColumn)
{
    Q_ASSERT(aRow >= 0 && aRow < 3 && aColumn >= 0 && aColumn < 3);
    return m[aColumn][aRow];
}

/**
 * @brief
 *
 * @param factor
 * @return Matrix3 &Matrix3::operator
 */
inline Matrix3& Matrix3::operator*=(double factor)
{
    m[0][0] *= factor;
    m[0][1] *= factor;
    m[0][2] *= factor;
    m[1][0] *= factor;
    m[1][1] *= factor;
    m[1][2] *= factor;
    m[2][0] *= factor;
    m[2][1] *= factor;
    m[2][2] *= factor;
    return *this;
}

/**
 * @brief
 *
 * @param matrix
 * @param vector
 * @return Vector3 operator
 */
inline Vector3 operator*(const Matrix3& matrix, const Vector3& vector)
{
    double x, y, z;
    x = vector.x() * matrix.m[0][0] +
        vector.y() * matrix.m[1][0] +
        vector.z() * matrix.m[2][0];
    y = vector.x() * matrix.m[0][1] +
        vector.y() * matrix.m[1][1] +
        vector.z() * matrix.m[2][1];
    z = vector.x() * matrix.m[0][2] +
        vector.y() * matrix.m[1][2] +
        vector.z() * matrix.m[2][2];
    return Vector3(x, y, z);
}

/**
 * @brief
 *
 * @param m1
 * @param m2
 * @return Matrix3 operator
 */
inline Matrix3 operator*(const Matrix3 &m1, const Matrix3 &m2)
{
    Matrix3 m(1);

    m.m[0][0] = m1.m[0][0] * m2.m[0][0]
              + m1.m[1][0] * m2.m[0][1]
              + m1.m[2][0] * m2.m[0][2];
    m.m[0][1] = m1.m[0][1] * m2.m[0][0]
              + m1.m[1][1] * m2.m[0][1]
              + m1.m[2][1] * m2.m[0][2];
    m.m[0][2] = m1.m[0][2] * m2.m[0][0]
              + m1.m[1][2] * m2.m[0][1]
              + m1.m[2][2] * m2.m[0][2];

    m.m[1][0] = m1.m[0][0] * m2.m[1][0]
              + m1.m[1][0] * m2.m[1][1]
              + m1.m[2][0] * m2.m[1][2];
    m.m[1][1] = m1.m[0][1] * m2.m[1][0]
              + m1.m[1][1] * m2.m[1][1]
              + m1.m[2][1] * m2.m[1][2];
    m.m[1][2] = m1.m[0][2] * m2.m[1][0]
              + m1.m[1][2] * m2.m[1][1]
              + m1.m[2][2] * m2.m[1][2];

    m.m[2][0] = m1.m[0][0] * m2.m[2][0]
              + m1.m[1][0] * m2.m[2][1]
              + m1.m[2][0] * m2.m[2][2];
    m.m[2][1] = m1.m[0][1] * m2.m[2][0]
              + m1.m[1][1] * m2.m[2][1]
              + m1.m[2][1] * m2.m[2][2];
    m.m[2][2] = m1.m[0][2] * m2.m[2][0]
              + m1.m[1][2] * m2.m[2][1]
              + m1.m[2][2] * m2.m[2][2];

    return m;
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Matrix3::getScale() const
{
    return Vector3(column(0).length(), column(1).length(), column(2).length());
}

/**
 * @brief
 *
 * @param scale
 * @return Matrix3
 */
inline Matrix3 &Matrix3::multiplyByScale(const Vector3 &scale)
{
    m[0][0] *= scale.x();
    m[0][1] *= scale.x();
    m[0][2] *= scale.x();
    m[1][0] *= scale.y();
    m[1][1] *= scale.y();
    m[1][2] *= scale.y();
    m[2][0] *= scale.z();
    m[2][1] *= scale.z();
    m[2][2] *= scale.z();
    return *this;
}

/**
 * @brief
 *
 * @param index
 * @return Vector3
 */
inline Vector3 Matrix3::column(int index) const
{
    Q_ASSERT(index >= 0 && index < 3);
    return Vector3(m[index][0], m[index][1], m[index][2]);
}

/**
 * @brief
 *
 * @param index
 * @param value
 */
inline void Matrix3::setColumn(int index, const Vector3& value)
{
    Q_ASSERT(index >= 0 && index < 3);
    m[index][0] = value.x();
    m[index][1] = value.y();
    m[index][2] = value.z();
}

/**
 * @brief
 *
 * @param index
 * @return Vector3
 */
inline Vector3 Matrix3::row(int index) const
{
    Q_ASSERT(index >= 0 && index < 3);
    return Vector3(m[0][index], m[1][index], m[2][index]);
}

/**
 * @brief
 *
 * @param index
 * @param value
 */
inline void Matrix3::setRow(int index, const Vector3& value)
{
    Q_ASSERT(index >= 0 && index < 3);
    m[0][index] = value.x();
    m[1][index] = value.y();
    m[2][index] = value.z();
}

/**
 * @brief
 *
 * @return Matrix3::operator
 */
inline Matrix3::operator QMatrix3x3() const
{
    QMatrix3x3 result;
    float *dst = result.data();
    const double *src = constData();
    for (int i = 0; i < 9; ++i)
        dst[i] = src[i];
    return result;
}

#endif // MATRIX3_H
