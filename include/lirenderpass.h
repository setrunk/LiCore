#ifndef LIRENDERPASS_H
#define LIRENDERPASS_H

#include "licore_global.h"

class LiRenderPass
{
public:
    enum PassState
    {
        Shadow,
        Color,
        Pick
    };

    LiRenderPass();
};

#endif // LIRENDERPASS_H
