#ifndef LIPROVIDERINTERFACE_H
#define LIPROVIDERINTERFACE_H

#include "liextrasglobal.h"
#include "rectangle.h"
#include "qgscoordinatereferencesystem.h"

class LIEXTRAS_EXPORT LiProviderInterface
{
public:
    virtual ~LiProviderInterface() {}

    virtual bool isTiled() const = 0;
    virtual int tileWidth() const = 0;
    virtual int tileHeight() const = 0;
    virtual int minimumLevel() const = 0;
    virtual int maximumLevel() const = 0;
    virtual int computeLevel(const LiRectangle &rectangle) const = 0;
    virtual QUrl getTileUrl(int x, int y, int level) = 0;
};

#endif // LIPROVIDERINTERFACE_H
