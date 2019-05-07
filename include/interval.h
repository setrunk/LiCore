#ifndef SEGMENT_H
#define SEGMENT_H

#include "licore_global.h"

/**
 * @brief
 * Interval定义了一段间隔，由起始点和结束点组成。
 */
class LICORE_EXPORT Interval
{
public:
    /**
     * @brief
     *
     */
    Interval()
        : start(0)
        , stop(0)
    {
    }

    /**
     * @brief
     *
     * @param _start
     * @param _stop
     */
    Interval(double _start, double _stop)
        : start(_start)
        , stop(_stop)
    {
    }

    /**
     * @brief
     *
     * @param other
     * @return bool
     */
    bool intersects(const Interval &other) const
    {
        if (start > other.stop) return false;
        if (stop < other.start) return false;
        return true;
    }

    double start; /**< TODO: describe */
    double stop; /**< TODO: describe */
};

#endif // SEGMENT_H
