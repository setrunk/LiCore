#ifndef LI3DTILEFEATURETABLE_H
#define LI3DTILEFEATURETABLE_H

#include "licore_global.h"

class LICORE_EXPORT Li3DTileFeatureTable
{
public:
    Li3DTileFeatureTable(const QJsonObject &json, const QByteArray &arrayBuffer);

private:
    QJsonObject _json;
    QByteArray _buffer;
};

#endif // LI3DTILEFEATURETABLE_H
