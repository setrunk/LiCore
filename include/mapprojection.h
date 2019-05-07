#ifndef MAPPROJECTION_H
#define MAPPROJECTION_H

#include "licore_global.h"
#include "cartesian3.h"
#include "cartographic.h"

/**
 * @brief
 * 提供制图坐标点（Cartographic）和三维坐标点（Cartesian3）的投影变换。
 */
class LICORE_EXPORT MapProjection
{
public:
    virtual ~MapProjection() {}

    /**
     * @brief
     *
     * @param cartographic
     * @return Cartesian3
     */
    virtual Cartesian3 project(const Cartographic &cartographic) const = 0;
    /**
     * @brief
     *
     * @param cartesian
     * @return Cartographic
     */
    virtual Cartographic unproject(const Cartesian3 &cartesian) const = 0;
};

#endif // MAPPROJECTION_H
