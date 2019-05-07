#ifndef LICOMMON_H
#define LICOMMON_H

struct SceneMode
{
    enum
    {
        Morphing = 0,
        ColumbusView,
        Scene2D,
        Scene3D,
    };
};

struct GraphicsLimit
{
    static int maximumTextureUnits;
};

#endif // LICOMMON_H
