#ifndef GEOGRAPHICTILINGSCHEME_H
#define GEOGRAPHICTILINGSCHEME_H

#include "tilingscheme.h"

class LICORE_EXPORT GeographicTilingScheme : public TilingScheme
{
public:
    explicit GeographicTilingScheme(const LiRectangle &rectangle = LiRectangle::MAX_VALUE,
                                    int numberOfLevelZeroTilesX = 2,
                                    int numberOfLevelZeroTilesY = 1,
                                    Ellipsoid *ellipsoid = 0);

    bool isGeographic() const { return true; }

    Ellipsoid *ellipsoid() const { return _ellipsoid; }
    LiRectangle rectangle() const { return _rectangle; }
    MapProjection *projection() const { return _projection; }

    int getNumberOfXTilesAtLevel(int level) const;
    int getNumberOfYTilesAtLevel(int level) const;

    LiRectangle rectangleToNativeRectangle(const LiRectangle &rectangle) const;
    LiRectangle tileXYToNativeRectangle(int x, int y, int level) const;
    LiRectangle tileXYToRectangle(int x, int y, int level) const;
    Cartesian2 positionToTileXY(const Cartographic &position, int level) const;

protected:
    Ellipsoid *_ellipsoid;
    LiRectangle _rectangle;
    MapProjection *_projection;
    int _numberOfLevelZeroTilesX;
    int _numberOfLevelZeroTilesY;
};

#endif // GEOGRAPHICTILINGSCHEME_H
