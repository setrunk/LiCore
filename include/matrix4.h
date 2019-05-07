#ifndef MATRIX4_H
#define MATRIX4_H

#include "licore_global.h"
#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"
#include "matrix3.h"
#include "plane.h"

/**
 * @brief
 * 双精度浮点4阶矩阵，用于不同坐标系间的变换计算。
 * 内部数组采用column-major的排列方式。
 */
class LICORE_EXPORT Matrix4
{
public:
    /**
     * @brief
     *
     */
    inline Matrix4() { setToIdentity(); }
    /**
     * @brief
     *
     * @param values
     */
    explicit Matrix4(const double *values);
    /**
     * @brief
     *
     * @param m11
     * @param m12
     * @param m13
     * @param m14
     * @param m21
     * @param m22
     * @param m23
     * @param m24
     * @param m31
     * @param m32
     * @param m33
     * @param m34
     * @param m41
     * @param m42
     * @param m43
     * @param m44
     */
    inline Matrix4(double m11, double m12, double m13, double m14,
                   double m21, double m22, double m23, double m24,
                   double m31, double m32, double m33, double m34,
                   double m41, double m42, double m43, double m44);
    /**
     * @brief
     *
     * @param values
     * @param cols
     * @param rows
     */
    Matrix4(const double *values, int cols, int rows);

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
     * @param index
     * @return Vector4
     */
    inline Vector4 column(int index) const;
    /**
     * @brief
     *
     * @param index
     * @param value
     */
    inline void setColumn(int index, const Vector4& value);

    /**
     * @brief
     *
     * @param index
     * @return Vector4
     */
    inline Vector4 row(int index) const;
    /**
     * @brief
     *
     * @param index
     * @param value
     */
    inline void setRow(int index, const Vector4& value);

    /**
     * @brief
     *
     * @return bool
     */
    inline bool isIdentity() const;
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
    inline bool isAffine() const;
    /**
     * @brief
     *
     * @return bool
     */
    inline bool hasScale() const;
    /**
     * @brief
     *
     * @return Vector3
     */
    inline Vector3 getScale() const;

    /**
     * @brief
     *
     * @param value
     */
    inline void fill(double value);

    /**
     * @brief
     *
     * @return Vector3
     */
    inline Vector3 translation() const;
    /**
     * @brief
     *
     * @param translation
     */
    inline void setTranslation(const Vector3 &translation);

    /**
     * @brief
     *
     * @return double
     */
    double determinant() const;
    /**
     * @brief
     *
     * @param invertible
     * @return Matrix4
     */
    Matrix4 inverted(bool *invertible = 0) const;
    /**
     * @brief
     *
     * @return Matrix4
     */
    Matrix4 inverseTransformation() const;
    /**
     * @brief
     *
     * @return Matrix4
     */
    Matrix4 transposed() const;
    /**
     * @brief
     *
     * @return Matrix3
     */
    Matrix3 normalMatrix() const;
    /**
     * @brief
     *
     * @return Matrix3
     */
    Matrix3 toMatrix3() const;
    /**
     * @brief
     *
     * @return Matrix3
     */
    Matrix3 rotationMatrix() const;

    /**
     * @brief
     *
     * @param position
     * @param orientation
     * @param scale
     */
    void compose(const Vector3 &position, const Quaternion &orientation, const Vector3 &scale);
    /**
     * @brief
     *
     * @param position
     * @param orientation
     * @param scale
     */
    void decompose(Vector3 &position, Quaternion &orientation, Vector3 &scale) const;

    /**
     * @brief
     *
     * @param other
     * @return Matrix4 &operator
     */
    inline Matrix4& operator+=(const Matrix4& other);
    /**
     * @brief
     *
     * @param other
     * @return Matrix4 &operator
     */
    inline Matrix4& operator-=(const Matrix4& other);
    /**
     * @brief
     *
     * @param other
     * @return Matrix4 &operator
     */
    inline Matrix4& operator*=(const Matrix4& other);
    /**
     * @brief
     *
     * @param factor
     * @return Matrix4 &operator
     */
    inline Matrix4& operator*=(double factor);
    /**
     * @brief
     *
     * @param divisor
     * @return Matrix4 &operator
     */
    Matrix4& operator/=(double divisor);
    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    inline bool operator==(const Matrix4& other) const;
    /**
     * @brief
     *
     * @param other
     * @return bool operator
     */
    inline bool operator!=(const Matrix4& other) const;

    /**
     * @brief
     *
     * @param m1
     * @param m2
     * @return Matrix4 operator
     */
    friend Matrix4 operator+(const Matrix4& m1, const Matrix4& m2);
    /**
     * @brief
     *
     * @param m1
     * @param m2
     * @return Matrix4 operator
     */
    friend Matrix4 operator-(const Matrix4& m1, const Matrix4& m2);
    /**
     * @brief
     *
     * @param m1
     * @param m2
     * @return Matrix4 operator
     */
    friend Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
    /**
     * @brief
     *
     * @param matrix
     * @param vector
     * @return Vector3 operator
     */
    friend Vector3 operator*(const Matrix4& matrix, const Vector3& vector);
    /**
     * @brief
     *
     * @param vector
     * @param matrix
     * @return Vector3 operator
     */
    friend Vector3 operator*(const Vector3& vector, const Matrix4& matrix);
    /**
     * @brief
     *
     * @param vector
     * @param matrix
     * @return Vector4 operator
     */
    friend Vector4 operator*(const Vector4& vector, const Matrix4& matrix);
    /**
     * @brief
     *
     * @param matrix
     * @param vector
     * @return Vector4 operator
     */
    friend Vector4 operator*(const Matrix4& matrix, const Vector4& vector);
    /**
     * @brief
     *
     * @param matrix
     * @param plane
     * @return Plane operator
     */
    friend Plane operator*(const Matrix4& matrix, const Plane& plane);
    /**
     * @brief
     *
     * @param matrix
     * @return Matrix4 operator
     */
    friend Matrix4 operator-(const Matrix4& matrix);
    /**
     * @brief
     *
     * @param factor
     * @param matrix
     * @return Matrix4 operator
     */
    friend Matrix4 operator*(double factor, const Matrix4& matrix);
    /**
     * @brief
     *
     * @param matrix
     * @param factor
     * @return Matrix4 operator
     */
    friend Matrix4 operator*(const Matrix4& matrix, double factor);
    /**
     * @brief
     *
     * @param matrix
     * @param divisor
     * @return Matrix4 operator
     */
    friend Matrix4 operator/(const Matrix4& matrix, double divisor);
    /**
     * @brief
     *
     * @param m1
     * @param m2
     * @return bool
     */
    friend inline bool qFuzzyCompare(const Matrix4& m1, const Matrix4& m2);

    /**
     * @brief
     *
     * @param vector
     */
    void translate(const Vector3& vector);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param z
     */
    void translate(double x, double y, double z);
    /**
     * @brief
     *
     * @param angle
     * @param vector
     */
    void rotate(double angle, const Vector3& vector);
    /**
     * @brief
     *
     * @param angle
     * @param x
     * @param y
     * @param z
     */
    void rotate(double angle, double x, double y, double z = 0.0);
    /**
     * @brief
     *
     * @param quaternion
     */
    void rotate(const Quaternion& quaternion);
    /**
     * @brief
     *
     * @param vector
     */
    void scale(const Vector3& vector);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param z
     */
    void scale(double x, double y, double z);
    /**
     * @brief
     *
     * @param factor
     */
    void scale(double factor);

    /**
     * @brief
     *
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param nearPlane
     * @param farPlane
     */
    void ortho(double left, double right, double bottom, double top, double nearPlane, double farPlane);
    /**
     * @brief
     *
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param nearPlane
     * @param farPlane
     */
    void frustum(double left, double right, double bottom, double top, double nearPlane, double farPlane);
    /**
     * @brief
     *
     * @param verticalAngle
     * @param aspectRatio
     * @param nearPlane
     * @param farPlane
     */
    void perspective(double verticalAngle, double aspectRatio, double nearPlane, double farPlane);
    /**
     * @brief
     *
     * @param eye
     * @param center
     * @param up
     */
    void lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
    /**
     * @brief
     *
     * @param eye
     * @param forward
     * @param up
     * @param side
     */
    void lookAt(const Vector3& eye, const Vector3& forward, const Vector3& up, const Vector3 &side);
    /**
     * @brief
     *
     */
    void flipCoordinates();

    /**
     * @brief
     *
     * @param point
     * @return Vector3
     */
    Vector3 map(const Vector3& point) const;
    /**
     * @brief
     *
     * @param vector
     * @return Vector3
     */
    Vector3 mapVector(const Vector3& vector) const;
    /**
     * @brief
     *
     * @param point
     * @return Vector4
     */
    Vector4 map(const Vector4& point) const;

    /**
     * @brief
     *
     * @return double
     */
    inline double *data();
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
    void optimize();

    /**
     * @brief
     *
     * @return operator
     */
    operator QMatrix4x4() const;
    /**
     * @brief
     *
     * @return operator
     */
    operator QVariant() const;

    /**
     * @brief
     *
     * @param translation
     * @return Matrix4
     */
    static Matrix4 fromTranslation(const Vector3 &translation);
    /**
     * @brief
     *
     * @param scale
     * @return Matrix4
     */
    static Matrix4 fromScale(const Vector3 &scale);
    /**
     * @brief
     *
     * @param rotation
     * @param translation
     * @return Matrix4
     */
    static Matrix4 fromRotationTranslation(const Matrix3 &rotation, const Vector3 &translation);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param width
     * @param height
     * @param nearDepthRange
     * @param farDepthRange
     * @return Matrix4
     */
    static Matrix4 computeViewportTransformation(double x, double y, double width, double height, double nearDepthRange = 0, double farDepthRange = 1);
    /**
     * @brief
     *
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param nearPlane
     * @param farPlane
     * @return Matrix4
     */
    static Matrix4 computePerspectiveOffCenter(double left, double right, double bottom, double top, double nearPlane, double farPlane);
    /**
     * @brief
     *
     * @param left
     * @param right
     * @param bottom
     * @param top
     * @param nearPlane
     * @return Matrix4
     */
    static Matrix4 computeInfinitePerspectiveOffCenter(double left, double right, double bottom, double top, double nearPlane);

private:
    double m[4][4];          // Column-major order to match OpenGL. /**< TODO: describe */
    int flagBits;           // Flag bits from the enum below. /**< TODO: describe */

    // When matrices are multiplied, the flag bits are or-ed together.
    /**
     * @brief
     *
     */
    enum {
        Identity        = 0x0000, // Identity matrix
        Translation     = 0x0001, // Contains a translation
        Scale           = 0x0002, // Contains a scale
        Rotation2D      = 0x0004, // Contains a rotation about the Z axis
        Rotation        = 0x0008, // Contains an arbitrary rotation
        Perspective     = 0x0010, // Last row is different from (0, 0, 0, 1)
        General         = 0x001f  // General matrix, unknown contents
    };

    // Construct without initializing identity matrix.
    /**
     * @brief
     *
     * @param int
     */
    explicit Matrix4(int) { }

    /**
     * @brief
     *
     * @return Matrix4
     */
    Matrix4 orthonormalInverse() const;

    /**
     * @brief
     *
     * @param angle
     * @param x
     * @param y
     * @param z
     */
    void projectedRotate(double angle, double x, double y, double z);
};

Q_DECLARE_METATYPE(Matrix4)
Q_DECLARE_TYPEINFO(Matrix4, Q_PRIMITIVE_TYPE);

/**
 * @brief
 *
 * @param m11
 * @param m12
 * @param m13
 * @param m14
 * @param m21
 * @param m22
 * @param m23
 * @param m24
 * @param m31
 * @param m32
 * @param m33
 * @param m34
 * @param m41
 * @param m42
 * @param m43
 * @param m44
 */
inline Matrix4::Matrix4
        (double m11, double m12, double m13, double m14,
         double m21, double m22, double m23, double m24,
         double m31, double m32, double m33, double m34,
         double m41, double m42, double m43, double m44)
{
    m[0][0] = m11; m[0][1] = m21; m[0][2] = m31; m[0][3] = m41;
    m[1][0] = m12; m[1][1] = m22; m[1][2] = m32; m[1][3] = m42;
    m[2][0] = m13; m[2][1] = m23; m[2][2] = m33; m[2][3] = m43;
    m[3][0] = m14; m[3][1] = m24; m[3][2] = m34; m[3][3] = m44;
    flagBits = General;
}

/**
 * @brief
 *
 * @param aRow
 * @param aColumn
 * @return const double &Matrix4::operator
 */
inline const double& Matrix4::operator()(int aRow, int aColumn) const
{
    Q_ASSERT(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
    return m[aColumn][aRow];
}

/**
 * @brief
 *
 * @param aRow
 * @param aColumn
 * @return double &Matrix4::operator
 */
inline double& Matrix4::operator()(int aRow, int aColumn)
{
    Q_ASSERT(aRow >= 0 && aRow < 4 && aColumn >= 0 && aColumn < 4);
    flagBits = General;
    return m[aColumn][aRow];
}

/**
 * @brief
 *
 * @param i
 * @return const double &Matrix4::operator
 */
inline const double& Matrix4::operator[](int i) const
{
    Q_ASSERT(i >= 0 && i < 16);
    return constData()[i];
}

/**
 * @brief
 *
 * @param i
 * @return double &Matrix4::operator
 */
inline double& Matrix4::operator[](int i)
{
    Q_ASSERT(i >= 0 && i < 16);
    return data()[i];
}

/**
 * @brief
 *
 * @param index
 * @return Vector4
 */
inline Vector4 Matrix4::column(int index) const
{
    Q_ASSERT(index >= 0 && index < 4);
    return Vector4(m[index][0], m[index][1], m[index][2], m[index][3]);
}

/**
 * @brief
 *
 * @param index
 * @param value
 */
inline void Matrix4::setColumn(int index, const Vector4& value)
{
    Q_ASSERT(index >= 0 && index < 4);
    m[index][0] = value.x();
    m[index][1] = value.y();
    m[index][2] = value.z();
    m[index][3] = value.w();
    flagBits = General;
}

/**
 * @brief
 *
 * @param index
 * @return Vector4
 */
inline Vector4 Matrix4::row(int index) const
{
    Q_ASSERT(index >= 0 && index < 4);
    return Vector4(m[0][index], m[1][index], m[2][index], m[3][index]);
}

/**
 * @brief
 *
 * @param index
 * @param value
 */
inline void Matrix4::setRow(int index, const Vector4& value)
{
    Q_ASSERT(index >= 0 && index < 4);
    m[0][index] = value.x();
    m[1][index] = value.y();
    m[2][index] = value.z();
    m[3][index] = value.w();
    flagBits = General;
}


/**
 * @brief
 *
 * @param matrix
 * @param divisor
 * @return Matrix4 operator
 */
inline Matrix4 operator/(const Matrix4& matrix, double divisor)
{
    Matrix4 m(1); // The "1" says to not load the identity.
    m.m[0][0] = matrix.m[0][0] / divisor;
    m.m[0][1] = matrix.m[0][1] / divisor;
    m.m[0][2] = matrix.m[0][2] / divisor;
    m.m[0][3] = matrix.m[0][3] / divisor;
    m.m[1][0] = matrix.m[1][0] / divisor;
    m.m[1][1] = matrix.m[1][1] / divisor;
    m.m[1][2] = matrix.m[1][2] / divisor;
    m.m[1][3] = matrix.m[1][3] / divisor;
    m.m[2][0] = matrix.m[2][0] / divisor;
    m.m[2][1] = matrix.m[2][1] / divisor;
    m.m[2][2] = matrix.m[2][2] / divisor;
    m.m[2][3] = matrix.m[2][3] / divisor;
    m.m[3][0] = matrix.m[3][0] / divisor;
    m.m[3][1] = matrix.m[3][1] / divisor;
    m.m[3][2] = matrix.m[3][2] / divisor;
    m.m[3][3] = matrix.m[3][3] / divisor;
    m.flagBits = Matrix4::General;
    return m;
}

/**
 * @brief
 *
 * @return bool
 */
inline bool Matrix4::isIdentity() const
{
    return flagBits == Identity;

//    if (flagBits == Identity)
//        return true;
//    if (m[0][0] != 1.0 || m[0][1] != 0.0 || m[0][2] != 0.0)
//        return false;
//    if (m[0][3] != 0.0 || m[1][0] != 0.0 || m[1][1] != 1.0)
//        return false;
//    if (m[1][2] != 0.0 || m[1][3] != 0.0 || m[2][0] != 0.0)
//        return false;
//    if (m[2][1] != 0.0 || m[2][2] != 1.0 || m[2][3] != 0.0)
//        return false;
//    if (m[3][0] != 0.0 || m[3][1] != 0.0 || m[3][2] != 0.0)
//        return false;
//    return (m[3][3] == 1.0);
}

/**
 * @brief
 *
 */
inline void Matrix4::setToIdentity()
{
    m[0][0] = 1.0;
    m[0][1] = 0.0;
    m[0][2] = 0.0;
    m[0][3] = 0.0;
    m[1][0] = 0.0;
    m[1][1] = 1.0;
    m[1][2] = 0.0;
    m[1][3] = 0.0;
    m[2][0] = 0.0;
    m[2][1] = 0.0;
    m[2][2] = 1.0;
    m[2][3] = 0.0;
    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
    flagBits = Identity;
}

/**
 * @brief
 *
 * @return bool
 */
inline bool Matrix4::isAffine() const
{
    return m[0][3] == 0.0 && m[1][3] == 0.0 && m[2][3] == 0.0 && m[3][3] == 1.0;
}

/**
 * @brief
 *
 * @return bool
 */
inline bool Matrix4::hasScale() const
{
    const Matrix4& mm = *this;

    // If the columns are orthonormal and form a right-handed system, then there is no scale
    double t = determinant();
    if (!qFuzzyIsNull(t - 1.0))
        return true;
    t = mm(0, 0) * mm(0, 0) + mm(1, 0) * mm(1, 0) + mm(2, 0) * mm(2, 0);
    if (!qFuzzyIsNull(t - 1.0))
        return true;
    t = mm(0, 1) * mm(0, 1) + mm(1, 1) * mm(1, 1) + mm(2, 1) * mm(2, 1);
    if (!qFuzzyIsNull(t - 1.0))
        return true;
    t = mm(0, 2) * mm(0, 2) + mm(1, 2) * mm(1, 2) + mm(2, 2) * mm(2, 2);
    if (!qFuzzyIsNull(t - 1.0))
        return true;
    return false;
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Matrix4::getScale() const
{
    const double *vals = constData();
    double x = Vector3(vals[0], vals[1], vals[2]).length();
    double y = Vector3(vals[4], vals[5], vals[6]).length();
    double z = Vector3(vals[8], vals[9], vals[10]).length();
    return Vector3(x, y, z);
}

/**
 * @brief
 *
 * @param value
 */
inline void Matrix4::fill(double value)
{
    m[0][0] = value;
    m[0][1] = value;
    m[0][2] = value;
    m[0][3] = value;
    m[1][0] = value;
    m[1][1] = value;
    m[1][2] = value;
    m[1][3] = value;
    m[2][0] = value;
    m[2][1] = value;
    m[2][2] = value;
    m[2][3] = value;
    m[3][0] = value;
    m[3][1] = value;
    m[3][2] = value;
    m[3][3] = value;
    flagBits = General;
}

/**
 * @brief
 *
 * @return Vector3
 */
inline Vector3 Matrix4::translation() const
{
    return Vector3(m[3][0], m[3][1], m[3][2]);
}

/**
 * @brief
 *
 * @param translation
 */
inline void Matrix4::setTranslation(const Vector3 &translation)
{
    m[3][0] = translation.x();
    m[3][1] = translation.y();
    m[3][2] = translation.z();
    flagBits |= Translation;
}

/**
 * @brief
 *
 * @param other
 * @return Matrix4 &Matrix4::operator
 */
inline Matrix4& Matrix4::operator+=(const Matrix4& other)
{
    m[0][0] += other.m[0][0];
    m[0][1] += other.m[0][1];
    m[0][2] += other.m[0][2];
    m[0][3] += other.m[0][3];
    m[1][0] += other.m[1][0];
    m[1][1] += other.m[1][1];
    m[1][2] += other.m[1][2];
    m[1][3] += other.m[1][3];
    m[2][0] += other.m[2][0];
    m[2][1] += other.m[2][1];
    m[2][2] += other.m[2][2];
    m[2][3] += other.m[2][3];
    m[3][0] += other.m[3][0];
    m[3][1] += other.m[3][1];
    m[3][2] += other.m[3][2];
    m[3][3] += other.m[3][3];
    flagBits = General;
    return *this;
}

/**
 * @brief
 *
 * @param other
 * @return Matrix4 &Matrix4::operator
 */
inline Matrix4& Matrix4::operator-=(const Matrix4& other)
{
    m[0][0] -= other.m[0][0];
    m[0][1] -= other.m[0][1];
    m[0][2] -= other.m[0][2];
    m[0][3] -= other.m[0][3];
    m[1][0] -= other.m[1][0];
    m[1][1] -= other.m[1][1];
    m[1][2] -= other.m[1][2];
    m[1][3] -= other.m[1][3];
    m[2][0] -= other.m[2][0];
    m[2][1] -= other.m[2][1];
    m[2][2] -= other.m[2][2];
    m[2][3] -= other.m[2][3];
    m[3][0] -= other.m[3][0];
    m[3][1] -= other.m[3][1];
    m[3][2] -= other.m[3][2];
    m[3][3] -= other.m[3][3];
    flagBits = General;
    return *this;
}

/**
 * @brief
 *
 * @param other
 * @return Matrix4 &Matrix4::operator
 */
inline Matrix4& Matrix4::operator*=(const Matrix4& other)
{
    if (other.flagBits == Identity)
        return *this;

    if (flagBits == Identity)
    {
        *this = other;
        return *this;
    }

    flagBits |= other.flagBits;

    if (flagBits < Rotation2D) {
        m[3][0] += m[0][0] * other.m[3][0];
        m[3][1] += m[1][1] * other.m[3][1];
        m[3][2] += m[2][2] * other.m[3][2];

        m[0][0] *= other.m[0][0];
        m[1][1] *= other.m[1][1];
        m[2][2] *= other.m[2][2];
        return *this;
    }

    double m0, m1, m2;
    m0 =  m[0][0] * other.m[0][0]
        + m[1][0] * other.m[0][1]
        + m[2][0] * other.m[0][2]
        + m[3][0] * other.m[0][3];
    m1 =  m[0][0] * other.m[1][0]
        + m[1][0] * other.m[1][1]
        + m[2][0] * other.m[1][2]
        + m[3][0] * other.m[1][3];
    m2 =  m[0][0] * other.m[2][0]
        + m[1][0] * other.m[2][1]
        + m[2][0] * other.m[2][2]
        + m[3][0] * other.m[2][3];
    m[3][0] = m[0][0] * other.m[3][0]
            + m[1][0] * other.m[3][1]
            + m[2][0] * other.m[3][2]
            + m[3][0] * other.m[3][3];
    m[0][0] = m0;
    m[1][0] = m1;
    m[2][0] = m2;

    m0 =  m[0][1] * other.m[0][0]
        + m[1][1] * other.m[0][1]
        + m[2][1] * other.m[0][2]
        + m[3][1] * other.m[0][3];
    m1 =  m[0][1] * other.m[1][0]
        + m[1][1] * other.m[1][1]
        + m[2][1] * other.m[1][2]
        + m[3][1] * other.m[1][3];
    m2 =  m[0][1] * other.m[2][0]
        + m[1][1] * other.m[2][1]
        + m[2][1] * other.m[2][2]
        + m[3][1] * other.m[2][3];
    m[3][1] = m[0][1] * other.m[3][0]
            + m[1][1] * other.m[3][1]
            + m[2][1] * other.m[3][2]
            + m[3][1] * other.m[3][3];
    m[0][1] = m0;
    m[1][1] = m1;
    m[2][1] = m2;

    m0 =  m[0][2] * other.m[0][0]
        + m[1][2] * other.m[0][1]
        + m[2][2] * other.m[0][2]
        + m[3][2] * other.m[0][3];
    m1 =  m[0][2] * other.m[1][0]
        + m[1][2] * other.m[1][1]
        + m[2][2] * other.m[1][2]
        + m[3][2] * other.m[1][3];
    m2 =  m[0][2] * other.m[2][0]
        + m[1][2] * other.m[2][1]
        + m[2][2] * other.m[2][2]
        + m[3][2] * other.m[2][3];
    m[3][2] = m[0][2] * other.m[3][0]
            + m[1][2] * other.m[3][1]
            + m[2][2] * other.m[3][2]
            + m[3][2] * other.m[3][3];
    m[0][2] = m0;
    m[1][2] = m1;
    m[2][2] = m2;

    m0 =  m[0][3] * other.m[0][0]
        + m[1][3] * other.m[0][1]
        + m[2][3] * other.m[0][2]
        + m[3][3] * other.m[0][3];
    m1 =  m[0][3] * other.m[1][0]
        + m[1][3] * other.m[1][1]
        + m[2][3] * other.m[1][2]
        + m[3][3] * other.m[1][3];
    m2 =  m[0][3] * other.m[2][0]
        + m[1][3] * other.m[2][1]
        + m[2][3] * other.m[2][2]
        + m[3][3] * other.m[2][3];
    m[3][3] = m[0][3] * other.m[3][0]
            + m[1][3] * other.m[3][1]
            + m[2][3] * other.m[3][2]
            + m[3][3] * other.m[3][3];
    m[0][3] = m0;
    m[1][3] = m1;
    m[2][3] = m2;
    return *this;
}

/**
 * @brief
 *
 * @param factor
 * @return Matrix4 &Matrix4::operator
 */
inline Matrix4& Matrix4::operator*=(double factor)
{
    m[0][0] *= factor;
    m[0][1] *= factor;
    m[0][2] *= factor;
    m[0][3] *= factor;
    m[1][0] *= factor;
    m[1][1] *= factor;
    m[1][2] *= factor;
    m[1][3] *= factor;
    m[2][0] *= factor;
    m[2][1] *= factor;
    m[2][2] *= factor;
    m[2][3] *= factor;
    m[3][0] *= factor;
    m[3][1] *= factor;
    m[3][2] *= factor;
    m[3][3] *= factor;
    flagBits = General;
    return *this;
}

/**
 * @brief
 *
 * @param other
 * @return bool Matrix4::operator
 */
inline bool Matrix4::operator==(const Matrix4& other) const
{
    return m[0][0] == other.m[0][0] &&
           m[0][1] == other.m[0][1] &&
           m[0][2] == other.m[0][2] &&
           m[0][3] == other.m[0][3] &&
           m[1][0] == other.m[1][0] &&
           m[1][1] == other.m[1][1] &&
           m[1][2] == other.m[1][2] &&
           m[1][3] == other.m[1][3] &&
           m[2][0] == other.m[2][0] &&
           m[2][1] == other.m[2][1] &&
           m[2][2] == other.m[2][2] &&
           m[2][3] == other.m[2][3] &&
           m[3][0] == other.m[3][0] &&
           m[3][1] == other.m[3][1] &&
           m[3][2] == other.m[3][2] &&
           m[3][3] == other.m[3][3];
}

/**
 * @brief
 *
 * @param other
 * @return bool Matrix4::operator
 */
inline bool Matrix4::operator!=(const Matrix4& other) const
{
    return m[0][0] != other.m[0][0] ||
           m[0][1] != other.m[0][1] ||
           m[0][2] != other.m[0][2] ||
           m[0][3] != other.m[0][3] ||
           m[1][0] != other.m[1][0] ||
           m[1][1] != other.m[1][1] ||
           m[1][2] != other.m[1][2] ||
           m[1][3] != other.m[1][3] ||
           m[2][0] != other.m[2][0] ||
           m[2][1] != other.m[2][1] ||
           m[2][2] != other.m[2][2] ||
           m[2][3] != other.m[2][3] ||
           m[3][0] != other.m[3][0] ||
           m[3][1] != other.m[3][1] ||
           m[3][2] != other.m[3][2] ||
            m[3][3] != other.m[3][3];
}

/**
 * @brief
 *
 * @param m1
 * @param m2
 * @return Matrix4 operator
 */
inline Matrix4 operator+(const Matrix4& m1, const Matrix4& m2)
{
    Matrix4 m(1);
    m.m[0][0] = m1.m[0][0] + m2.m[0][0];
    m.m[0][1] = m1.m[0][1] + m2.m[0][1];
    m.m[0][2] = m1.m[0][2] + m2.m[0][2];
    m.m[0][3] = m1.m[0][3] + m2.m[0][3];
    m.m[1][0] = m1.m[1][0] + m2.m[1][0];
    m.m[1][1] = m1.m[1][1] + m2.m[1][1];
    m.m[1][2] = m1.m[1][2] + m2.m[1][2];
    m.m[1][3] = m1.m[1][3] + m2.m[1][3];
    m.m[2][0] = m1.m[2][0] + m2.m[2][0];
    m.m[2][1] = m1.m[2][1] + m2.m[2][1];
    m.m[2][2] = m1.m[2][2] + m2.m[2][2];
    m.m[2][3] = m1.m[2][3] + m2.m[2][3];
    m.m[3][0] = m1.m[3][0] + m2.m[3][0];
    m.m[3][1] = m1.m[3][1] + m2.m[3][1];
    m.m[3][2] = m1.m[3][2] + m2.m[3][2];
    m.m[3][3] = m1.m[3][3] + m2.m[3][3];
    m.flagBits = Matrix4::General;
    return m;
}

/**
 * @brief
 *
 * @param m1
 * @param m2
 * @return Matrix4 operator
 */
inline Matrix4 operator-(const Matrix4& m1, const Matrix4& m2)
{
    Matrix4 m(1);
    m.m[0][0] = m1.m[0][0] - m2.m[0][0];
    m.m[0][1] = m1.m[0][1] - m2.m[0][1];
    m.m[0][2] = m1.m[0][2] - m2.m[0][2];
    m.m[0][3] = m1.m[0][3] - m2.m[0][3];
    m.m[1][0] = m1.m[1][0] - m2.m[1][0];
    m.m[1][1] = m1.m[1][1] - m2.m[1][1];
    m.m[1][2] = m1.m[1][2] - m2.m[1][2];
    m.m[1][3] = m1.m[1][3] - m2.m[1][3];
    m.m[2][0] = m1.m[2][0] - m2.m[2][0];
    m.m[2][1] = m1.m[2][1] - m2.m[2][1];
    m.m[2][2] = m1.m[2][2] - m2.m[2][2];
    m.m[2][3] = m1.m[2][3] - m2.m[2][3];
    m.m[3][0] = m1.m[3][0] - m2.m[3][0];
    m.m[3][1] = m1.m[3][1] - m2.m[3][1];
    m.m[3][2] = m1.m[3][2] - m2.m[3][2];
    m.m[3][3] = m1.m[3][3] - m2.m[3][3];
    m.flagBits = Matrix4::General;
    return m;
}

/**
 * @brief
 *
 * @param m1
 * @param m2
 * @return Matrix4 operator
 */
inline Matrix4 operator*(const Matrix4& m1, const Matrix4& m2)
{
    if (m1.flagBits == Matrix4::Identity)
        return m2;

    if (m2.flagBits == Matrix4::Identity)
        return m1;

    int flagBits = m1.flagBits | m2.flagBits;
    if (flagBits < Matrix4::Rotation2D) {
        Matrix4 m = m1;
        m.m[3][0] += m.m[0][0] * m2.m[3][0];
        m.m[3][1] += m.m[1][1] * m2.m[3][1];
        m.m[3][2] += m.m[2][2] * m2.m[3][2];

        m.m[0][0] *= m2.m[0][0];
        m.m[1][1] *= m2.m[1][1];
        m.m[2][2] *= m2.m[2][2];
        m.flagBits = flagBits;
        return m;
    }

    Matrix4 m(1);
    m.m[0][0] = m1.m[0][0] * m2.m[0][0]
              + m1.m[1][0] * m2.m[0][1]
              + m1.m[2][0] * m2.m[0][2]
              + m1.m[3][0] * m2.m[0][3];
    m.m[0][1] = m1.m[0][1] * m2.m[0][0]
              + m1.m[1][1] * m2.m[0][1]
              + m1.m[2][1] * m2.m[0][2]
              + m1.m[3][1] * m2.m[0][3];
    m.m[0][2] = m1.m[0][2] * m2.m[0][0]
              + m1.m[1][2] * m2.m[0][1]
              + m1.m[2][2] * m2.m[0][2]
              + m1.m[3][2] * m2.m[0][3];
    m.m[0][3] = m1.m[0][3] * m2.m[0][0]
              + m1.m[1][3] * m2.m[0][1]
              + m1.m[2][3] * m2.m[0][2]
              + m1.m[3][3] * m2.m[0][3];

    m.m[1][0] = m1.m[0][0] * m2.m[1][0]
              + m1.m[1][0] * m2.m[1][1]
              + m1.m[2][0] * m2.m[1][2]
              + m1.m[3][0] * m2.m[1][3];
    m.m[1][1] = m1.m[0][1] * m2.m[1][0]
              + m1.m[1][1] * m2.m[1][1]
              + m1.m[2][1] * m2.m[1][2]
              + m1.m[3][1] * m2.m[1][3];
    m.m[1][2] = m1.m[0][2] * m2.m[1][0]
              + m1.m[1][2] * m2.m[1][1]
              + m1.m[2][2] * m2.m[1][2]
              + m1.m[3][2] * m2.m[1][3];
    m.m[1][3] = m1.m[0][3] * m2.m[1][0]
              + m1.m[1][3] * m2.m[1][1]
              + m1.m[2][3] * m2.m[1][2]
              + m1.m[3][3] * m2.m[1][3];

    m.m[2][0] = m1.m[0][0] * m2.m[2][0]
              + m1.m[1][0] * m2.m[2][1]
              + m1.m[2][0] * m2.m[2][2]
              + m1.m[3][0] * m2.m[2][3];
    m.m[2][1] = m1.m[0][1] * m2.m[2][0]
              + m1.m[1][1] * m2.m[2][1]
              + m1.m[2][1] * m2.m[2][2]
              + m1.m[3][1] * m2.m[2][3];
    m.m[2][2] = m1.m[0][2] * m2.m[2][0]
              + m1.m[1][2] * m2.m[2][1]
              + m1.m[2][2] * m2.m[2][2]
              + m1.m[3][2] * m2.m[2][3];
    m.m[2][3] = m1.m[0][3] * m2.m[2][0]
              + m1.m[1][3] * m2.m[2][1]
              + m1.m[2][3] * m2.m[2][2]
              + m1.m[3][3] * m2.m[2][3];

    m.m[3][0] = m1.m[0][0] * m2.m[3][0]
              + m1.m[1][0] * m2.m[3][1]
              + m1.m[2][0] * m2.m[3][2]
              + m1.m[3][0] * m2.m[3][3];
    m.m[3][1] = m1.m[0][1] * m2.m[3][0]
              + m1.m[1][1] * m2.m[3][1]
              + m1.m[2][1] * m2.m[3][2]
              + m1.m[3][1] * m2.m[3][3];
    m.m[3][2] = m1.m[0][2] * m2.m[3][0]
              + m1.m[1][2] * m2.m[3][1]
              + m1.m[2][2] * m2.m[3][2]
              + m1.m[3][2] * m2.m[3][3];
    m.m[3][3] = m1.m[0][3] * m2.m[3][0]
              + m1.m[1][3] * m2.m[3][1]
              + m1.m[2][3] * m2.m[3][2]
              + m1.m[3][3] * m2.m[3][3];
    m.flagBits = flagBits;
    return m;
}

/**
 * @brief
 *
 * @param vector
 * @param matrix
 * @return Vector3 operator
 */
inline Vector3 operator*(const Vector3& vector, const Matrix4& matrix)
{
    if (matrix.flagBits == Matrix4::Identity)
        return vector;

    double x, y, z, w;
    x = vector.x() * matrix.m[0][0] +
        vector.y() * matrix.m[0][1] +
        vector.z() * matrix.m[0][2] +
        matrix.m[0][3];
    y = vector.x() * matrix.m[1][0] +
        vector.y() * matrix.m[1][1] +
        vector.z() * matrix.m[1][2] +
        matrix.m[1][3];
    z = vector.x() * matrix.m[2][0] +
        vector.y() * matrix.m[2][1] +
        vector.z() * matrix.m[2][2] +
        matrix.m[2][3];
    w = vector.x() * matrix.m[3][0] +
        vector.y() * matrix.m[3][1] +
        vector.z() * matrix.m[3][2] +
        matrix.m[3][3];
    if (w == 1.0)
        return Vector3(x, y, z);
    else
        return Vector3(x / w, y / w, z / w);
}

/**
 * @brief
 *
 * @param matrix
 * @param vector
 * @return Vector3 operator
 */
inline Vector3 operator*(const Matrix4& matrix, const Vector3& vector)
{
    if (matrix.flagBits == Matrix4::Identity)
        return vector;

    double x, y, z, w;
    if (matrix.flagBits == Matrix4::Identity) {
        return vector;
    } else if (matrix.flagBits < Matrix4::Rotation2D) {
        // Translation | Scale
        return Vector3(vector.x() * matrix.m[0][0] + matrix.m[3][0],
                         vector.y() * matrix.m[1][1] + matrix.m[3][1],
                         vector.z() * matrix.m[2][2] + matrix.m[3][2]);
    } else if (matrix.flagBits < Matrix4::Rotation) {
        // Translation | Scale | Rotation2D
        return Vector3(vector.x() * matrix.m[0][0] + vector.y() * matrix.m[1][0] + matrix.m[3][0],
                         vector.x() * matrix.m[0][1] + vector.y() * matrix.m[1][1] + matrix.m[3][1],
                         vector.z() * matrix.m[2][2] + matrix.m[3][2]);
    } else {
        x = vector.x() * matrix.m[0][0] +
            vector.y() * matrix.m[1][0] +
            vector.z() * matrix.m[2][0] +
            matrix.m[3][0];
        y = vector.x() * matrix.m[0][1] +
            vector.y() * matrix.m[1][1] +
            vector.z() * matrix.m[2][1] +
            matrix.m[3][1];
        z = vector.x() * matrix.m[0][2] +
            vector.y() * matrix.m[1][2] +
            vector.z() * matrix.m[2][2] +
            matrix.m[3][2];
        w = vector.x() * matrix.m[0][3] +
            vector.y() * matrix.m[1][3] +
            vector.z() * matrix.m[2][3] +
            matrix.m[3][3];
        if (w == 1.0)
            return Vector3(x, y, z);
        else
            return Vector3(x / w, y / w, z / w);
    }
}

/**
 * @brief
 *
 * @param vector
 * @param matrix
 * @return Vector4 operator
 */
inline Vector4 operator*(const Vector4& vector, const Matrix4& matrix)
{
    if (matrix.flagBits == Matrix4::Identity)
        return vector;

    double x, y, z, w;
    x = vector.x() * matrix.m[0][0] +
        vector.y() * matrix.m[0][1] +
        vector.z() * matrix.m[0][2] +
        vector.w() * matrix.m[0][3];
    y = vector.x() * matrix.m[1][0] +
        vector.y() * matrix.m[1][1] +
        vector.z() * matrix.m[1][2] +
        vector.w() * matrix.m[1][3];
    z = vector.x() * matrix.m[2][0] +
        vector.y() * matrix.m[2][1] +
        vector.z() * matrix.m[2][2] +
        vector.w() * matrix.m[2][3];
    w = vector.x() * matrix.m[3][0] +
        vector.y() * matrix.m[3][1] +
        vector.z() * matrix.m[3][2] +
        vector.w() * matrix.m[3][3];
    return Vector4(x, y, z, w);
}

/**
 * @brief
 *
 * @param matrix
 * @param vector
 * @return Vector4 operator
 */
inline Vector4 operator*(const Matrix4& matrix, const Vector4& vector)
{
    if (matrix.flagBits == Matrix4::Identity)
        return vector;

    double x, y, z, w;
    x = vector.x() * matrix.m[0][0] +
        vector.y() * matrix.m[1][0] +
        vector.z() * matrix.m[2][0] +
        vector.w() * matrix.m[3][0];
    y = vector.x() * matrix.m[0][1] +
        vector.y() * matrix.m[1][1] +
        vector.z() * matrix.m[2][1] +
        vector.w() * matrix.m[3][1];
    z = vector.x() * matrix.m[0][2] +
        vector.y() * matrix.m[1][2] +
        vector.z() * matrix.m[2][2] +
        vector.w() * matrix.m[3][2];
    w = vector.x() * matrix.m[0][3] +
        vector.y() * matrix.m[1][3] +
        vector.z() * matrix.m[2][3] +
        vector.w() * matrix.m[3][3];
    return Vector4(x, y, z, w);
}

/**
 * @brief
 *
 * @param matrix
 * @param plane
 * @return Plane operator
 */
inline Plane operator*(const Matrix4& matrix, const Plane& plane)
{
    if (matrix.flagBits == Matrix4::Identity)
        return plane;

    Vector3 n = matrix.mapVector(plane.normal);
    double d = plane.distance - Vector3::dot(n, matrix.translation());
    return Plane(n, d);
}

/**
 * @brief
 *
 * @param matrix
 * @return Matrix4 operator
 */
inline Matrix4 operator-(const Matrix4& matrix)
{
    Matrix4 m(1);
    m.m[0][0] = -matrix.m[0][0];
    m.m[0][1] = -matrix.m[0][1];
    m.m[0][2] = -matrix.m[0][2];
    m.m[0][3] = -matrix.m[0][3];
    m.m[1][0] = -matrix.m[1][0];
    m.m[1][1] = -matrix.m[1][1];
    m.m[1][2] = -matrix.m[1][2];
    m.m[1][3] = -matrix.m[1][3];
    m.m[2][0] = -matrix.m[2][0];
    m.m[2][1] = -matrix.m[2][1];
    m.m[2][2] = -matrix.m[2][2];
    m.m[2][3] = -matrix.m[2][3];
    m.m[3][0] = -matrix.m[3][0];
    m.m[3][1] = -matrix.m[3][1];
    m.m[3][2] = -matrix.m[3][2];
    m.m[3][3] = -matrix.m[3][3];
    m.flagBits = Matrix4::General;
    return m;
}

/**
 * @brief
 *
 * @param factor
 * @param matrix
 * @return Matrix4 operator
 */
inline Matrix4 operator*(double factor, const Matrix4& matrix)
{
    Matrix4 m(1);
    m.m[0][0] = matrix.m[0][0] * factor;
    m.m[0][1] = matrix.m[0][1] * factor;
    m.m[0][2] = matrix.m[0][2] * factor;
    m.m[0][3] = matrix.m[0][3] * factor;
    m.m[1][0] = matrix.m[1][0] * factor;
    m.m[1][1] = matrix.m[1][1] * factor;
    m.m[1][2] = matrix.m[1][2] * factor;
    m.m[1][3] = matrix.m[1][3] * factor;
    m.m[2][0] = matrix.m[2][0] * factor;
    m.m[2][1] = matrix.m[2][1] * factor;
    m.m[2][2] = matrix.m[2][2] * factor;
    m.m[2][3] = matrix.m[2][3] * factor;
    m.m[3][0] = matrix.m[3][0] * factor;
    m.m[3][1] = matrix.m[3][1] * factor;
    m.m[3][2] = matrix.m[3][2] * factor;
    m.m[3][3] = matrix.m[3][3] * factor;
    m.flagBits = Matrix4::General;
    return m;
}

/**
 * @brief
 *
 * @param matrix
 * @param factor
 * @return Matrix4 operator
 */
inline Matrix4 operator*(const Matrix4& matrix, double factor)
{
    Matrix4 m(1);
    m.m[0][0] = matrix.m[0][0] * factor;
    m.m[0][1] = matrix.m[0][1] * factor;
    m.m[0][2] = matrix.m[0][2] * factor;
    m.m[0][3] = matrix.m[0][3] * factor;
    m.m[1][0] = matrix.m[1][0] * factor;
    m.m[1][1] = matrix.m[1][1] * factor;
    m.m[1][2] = matrix.m[1][2] * factor;
    m.m[1][3] = matrix.m[1][3] * factor;
    m.m[2][0] = matrix.m[2][0] * factor;
    m.m[2][1] = matrix.m[2][1] * factor;
    m.m[2][2] = matrix.m[2][2] * factor;
    m.m[2][3] = matrix.m[2][3] * factor;
    m.m[3][0] = matrix.m[3][0] * factor;
    m.m[3][1] = matrix.m[3][1] * factor;
    m.m[3][2] = matrix.m[3][2] * factor;
    m.m[3][3] = matrix.m[3][3] * factor;
    m.flagBits = Matrix4::General;
    return m;
}

/**
 * @brief
 *
 * @param m1
 * @param m2
 * @return bool
 */
inline bool qFuzzyCompare(const Matrix4& m1, const Matrix4& m2)
{
    return qFuzzyCompare(m1.m[0][0], m2.m[0][0]) &&
           qFuzzyCompare(m1.m[0][1], m2.m[0][1]) &&
           qFuzzyCompare(m1.m[0][2], m2.m[0][2]) &&
           qFuzzyCompare(m1.m[0][3], m2.m[0][3]) &&
           qFuzzyCompare(m1.m[1][0], m2.m[1][0]) &&
           qFuzzyCompare(m1.m[1][1], m2.m[1][1]) &&
           qFuzzyCompare(m1.m[1][2], m2.m[1][2]) &&
           qFuzzyCompare(m1.m[1][3], m2.m[1][3]) &&
           qFuzzyCompare(m1.m[2][0], m2.m[2][0]) &&
           qFuzzyCompare(m1.m[2][1], m2.m[2][1]) &&
           qFuzzyCompare(m1.m[2][2], m2.m[2][2]) &&
           qFuzzyCompare(m1.m[2][3], m2.m[2][3]) &&
           qFuzzyCompare(m1.m[3][0], m2.m[3][0]) &&
           qFuzzyCompare(m1.m[3][1], m2.m[3][1]) &&
           qFuzzyCompare(m1.m[3][2], m2.m[3][2]) &&
           qFuzzyCompare(m1.m[3][3], m2.m[3][3]);
}

/**
 * @brief
 *
 * @param position
 * @param orientation
 * @param scale
 */
inline void Matrix4::compose(const Vector3 &position, const Quaternion &orientation, const Vector3 &scale)
{
    Matrix4 &mm = *this;

    const Matrix3 rot3x3(orientation.toRotationMatrix());

    // set up final matrix with scale, rotation and translation
    mm(0, 0) = scale.x() * rot3x3(0, 0); mm(0, 1) = scale.y() * rot3x3(0, 1); mm(0, 2) = scale.z() * rot3x3(0, 2); mm(0, 3) = position.x();
    mm(1, 0) = scale.x() * rot3x3(1, 0); mm(1, 1) = scale.y() * rot3x3(1, 1); mm(1, 2) = scale.z() * rot3x3(1, 2); mm(1, 3) = position.y();
    mm(2, 0) = scale.x() * rot3x3(2, 0); mm(2, 1) = scale.y() * rot3x3(2, 1); mm(2, 2) = scale.z() * rot3x3(2, 2); mm(2, 3) = position.z();
    // no projection term
    mm(3, 0) = 0.0; mm(3, 1) = 0.0; mm(3, 2) = 0.0; mm(3, 3) = 1.0;

    flagBits = Identity;
    if (!position.isNull()) flagBits |= Translation;
    if (!orientation.isIdentity()) flagBits |= Rotation;
    if (scale != Vector3(1,1,1)) flagBits |= Scale;
}

/**
 * @brief
 *
 * @param position
 * @param orientation
 * @param scale
 */
inline void Matrix4::decompose(Vector3 &position, Quaternion &orientation, Vector3 &scale) const
{
    const Matrix4 &mm = *this;

//    Q_ASSERT(mm.isAffine());

    const Matrix3 m3x3(mm.toMatrix3());

    Matrix3 rot3x3(1);
    if (mm.hasScale()) {
        Matrix3::decomposeMatrix3(m3x3, rot3x3, scale, position);
    } else {
        // we know there is no scaling part; no need for QDU decomposition
        scale = Vector3(1.0, 1.0, 1.0);
        rot3x3 = m3x3;
    }
    orientation = Quaternion::fromRotationMatrix(rot3x3);
    position = Vector3(mm(0, 3), mm(1, 3), mm(2, 3));
}

/**
 * @brief
 *
 * @param point
 * @return Vector3
 */
inline Vector3 Matrix4::map(const Vector3& point) const
{
    return *this * point;
}

/**
 * @brief
 *
 * @param vector
 * @return Vector3
 */
inline Vector3 Matrix4::mapVector(const Vector3& vector) const
{
    if (flagBits < Scale) {
        // Translation
        return vector;
    } else if (flagBits < Rotation2D) {
        // Translation | Scale
        return Vector3(  vector.x() * m[0][0],
                         vector.y() * m[1][1],
                         vector.z() * m[2][2]);
    } else {
        return Vector3(  vector.x() * m[0][0] +
                         vector.y() * m[1][0] +
                         vector.z() * m[2][0],
                         vector.x() * m[0][1] +
                         vector.y() * m[1][1] +
                         vector.z() * m[2][1],
                         vector.x() * m[0][2] +
                         vector.y() * m[1][2] +
                         vector.z() * m[2][2]);
    }
}

/**
 * @brief
 *
 * @param point
 * @return Vector4
 */
inline Vector4 Matrix4::map(const Vector4& point) const
{
    return *this * point;
}

/**
 * @brief
 *
 * @return double
 */
inline double *Matrix4::data()
{
    // We have to assume that the caller will modify the matrix elements,
    // so we flip it over to "General" mode.
    flagBits = General;
    return *m;
}

/**
 * @brief
 *
 * @return Matrix4::operator
 */
inline Matrix4::operator QVariant() const
{
    return QVariant::fromValue<Matrix4>(*this);
}

#ifndef QT_NO_DATASTREAM
/**
 * @brief
 *
 * @param
 * @param
 * @return QDataStream &operator
 */
LICORE_EXPORT QDataStream &operator<<(QDataStream &, const Matrix4 &);
/**
 * @brief
 *
 * @param
 * @param
 * @return QDataStream &operator >>
 */
LICORE_EXPORT QDataStream &operator>>(QDataStream &, Matrix4 &);
#endif

#endif // MATRIX4_H
