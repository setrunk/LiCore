#ifndef WEBMERCATORTILINGSCHEME_H
#define WEBMERCATORTILINGSCHEME_H

#include "licore_global.h"
#include "tilingscheme.h"
#include "rectangle.h"
#include "cartesian2.h"
#include "cartesian3.h"

class Ellipsoid;
class MapProjection;
class WebMercatorProjection;

class LICORE_EXPORT WebMercatorTilingScheme : public TilingScheme
{
public:
    WebMercatorTilingScheme();
    WebMercatorTilingScheme(int numX, int numY, Ellipsoid *ellipsoid = 0);

    bool isGeographic() const { return false; }

    int getNumberOfXTilesAtLevel(int level) const;
    int getNumberOfYTilesAtLevel(int level) const;

    Ellipsoid *ellipsoid() const { return _ellipsoid; }
    LiRectangle rectangle() const { return _rectangle; }
    MapProjection *projection() const { return (MapProjection *)_projection; }

    LiRectangle tileXYToRectangle(int x, int y, int level) const;
    LiRectangle tileXYToNativeRectangle(int x, int y, int level) const;
    LiRectangle rectangleToNativeRectangle(const LiRectangle &rectangle) const;
    Cartesian2 positionToTileXY(const Cartographic &position, int level) const;

private:
    Ellipsoid *_ellipsoid;
    int _numberOfLevelZeroTilesX;
    int _numberOfLevelZeroTilesY;
    WebMercatorProjection *_projection;
    Cartesian2 _rectangleSouthwestInMeters;
    Cartesian2 _rectangleNortheastInMeters;
    LiRectangle _rectangle;
};

#endif // WEBMERCATORTILINGSCHEME_H
