#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "licore_global.h"

/**
 * @brief
 * 提供获取时间戳的函数。
 */
class LICORE_EXPORT Timestamp
{
public:
    Timestamp();

    /**
     * @brief
    * 返回当前时间戳，单位为毫秒（1秒=1000毫秒）
     * @return quint64
     */
    static quint64 getTimestamp();

    /**
     * @brief
    * 返回当前时间戳，单位为纳秒（1秒=1000,000,000纳秒）
     * @return quint64
     */
    static quint64 getNanoseconds();

    static QElapsedTimer *elapsedTimer; /**< TODO: describe */
};

LICORE_EXPORT quint64 getTimestamp();
LICORE_EXPORT quint64 getNanoseconds();

#endif // TIMESTAMP_H
