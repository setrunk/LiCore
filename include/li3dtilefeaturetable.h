#ifndef LI3DTILEFEATURETABLE_H
#define LI3DTILEFEATURETABLE_H

#include "licore_global.h"
#include "vector4.h"

class LICORE_EXPORT Li3DTileFeatureTable
{
public:
    enum DataType
    {
        BYTE,
        UNSIGNED_BYTE,
        SHORT,
        UNSIGNED_SHORT,
        INT,
        UNSIGNED_INT,
        FLOAT,
        DOUBLE
    };

    Li3DTileFeatureTable(const QJsonObject &json, const QByteArray &arrayBuffer);

    int featuresLength() const { return _featuresLength; }

    QVariant getProperty(const QString &semantic, int featureId, DataType componentType = UNSIGNED_BYTE, int componentLength = 1);
    QVariant getGlobalProperty(const QString &semantic, DataType componentType = UNSIGNED_BYTE, int componentLength = 1);
    QVariantList getPropertyArray(const QString &semantic, DataType componentType = UNSIGNED_BYTE, int componentLength = 1);

private:
    QVariantList getTypedArrayFromBinary(const QString &semantic, DataType componentType, int componentLength, int count, int byteOffset);

    QJsonObject _json;
    QByteArray _buffer;
    int _featuresLength = 0;
    QHash<QString, QVariantList> _cachedTypedArrays;
};

#endif // LI3DTILEFEATURETABLE_H
