#ifndef LIUTILS_H
#define LIUTILS_H

#include "licore_global.h"
#include "cartesian3.h"
#include "cartographic.h"
#include "vector3.h"
#include "matrix4.h"
#include <QJSValue>

#define DEFERRED_SHADING 1

inline bool isValid(const QJSValue &value)
{
    return !value.isError() && !value.isNull() && !value.isUndefined();
}

inline bool operator ==(const QJSValue &left, const QJSValue &right)
{
    return left.equals(right);
}

inline QUrl resolvedShaderUrl(const QString &fileName)
{
#if DEFERRED_SHADING
    QDir dir(QCoreApplication::applicationDirPath() + QStringLiteral("/Assets/Shaders/Deferred"));
#else
    QDir dir(QCoreApplication::applicationDirPath() + QStringLiteral("/Assets/Shaders/GL"));
#endif
    return QUrl::fromLocalFile(dir.absoluteFilePath(fileName));
}

inline QUrl resolvedTextureUrl(const QString &fileName)
{
    QDir dir(QCoreApplication::applicationDirPath() + QStringLiteral("/Assets/Textures"));
    return QUrl::fromLocalFile(dir.absoluteFilePath(fileName));
}

inline QUrl resolvedScriptUrl(const QString &fileName)
{
    QDir dir(QCoreApplication::applicationDirPath() + QStringLiteral("/Assets/Scripts"));
    return QUrl::fromLocalFile(dir.absoluteFilePath(fileName));
}

//inline QUrl resolvedUrl(const QString &path)
//{
//    if (path.startsWith(QLatin1String("http"), Qt::CaseInsensitive))
//        return QUrl(path);

//    QFileInfo fi(path);
//    if (fi.isRelative())
//    {
//        QDir dir(QCoreApplication::applicationDirPath());
//        return QUrl::fromLocalFile(dir.absoluteFilePath(path));
//    }

//    return QUrl::fromLocalFile(path);
//}

inline QUrl resolvedUrl(const QString &path, const QUrl &baseUrl = QUrl())
{
    if (path.startsWith(QLatin1String("http"), Qt::CaseInsensitive))
        return QUrl(path);

    if (!baseUrl.isValid() || baseUrl.isLocalFile())
    {
        QFileInfo fi(path);
        if (fi.isAbsolute())
        {
            return QUrl::fromLocalFile(path);
        }
        else
        {
            QDir dir(baseUrl.isValid() ? baseUrl.toLocalFile() : QCoreApplication::applicationDirPath());
            return QUrl::fromLocalFile(dir.absoluteFilePath(path));
        }
    }
    else
    {
        return baseUrl.resolved(path);
    }
}

inline QUrl resolvedQueryUrl(const QUrl &baseUrl, const QUrl &url)
{
    QUrlQuery q(baseUrl);
    QUrl result = baseUrl.resolved(url);
    result.setQuery(q);
    return result;
}

inline QUrl getBaseUrl(const QUrl &url)
{
    static QUrl a = QUrl("./");
    return resolvedQueryUrl(url, a);
}

inline QString urlToLocalFileOrQrc(const QUrl &url)
{
    if (!url.toString().startsWith(QLatin1String("http"), Qt::CaseInsensitive))
    {
        const QString scheme(url.scheme().toLower());
        if (scheme == QLatin1String("qrc")) {
            if (url.authority().isEmpty())
                return QLatin1Char(':') + url.path();
            return QString();
        }
        return url.toLocalFile();
    }

    return url.toString();
}

inline int nextPowerOfTwo(int n)
{
    // From http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    ++n;

    return n;
}

inline uint AlignToPowerOf2(uint Value, uint Alignment = 16)
{
    Q_ASSERT((Alignment & (Alignment - 1)) == 0);
    // to align to 2^N, add 2^N - 1 and AND with all but lowest N bits set
    return (Value + Alignment - 1) & (~(Alignment - 1));
}

inline GLuint byteSizeFromType(GLint type)
{
    switch (type) {
    case GL_FLOAT:          return sizeof(float);
#ifndef QT_OPENGL_ES_2 // Otherwise compile error as Qt defines GL_DOUBLE as GL_FLOAT when using ES2
    case GL_DOUBLE:         return sizeof(double);
#endif
    case GL_BYTE:           return sizeof(char);
    case GL_UNSIGNED_BYTE:  return sizeof(unsigned char);
    case GL_SHORT:          return sizeof(short);
    case GL_UNSIGNED_SHORT: return sizeof(unsigned short);
    case GL_INT:            return sizeof(GLint);
    case GL_UNSIGNED_INT:   return sizeof(GLuint);

    case GL_FLOAT_VEC2:     return sizeof(float) * 2;
    case GL_FLOAT_VEC3:     return sizeof(float) * 3;
    case GL_FLOAT_VEC4:     return sizeof(float) * 4;
#ifdef GL_DOUBLE_VEC3 // Required to compile on pre GL 4.1 systems
    case GL_DOUBLE_VEC2:    return sizeof(double) * 2;
    case GL_DOUBLE_VEC3:    return sizeof(double) * 3;
    case GL_DOUBLE_VEC4:    return sizeof(double) * 4;
#endif
    default:
        qWarning() << Q_FUNC_INFO << "unsupported:" << QString::number(type, 16);
    }

    return 0;
}

inline Matrix4 modifiedModelViewMatrix(const Matrix4 &modelMatrix, const Matrix4 &viewMatrix)
{
    Vector3 centerEye = viewMatrix * modelMatrix.translation();
    Matrix4 model = modelMatrix;
    model.setTranslation(Vector3(0, 0, 0));
    Matrix4 view = viewMatrix;
    view.setTranslation(centerEye);
    return view * model;
}

inline quint8 getUint8(const QByteArray &buffer, int pos)
{
    return *(quint8*)(buffer.data() + pos);
}

inline quint16 getUint16(const QByteArray &buffer, int pos)
{
    return *(quint16*)(buffer.data() + pos);
}

inline uint getUint32(const QByteArray &buffer, int pos)
{
    return *(uint*)(buffer.data() + pos);
}

inline float getFloat32(const QByteArray &buffer, int pos)
{
    return *(float*)(buffer.data() + pos);
}

inline double getFloat64(const QByteArray &buffer, int pos)
{
    return *(double*)(buffer.data() + pos);
}

inline Vector2 jsonArrToVec2(const QJsonArray &array)
{
    return Vector2(array[0].toDouble(), array[1].toDouble());
}

inline Vector3 jsonArrToVec3(const QJsonArray &array)
{
    return Vector3(array[0].toDouble(), array[1].toDouble(), array[2].toDouble());
}

inline Vector4 jsonArrToVec4(const QJsonArray &array)
{
    return Vector4(array[0].toDouble(), array[1].toDouble(), array[2].toDouble(), array[3].toDouble());
}

inline Matrix4 jsonArrToMatrix4(const QJsonArray &array)
{
    Matrix4 m;
    if (array.size() == 16)
    {
        double *p = m.data();
        for (int i = 0; i < 16; ++i)
            p[i] = array[i].toDouble();
    }
    return m;
}

inline int floatToByte(float f)
{
    return f == 1.0f ? 255 : f * 256;
}

inline float byteToFloat(int n)
{
    return n / 255.0f;
}

inline QColor vec4ToColor(const Vector4 &v)
{
    return QColor::fromRgbF(v.x(), v.y(), v.z(), v.w());
}

inline Vector4 colorToVec4(const QColor &c)
{
    return Vector4(c.redF(), c.greenF(), c.blueF(), c.alphaF());
}

inline QColor vec3ToColor(const Vector3 &v)
{
    return QColor::fromRgbF(v.x(), v.y(), v.z());
}

inline Vector3 colorToVec3(const QColor &c)
{
    return Vector3(c.redF(), c.greenF(), c.blueF());
}

inline QJsonArray matrix4ToJsonArr(const Matrix4 &m)
{
    QJsonArray json;
    for (int i = 0; i < 16; ++i)
        json.append(m[i]);
    return json;
}

inline int zigZagDecode(int value)
{
    return (value >> 1) ^ (-(value & 1));
}

LICORE_EXPORT QByteArray createRegularGridIndices(int width, int height);
LICORE_EXPORT QByteArray createWireGridIndices(int width, int height);

LICORE_EXPORT double metersToRadians(double meters);
LICORE_EXPORT double metersToDegrees(double meters);
LICORE_EXPORT QVector<double> toNumberList(const QJSValue &value);
LICORE_EXPORT QJSValue fromNumberList(const QVector<double> &values);

LICORE_EXPORT Vector4 packFloat(double value);
LICORE_EXPORT double unpackFloat(const Vector4 &value);

LICORE_EXPORT Cartesian3 cartographicToCartesian(const Cartographic &cartographic);
LICORE_EXPORT Cartographic cartesianToCartographic(const Cartesian3 &cartesian);
LICORE_EXPORT Matrix4 eastNorthUpToFixedFrame(const Cartesian3 &cartesian);
LICORE_EXPORT Matrix4 eastNorthUpToFixedFrame(const Cartographic &cartographic);

#endif // LIUTILS_H
