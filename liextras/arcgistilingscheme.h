#ifndef ARCGISTILINGSCHEME_H
#define ARCGISTILINGSCHEME_H

#include "liextrasglobal.h"
#include "tilingscheme.h"
#include <qgsrectangle.h>
#include <qgscoordinatereferencesystem.h>
#include <qgscoordinatetransform.h>

class LIEXTRAS_EXPORT ArcgisTilingScheme : public TilingScheme
{
public:
    explicit ArcgisTilingScheme(const QVariantMap &serviceInfo);

    virtual bool isGeographic() const { return true; }

    virtual Ellipsoid *ellipsoid() const { return _ellipsoid; }
    virtual LiRectangle rectangle() const { return _rectangle; }
    virtual MapProjection *projection() const { return _projection; }

    virtual int getNumberOfXTilesAtLevel(int level) const;
    virtual int getNumberOfYTilesAtLevel(int level) const;

    virtual LiRectangle rectangleToNativeRectangle(const LiRectangle &rectangle) const;
    virtual LiRectangle tileXYToNativeRectangle(int x, int y, int level) const;
    virtual LiRectangle tileXYToRectangle(int x, int y, int level) const;
    virtual Cartesian2 positionToTileXY(const Cartographic &position, int level) const;

    static QgsCoordinateReferenceSystem parseSpatialReference( const QVariantMap& spatialReferenceMap );

    int tileWidth() const { return _tileWidth; }
    int tileHeight() const { return _tileHeight; }
    int maximumLevel() const { return _lodEntries.size() - 1; }
    QgsRectangle fullExtent() const { return _fullExtent; }
    double resolution(int level) const { return _lodEntries[level].resolution; }

private:
    struct LodEntry
    {
        int level;
        double resolution;
        double scale;
        int tileStartX;
        int tileEndX;
        int tileStartY;
        int tileEndY;
        double tileWidth;
        double tileHeight;
        LiRectangle rectangle;
    };

    QgsRectangle _fullExtent;
    QgsCoordinateReferenceSystem mCrs;
    Cartesian2 _origin;
    int _tileWidth;
    int _tileHeight;
    QVector<LodEntry> _lodEntries;

    Ellipsoid *_ellipsoid;
    LiRectangle _rectangle;
    MapProjection *_projection;
};

#endif // ARCGISTILINGSCHEME_H
