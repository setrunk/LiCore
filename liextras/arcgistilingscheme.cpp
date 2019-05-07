#include "arcgistilingscheme.h"
#include "geographicprojection.h"
#include "transformhelper.h"
#include "ellipsoid.h"

ArcgisTilingScheme::ArcgisTilingScheme(const QVariantMap &serviceInfo)
    : _ellipsoid(Ellipsoid::WGS84())
    , _projection(new GeographicProjection(_ellipsoid))
{
    QVariantMap extentData = serviceInfo["fullExtent"].toMap();
    _fullExtent.setXMinimum( extentData["xmin"].toDouble() );
    _fullExtent.setYMinimum( extentData["ymin"].toDouble() );
    _fullExtent.setXMaximum( extentData["xmax"].toDouble() );
    _fullExtent.setYMaximum( extentData["ymax"].toDouble() );
    mCrs = parseSpatialReference( extentData["spatialReference"].toMap() );
    if ( !mCrs.isValid() )
    {
        qDebug() << "Could not parse spatial reference";
        return;
    }

    _rectangle = TransformHelper::instance()->transform(_fullExtent, &mCrs);

    QVariantMap tileInfo = serviceInfo["tileInfo"].toMap();
    _tileWidth = tileInfo["cols"].toInt();
    _tileHeight = tileInfo["rows"].toInt();

    QVariantMap origin = tileInfo["origin"].toMap();
    _origin.x = origin["x"].toDouble();
    _origin.y = origin["y"].toDouble();

    const QList<QVariant> lodEntries = tileInfo["lods"].toList();
    for (const QVariant &lod : lodEntries)
    {
        QVariantMap lodMap = lod.toMap();

        LodEntry entry;
        entry.level = lodMap["level"].toInt();
        entry.scale = lodMap["scale"].toDouble();

        double resolution = lodMap["resolution"].toDouble();
        double tileWidth = _tileWidth * resolution;
        double tileHeight = _tileHeight * resolution;

        double ox = _origin.x;
        double oy = _origin.y;
        entry.tileStartX = qFloor(( _fullExtent.xMinimum() - ox ) / tileWidth );
        entry.tileStartY = qFloor(( oy - _fullExtent.yMaximum() ) / tileHeight );
        entry.tileEndX = qCeil(( _fullExtent.xMaximum() - ox ) / tileWidth );
        entry.tileEndY = qCeil(( oy - _fullExtent.yMinimum() ) / tileHeight );

        int tilesX = entry.tileEndX - entry.tileStartX;
        int tilesY = entry.tileEndY - entry.tileStartY;

        double xmin = ox + tileWidth * entry.tileStartX;
        double xmax = ox + tileWidth * entry.tileEndX;
        double ymin = oy - tileHeight * entry.tileStartY;
        double ymax = oy - tileHeight * entry.tileEndY;
        LiRectangle rect = TransformHelper::instance()->transform(QgsRectangle(xmin, ymin, xmax, ymax), &mCrs);

        entry.tileWidth = rect.width() / tilesX;
        entry.tileHeight = rect.height() / tilesY;
        entry.resolution = entry.tileWidth / _tileWidth;
        entry.rectangle = rect;

        _lodEntries.append(entry);
    }
}

QgsCoordinateReferenceSystem ArcgisTilingScheme::parseSpatialReference(const QVariantMap &spatialReferenceMap)
{
    QString spatialReference = spatialReferenceMap["latestWkid"].toString();
    if ( spatialReference.isEmpty() )
        spatialReference = spatialReferenceMap["wkid"].toString();
    if ( spatialReference.isEmpty() )
        spatialReference = spatialReferenceMap["wkt"].toString();
    else
        spatialReference = QString( "EPSG:%1" ).arg( spatialReference );
    QgsCoordinateReferenceSystem crs;
    crs.createFromString( spatialReference );
    if ( crs.authid().startsWith( "USER:" ) )
        crs.createFromString( "EPSG:4326" ); // If we can't recognize the SRS, fall back to WGS84
    return crs;
}

int ArcgisTilingScheme::getNumberOfXTilesAtLevel(int level) const
{
    if (level >= _lodEntries.size())
        return 0;

    const LodEntry &lod = _lodEntries.at(level);
    return lod.tileEndX - lod.tileStartX;
}

int ArcgisTilingScheme::getNumberOfYTilesAtLevel(int level) const
{
    if (level >= _lodEntries.size())
        return 0;

    const LodEntry &lod = _lodEntries.at(level);
    return lod.tileEndY - lod.tileStartY;
}

LiRectangle ArcgisTilingScheme::rectangleToNativeRectangle(const LiRectangle &rectangle) const
{
    double west = Math::toDegrees(rectangle.west);
    double south = Math::toDegrees(rectangle.south);
    double east = Math::toDegrees(rectangle.east);
    double north = Math::toDegrees(rectangle.north);

    LiRectangle result;
    result.west = west;
    result.south = south;
    result.east = east;
    result.north = north;
    return result;
}

LiRectangle ArcgisTilingScheme::tileXYToNativeRectangle(int x, int y, int level) const
{
    LiRectangle rectangleRadians = tileXYToRectangle(x, y, level);
    rectangleRadians.west = Math::toDegrees(rectangleRadians.west);
    rectangleRadians.south = Math::toDegrees(rectangleRadians.south);
    rectangleRadians.east = Math::toDegrees(rectangleRadians.east);
    rectangleRadians.north = Math::toDegrees(rectangleRadians.north);
    return rectangleRadians;
}

LiRectangle ArcgisTilingScheme::tileXYToRectangle(int x, int y, int level) const
{
    if (level >= _lodEntries.size())
        return LiRectangle();

    const LodEntry &lod = _lodEntries.at(level);
    if (x < lod.tileStartX || x >= lod.tileEndX || y < lod.tileStartY || y >= lod.tileEndY)
        return LiRectangle();

    double west = lod.rectangle.west + lod.tileWidth * (x - lod.tileStartX);
    double north = lod.rectangle.north - lod.tileHeight * (y - lod.tileStartY);
    double east = west + lod.tileWidth;
    double south = north - lod.tileHeight;
    return LiRectangle(west, south, east, north);
}

Cartesian2 ArcgisTilingScheme::positionToTileXY(const Cartographic &position, int level) const
{
    if (level >= _lodEntries.size()) {
        // outside the bounds of the tiling scheme
        return Cartesian2();
    }

    const LodEntry &lod = _lodEntries.at(level);

    int xTiles = lod.tileEndX - lod.tileStartX;
    int yTiles = lod.tileEndY - lod.tileStartY;

    double xTileWidth = lod.tileWidth;
    double yTileHeight = lod.tileHeight;

    double longitude = position.longitude;
    if (_rectangle.east < _rectangle.west) {
        longitude += Math::TWO_PI;
    }

    double ox = lod.rectangle.west;
    double oy = lod.rectangle.north;

    int xTileCoordinate = (longitude - ox) / xTileWidth;
    xTileCoordinate = Math::clamp(xTileCoordinate, 0, xTiles-1);
//    if (xTileCoordinate >= xTiles) {
//        xTileCoordinate = xTiles - 1;
//    }

    int yTileCoordinate = (oy - position.latitude) / yTileHeight;
    yTileCoordinate = Math::clamp(yTileCoordinate, 0, yTiles-1);
//    if (yTileCoordinate >= yTiles) {
//        yTileCoordinate = yTiles - 1;
//    }

    Cartesian2 result;
    result.x = xTileCoordinate + lod.tileStartX;
    result.y = yTileCoordinate + lod.tileStartY;
    return result;
}
