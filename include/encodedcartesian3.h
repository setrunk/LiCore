#ifndef ENCODEDCARTESIAN3_H
#define ENCODEDCARTESIAN3_H

#include "licore_global.h"
#include "cartesian3.h"
#include "cartesian2.h"

/**
 * @brief
 * EncodedCartesian3把一个双精度浮点的三维坐标拆分成两个单精度浮点的三维坐标，
 * 由于gpu渲染只能使用单精度浮点变量，所以双精度浮点数必须拆分后才能上传gpu进行渲染。
 */
class LICORE_EXPORT EncodedCartesian3
{
public:
    /**
     * @brief
     *
     */
    EncodedCartesian3() {}

    /**
     * @brief
     *
     * @param value
     * @return Cartesian2
     */
    static Cartesian2 encode(double value);
    /**
     * @brief
     *
     * @param cartesian
     * @return EncodedCartesian3
     */
    static EncodedCartesian3 fromCartesian(const Cartesian3 &cartesian);
    /**
     * @brief
     *
     * @param cartesian
     * @param cartesianArray
     * @param index
     */
    static void writeElements(const Cartesian3 &cartesian, float *cartesianArray, int index);

    Cartesian3 high; /**< TODO: describe */
    Cartesian3 low; /**< TODO: describe */
};

#endif // ENCODEDCARTESIAN3_H
