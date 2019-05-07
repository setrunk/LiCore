#ifndef BINARYACCESSOR_H
#define BINARYACCESSOR_H

#include "licore_global.h"
#include "vector4.h"
#include "matrix3.h"
#include "matrix4.h"

/**
 * @brief
 * BinaryAccessor描述如何从一块内存中读取为特定类型的数据，
 * 支持通过文本定义的类型读取，如‘VEC2', 'VEC3', 'MAT4'等。
 */
class LICORE_EXPORT BinaryAccessor
{
public:
    /**
     * @brief
     *
     */
    enum ComponentDatatype
    {
        BYTE            = 0x1400,
        UNSIGNED_BYTE   = 0x1401,
        SHORT           = 0x1402,
        UNSIGNED_SHORT  = 0x1403,
        INT             = 0x1404,
        UNSIGNED_INT    = 0x1405,
        FLOAT           = 0x1406,
        DOUBLE          = 0x140A
    };

    /**
     * @brief
     *
     */
    enum Accessor
    {
        SCALAR,
        VEC2,
        VEC3,
        VEC4,
        MAT2,
        MAT3,
        MAT4
    };

    BinaryAccessor();

    /**
     * @brief
     *
     * @param binary
     * @param byteOffset
     * @param accessor
     * @param componentDataType
     */
    BinaryAccessor(const QByteArray &binary, int byteOffset, int accessor, int componentDataType);

    /**
     * @brief
     *
     * @param binary
     * @param json
     */
    BinaryAccessor(const QByteArray &binary, const QJsonObject &json);

    /**
     * @brief
     *
     * @param index
     * @return QVariant
     */
    QVariant getValue(int index) const;

    /**
     * @brief
     *
     * @param count
     * @return QVector<T>
     */
    template<typename T>
    QVector<T> createArrayBufferView(int count) const;

    /**
     * @brief
     *
     * @param name
     * @return int
     */
    static int accessorTypeFromName(const QString &name);
    /**
     * @brief
     *
     * @param name
     * @return int
     */
    static int componentDataTypeFromName(const QString &name);
    /**
     * @brief
     *
     * @param accessor
     * @return int
     */
    static int componentCountFromAccessor(int accessor);
    /**
     * @brief
     *
     * @param componentDataType
     * @return int
     */
    static int sizeInBytes(int componentDataType);

private:
    int m_accessor; /**< TODO: describe */
    int m_componentDataType; /**< TODO: describe */
    QByteArray m_binary; /**< TODO: describe */
    int m_byteOffset; /**< TODO: describe */
};

template<typename T>
QVector<T> BinaryAccessor::createArrayBufferView(int count) const
{
    QVector<T> result(count);
    int size = sizeof(T)*count;
    int copyCount = std::min(m_binary.size() - m_byteOffset, size);
    if (copyCount > 0) {
        memcpy(result.data(), m_binary.constData()+m_byteOffset, copyCount);
    }
    return result;
}

/**
 * @brief
 *
 */
typedef QSharedPointer<BinaryAccessor> BinaryAccessorPtr;
typedef QHash<QString, BinaryAccessor> BinaryAccessorHash;

#endif // BINARYACCESSOR_H
