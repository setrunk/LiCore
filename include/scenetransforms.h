#ifndef SCENETRANSFORMS_H
#define SCENETRANSFORMS_H

#include "licore_global.h"
#include "cartesian3.h"
#include "cartesian4.h"
#include "boundingrectangle.h"

class LiScene;
class FrameState;

class LICORE_EXPORT SceneTransforms
{
public:
    static Cartesian2 wgs84ToWindowCoordinates(const Cartesian3 &position, FrameState *frameState);
    static Cartesian2 wgs84WithEyeOffsetToWindowCoordinates(const Cartesian3 &position, const Cartesian3 &eyeOffset, FrameState *frameState);
    static Cartesian2 clipToGLWindowCoordinates(const BoundingRectangle &viewport, const Cartesian4 &position);
    static Cartesian4 worldToClip(const Cartesian3 &position, const Cartesian3 &eyeOffset, FrameState *frameState);
};

#endif // SCENETRANSFORMS_H
