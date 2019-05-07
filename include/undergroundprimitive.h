#ifndef UNDERGROUNDPRIMITIVE_H
#define UNDERGROUNDPRIMITIVE_H

#include "ligeometryrenderer.h"

class UndergroundPrimitivePrivate;

/**
 * @brief
 * 地下网格平面，是一个无限大的网格，会随着摄像机的位置自动延申。
 */
class LICORE_EXPORT UndergroundPrimitive : public LiGeometryRenderer
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(UndergroundPrimitive)

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit UndergroundPrimitive(LiNode *parent = nullptr);
};

#endif // UNDERGROUNDPRIMITIVE_H
