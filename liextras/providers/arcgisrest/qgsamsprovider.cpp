/***************************************************************************
    qgsamsprovider.cpp - ArcGIS MapServer Raster Provider
     ----------------------------------------------------
    Date                 : Nov 24, 2015
    Copyright            : (C) 2015 by Sandro Mani
    email                : manisandro@gmail.com

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsamsprovider.h"
#include "qgsarcgisrestutils.h"
#include "qgsdatasourceuri.h"
#include "qgslogger.h"
#include "qgsrasteridentifyresult.h"
#include "qgsfeaturestore.h"
#include "qgsgeometry.h"

#include <cstring>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPainter>
#include <QUrlQuery>

QgsAmsLegendFetcher::QgsAmsLegendFetcher( QgsAmsProvider *provider )
    : QgsImageFetcher( provider ), mProvider( provider )
{
    mQuery = new QgsArcGisAsyncQuery( this );
    connect( mQuery, &QgsArcGisAsyncQuery::finished, this, &QgsAmsLegendFetcher::handleFinished );
    connect( mQuery, &QgsArcGisAsyncQuery::failed, this, &QgsAmsLegendFetcher::handleError );
}

void QgsAmsLegendFetcher::start()
{
    // http://resources.arcgis.com/en/help/rest/apiref/mslegend.html
    // http://sampleserver5.arcgisonline.com/arcgis/rest/services/CommunityAddressing/MapServer/legend?f=pjson
    QgsDataSourceUri dataSource( mProvider->dataSourceUri() );
    QUrl queryUrl( dataSource.param( QStringLiteral( "url" ) ) + "/legend" );
    QUrlQuery query;
    query.addQueryItem( QStringLiteral( "f" ), QStringLiteral( "json" ) );
    queryUrl.setQuery(query);
    mQuery->start( queryUrl, &mQueryReply );
}

void QgsAmsLegendFetcher::handleError( const QString &errorTitle, const QString &errorMsg )
{
    emit error( errorTitle + ": " + errorMsg );
}

void QgsAmsLegendFetcher::handleFinished()
{
    // Parse result
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson( mQueryReply, &err );
    if ( doc.isNull() )
    {
        emit error( QStringLiteral( "Parsing error:" ).arg( err.errorString() ) );
    }
    QVariantMap queryResults = doc.object().toVariantMap();
    QgsDataSourceUri dataSource( mProvider->dataSourceUri() );
    QVector< QPair<QString, QImage> > legendEntries;
    for ( const QVariant &result : queryResults["layers"].toList() )
    {
        QVariantMap queryResultMap = result.toMap();
        QString layerId = queryResultMap[QStringLiteral( "layerId" )].toString();
        if ( layerId != dataSource.param( QStringLiteral( "layer" ) ) && !mProvider->subLayers().contains( layerId ) )
        {
            continue;
        }
        QVariantList legendSymbols = queryResultMap[QStringLiteral( "legend" )].toList();
        for ( const QVariant &legendEntry : legendSymbols )
        {
            QVariantMap legendEntryMap = legendEntry.toMap();
            QString label = legendEntryMap[QStringLiteral( "label" )].toString();
            if ( label.isEmpty() && legendSymbols.size() == 1 )
                label = queryResultMap[QStringLiteral( "layerName" )].toString();
            QByteArray imageData = QByteArray::fromBase64( legendEntryMap[QStringLiteral( "imageData" )].toByteArray() );
            legendEntries.append( qMakePair( label, QImage::fromData( imageData ) ) );
        }
    }
    if ( !legendEntries.isEmpty() )
    {
        int padding = 5;
        int vpadding = 1;
        int imageSize = 20;
        int textWidth = 175;

        typedef QPair<QString, QImage> LegendEntry_t;
        QSize maxImageSize( 0, 0 );
        for ( const LegendEntry_t &legendEntry : legendEntries )
        {
            maxImageSize.setWidth( std::max( maxImageSize.width(), legendEntry.second.width() ) );
            maxImageSize.setHeight( std::max( maxImageSize.height(), legendEntry.second.height() ) );
        }
        double scaleFactor = maxImageSize.width() == 0 || maxImageSize.height() == 0 ? 1.0 :
                                                                                       std::min( 1., std::min( double( imageSize ) / maxImageSize.width(), double( imageSize ) / maxImageSize.height() ) );

        mLegendImage = QImage( imageSize + padding + textWidth, vpadding + legendEntries.size() * ( imageSize + vpadding ), QImage::Format_ARGB32 );
        mLegendImage.fill( Qt::transparent );
        QPainter painter( &mLegendImage );
        int i = 0;
        for ( const LegendEntry_t &legendEntry : legendEntries )
        {
            QImage symbol = legendEntry.second.scaled( legendEntry.second.width() * scaleFactor, legendEntry.second.height() * scaleFactor, Qt::KeepAspectRatio, Qt::SmoothTransformation );
            painter.drawImage( 0, vpadding + i * ( imageSize + vpadding ) + ( imageSize - symbol.height() ), symbol );
            painter.drawText( imageSize + padding, vpadding + i * ( imageSize + vpadding ), textWidth, imageSize, Qt::AlignLeft | Qt::AlignVCenter, legendEntry.first );
            ++i;
        }
    }
    emit finish( mLegendImage );
}

///////////////////////////////////////////////////////////////////////////////

QgsAmsProvider::QgsAmsProvider( const QString &uri, const ProviderOptions &options )
    : QgsRasterDataProvider( uri, options )
{
    mLegendFetcher = new QgsAmsLegendFetcher( this );

    QgsDataSourceUri dataSource( dataSourceUri() );
    mServiceInfo = QgsArcGisRestUtils::getServiceInfo( dataSource.param( QStringLiteral( "url" ) ), mErrorTitle, mError );
    mLayerInfo = QgsArcGisRestUtils::getLayerInfo( dataSource.param( QStringLiteral( "url" ) ) + "/" + dataSource.param( QStringLiteral( "layer" ) ), mErrorTitle, mError );

    QVariantMap extentData = mLayerInfo[QStringLiteral( "extent" )].toMap();
    mExtent.setXMinimum( extentData[QStringLiteral( "xmin" )].toDouble() );
    mExtent.setYMinimum( extentData[QStringLiteral( "ymin" )].toDouble() );
    mExtent.setXMaximum( extentData[QStringLiteral( "xmax" )].toDouble() );
    mExtent.setYMaximum( extentData[QStringLiteral( "ymax" )].toDouble() );
    mCrs = QgsArcGisRestUtils::parseSpatialReference( extentData[QStringLiteral( "spatialReference" )].toMap() );
    if ( !mCrs.isValid() )
    {
        appendError( QgsErrorMessage( tr( "Could not parse spatial reference" ), QStringLiteral( "AMSProvider" ) ) );
        return;
    }
    for ( const QVariant &sublayer : mLayerInfo["subLayers"].toList() )
    {
        mSubLayers.append( sublayer.toMap()[QStringLiteral( "id" )].toString() );
        mSubLayerVisibilities.append( true );
    }

    mTilingScheme = this;
    mMapProjection.reset( new QgsMapProjection(mCrs) );
    mExtent84 = mMapProjection->toWgs84(mExtent);

    // service info
    {
        mInfo.url = dataSource.param( QStringLiteral( "url" ) );
        mInfo.format = dataSource.param( QStringLiteral( "format" ) ).toLatin1();
        mInfo.singleFusedMapCache = mServiceInfo[QStringLiteral( "singleFusedMapCache" )].toBool();

        // Tiles available, assemble image from tiles
        QVariantMap tileInfo = mServiceInfo[QStringLiteral( "tileInfo" )].toMap();
        mInfo.tileInfo.tileWidth = tileInfo[QStringLiteral( "cols" )].toInt();
        mInfo.tileInfo.tileHeight = tileInfo[QStringLiteral( "rows" )].toInt();
        QVariantMap origin = tileInfo[QStringLiteral( "origin" )].toMap();
        mInfo.tileInfo.x = origin[QStringLiteral( "x" )].toDouble();
        mInfo.tileInfo.y = origin[QStringLiteral( "y" )].toDouble();

        // Search matching resolution (tile resolution <= targetRes)
        QList<QVariant> lodEntries = tileInfo[QStringLiteral( "lods" )].toList();
        for ( const QVariant &lodEntry : lodEntries )
        {
            QVariantMap lodEntryMap = lodEntry.toMap();
            LodEntry le;
            le.level = lodEntryMap[QStringLiteral( "level" )].toInt();
            le.resolution = lodEntryMap[QStringLiteral( "resolution" )].toDouble();
            mInfo.tileInfo.lods.append(le);
        }
    }

    mTimestamp = QDateTime::currentDateTime();
    mValid = true;
}

QStringList QgsAmsProvider::subLayerStyles() const
{
    QStringList styles;
    for ( int i = 0, n = mSubLayers.size(); i < n; ++i )
    {
        styles.append( QString() );
    }
    return styles;
}

void QgsAmsProvider::setLayerOrder( const QStringList &layers )
{
    QStringList oldSubLayers = mSubLayers;
    QList<bool> oldSubLayerVisibilities = mSubLayerVisibilities;
    mSubLayers.clear();
    mSubLayerVisibilities.clear();
    for ( const QString &layer : layers )
    {
        // Search for match
        for ( int i = 0, n = oldSubLayers.size(); i < n; ++i )
        {
            if ( oldSubLayers[i] == layer )
            {
                mSubLayers.append( layer );
                oldSubLayers.removeAt( i );
                mSubLayerVisibilities.append( oldSubLayerVisibilities[i] );
                oldSubLayerVisibilities.removeAt( i );
                break;
            }
        }
    }
    // Add remaining at bottom
    mSubLayers.append( oldSubLayers );
    mSubLayerVisibilities.append( oldSubLayerVisibilities );
}

void QgsAmsProvider::setSubLayerVisibility( const QString &name, bool vis )
{
    for ( int i = 0, n = mSubLayers.size(); i < n; ++i )
    {
        if ( mSubLayers[i] == name )
        {
            mSubLayerVisibilities[i] = vis;
            break;
        }
    }
}

void QgsAmsProvider::reloadData()
{
    mCachedImage = QImage();
}

QgsRasterInterface *QgsAmsProvider::clone() const
{
    QgsDataProvider::ProviderOptions options;
    QgsAmsProvider *provider = new QgsAmsProvider( dataSourceUri(), options );
    provider->copyBaseSettings( *this );
    return provider;
}

static inline QString dumpVariantMap( const QVariantMap &variantMap, const QString &title = QString() )
{
    QString result;
    if ( !title.isEmpty() )
    {
        result += QStringLiteral( "<tr><td class=\"highlight\">%1</td><td>" ).arg( title );
    }
    else
    {
        result += QStringLiteral( "<tr><td>" );
    }
    for ( auto it = variantMap.constBegin(); it != variantMap.constEnd(); ++it )
    {
        QVariantMap childMap = it.value().toMap();
        if ( childMap.isEmpty() )
        {
            result += QStringLiteral( "%1:%2</td></tr>" ).arg( it.key(), it.value().toString() );
        }
        else
        {
            result += QStringLiteral( "%1:<table>%2</table></td></tr>" ).arg( it.key(), dumpVariantMap( childMap ) );
        }
    }
    return result;
}

QString QgsAmsProvider::htmlMetadata()
{
    // This must return the content of a HTML table starting by tr and ending by tr
    return dumpVariantMap( mServiceInfo, tr( "Service Info" ) ) + dumpVariantMap( mLayerInfo, tr( "Layer Info" ) );
}

void QgsAmsProvider::draw( const QgsRectangle &viewExtent, int pixelWidth, int pixelHeight )
{
    if ( !mCachedImage.isNull() && mCachedImageExtent == viewExtent )
    {
        return;
    }
    QgsDataSourceUri dataSource( dataSourceUri() );

    // Use of tiles currently only implemented if service CRS is meter based
    if ( mServiceInfo[QStringLiteral( "singleFusedMapCache" )].toBool() && mCrs.mapUnits() == QgsUnitTypes::DistanceMeters )
    {
        // Compute ideal resolution
        // - Measure distance in meters along lower and upper edge of bounding box
        // - Target resolution is the coarser resolution (resolution = distMeters / pixelWidth)
        double width = viewExtent.xMaximum() - viewExtent.xMinimum();
        double targetRes = width / ( pixelWidth );

        // Tiles available, assemble image from tiles
        QVariantMap tileInfo = mServiceInfo[QStringLiteral( "tileInfo" )].toMap();
        int tileWidth = tileInfo[QStringLiteral( "cols" )].toInt();
        int tileHeight = tileInfo[QStringLiteral( "rows" )].toInt();
        QVariantMap origin = tileInfo[QStringLiteral( "origin" )].toMap();
        double ox = origin[QStringLiteral( "x" )].toDouble();
        double oy = origin[QStringLiteral( "y" )].toDouble();

        // Search matching resolution (tile resolution <= targetRes)
        QList<QVariant> lodEntries = tileInfo[QStringLiteral( "lods" )].toList();
        if ( lodEntries.isEmpty() )
        {
            mCachedImage = QImage();
            mCachedImage.fill( Qt::transparent );
            return;
        }
        int level = 0;
        double resolution = lodEntries.front().toMap()[QStringLiteral( "resolution" )].toDouble();
        for ( const QVariant &lodEntry : lodEntries )
        {
            QVariantMap lodEntryMap = lodEntry.toMap();
            level = lodEntryMap[QStringLiteral( "level" )].toInt();
            resolution = lodEntryMap[QStringLiteral( "resolution" )].toDouble();
            if ( lodEntryMap[QStringLiteral( "resolution" )].toDouble() <= 1.5 * targetRes )
            {
                break;
            }
        }

        // Get necessary tiles to fill extent
        // tile_x = ox + i * (resolution * tileWidth)
        // tile_y = oy - j * (resolution * tileHeight)
        int ixStart = std::floor( ( viewExtent.xMinimum() - ox ) / ( tileWidth * resolution ) );
        int iyStart = std::floor( ( oy - viewExtent.yMaximum() ) / ( tileHeight * resolution ) );
        int ixEnd = std::ceil( ( viewExtent.xMaximum() - ox ) / ( tileWidth * resolution ) );
        int iyEnd = std::ceil( ( oy - viewExtent.yMinimum() ) / ( tileHeight * resolution ) );
        double imX = ( viewExtent.xMinimum() - ox ) / resolution;
        double imY = ( oy - viewExtent.yMaximum() ) / resolution;

        // Query tiles
        int ixCount = ( ixEnd - ixStart + 1 );
        QVector<QByteArray> results( ixCount * ( iyEnd - iyStart + 1 ) );
        QVector<QUrl> queries( ixCount * ( iyEnd - iyStart + 1 ) );
        for ( int iy = iyStart; iy <= iyEnd; ++iy )
        {
            for ( int ix = ixStart; ix <= ixEnd; ++ix )
            {
                queries[( iy - iyStart ) * ixCount + ( ix - ixStart )] = QUrl( dataSource.param( QStringLiteral( "url" ) ) + QStringLiteral( "/tile/%1/%2/%3" ).arg( level ).arg( iy ).arg( ix ) );
            }
        }
        QgsArcGisAsyncParallelQuery query;
        QEventLoop evLoop;
        connect( &query, &QgsArcGisAsyncParallelQuery::finished, &evLoop, &QEventLoop::quit );
        query.start( queries, &results, true );
        evLoop.exec( QEventLoop::ExcludeUserInputEvents );

        // Fill image
        mCachedImage = QImage( pixelWidth, pixelHeight, QImage::Format_ARGB32 );
        mCachedImage.fill( Qt::transparent );
        QPainter painter( &mCachedImage );
        painter.setRenderHint( QPainter::SmoothPixmapTransform, true );
        double resScale = resolution / targetRes;
        painter.scale( resScale, resScale );
        for ( int iy = iyStart; iy <= iyEnd; ++iy )
        {
            for ( int ix = ixStart; ix <= ixEnd; ++ix )
            {
                QImage image = QImage::fromData( results[( iy - iyStart ) * ixCount + ( ix - ixStart )], tileInfo[QStringLiteral( "format" )].toByteArray() );
                painter.drawImage( QPointF( ix * tileWidth - imX, iy * tileHeight - imY ), image );
            }
        }
    }
    else
    {
        QUrl requestUrl( dataSource.param( QStringLiteral( "url" ) ) + "/export" );
        QUrlQuery query;
        query.addQueryItem( QStringLiteral( "bbox" ), QStringLiteral( "%1,%2,%3,%4" ).arg( viewExtent.xMinimum(), 0, 'f', -1 ).arg( viewExtent.yMinimum(), 0, 'f', -1 ).arg( viewExtent.xMaximum(), 0, 'f', -1 ).arg( viewExtent.yMaximum(), 0, 'f', -1 ) );
        query.addQueryItem( QStringLiteral( "size" ), QStringLiteral( "%1,%2" ).arg( pixelWidth ).arg( pixelHeight ) );
        query.addQueryItem( QStringLiteral( "format" ), dataSource.param( QStringLiteral( "format" ) ) );
        query.addQueryItem( QStringLiteral( "layers" ), QStringLiteral( "show:%1" ).arg( dataSource.param( QStringLiteral( "layer" ) ) ) );
        query.addQueryItem( QStringLiteral( "transparent" ), QStringLiteral( "true" ) );
        query.addQueryItem( QStringLiteral( "f" ), QStringLiteral( "image" ) );
        requestUrl.setQuery(query);
        QByteArray reply = QgsArcGisRestUtils::queryService( requestUrl, mErrorTitle, mError );
        mCachedImage = QImage::fromData( reply, dataSource.param( QStringLiteral( "format" ) ).toLatin1() );
        if ( mCachedImage.format() != QImage::Format_ARGB32 )
        {
            mCachedImage = mCachedImage.convertToFormat( QImage::Format_ARGB32 );
        }
    }
}

double QgsAmsProvider::getResolution(int level) const
{
    const auto &les = mInfo.tileInfo.lods;
    if (!les.size())
        return 0;

    for (const auto &le : les)
    {
        if (level == le.level)
            return le.resolution;
    }

    return les.first().resolution;
}

QImage QgsAmsProvider::getLegendGraphic( double /*scale*/, bool forceRefresh, const QgsRectangle * /*visibleExtent*/ )
{
    if ( mLegendFetcher->haveImage() && !forceRefresh )
    {
        return mLegendFetcher->getImage();
    }
    QEventLoop evLoop;
    connect( mLegendFetcher, &QgsImageFetcher::finish, &evLoop, &QEventLoop::quit );
    connect( mLegendFetcher, &QgsImageFetcher::error, &evLoop, &QEventLoop::quit );
    mLegendFetcher->start();
    evLoop.exec( QEventLoop::ExcludeUserInputEvents );
    if ( !mLegendFetcher->errorTitle().isEmpty() )
    {
        mErrorTitle = mLegendFetcher->errorTitle();
        mError = mLegendFetcher->errorMessage();
        return QImage();
    }
    else
    {
        return mLegendFetcher->getImage();
    }
}

QgsImageFetcher *QgsAmsProvider::getLegendGraphicFetcher( const QgsMapSettings * /*mapSettings*/ )
{
    return new QgsAmsLegendFetcher( this );
}

QgsRasterIdentifyResult QgsAmsProvider::identify( const QgsPointXY &point, QgsRaster::IdentifyFormat format, const QgsRectangle &extent, int width, int height, int dpi )
{
    // http://resources.arcgis.com/en/help/rest/apiref/identify.html
    QgsDataSourceUri dataSource( dataSourceUri() );
    QUrl queryUrl( dataSource.param( QStringLiteral( "url" ) ) + "/identify" );
    QUrlQuery query;
    query.addQueryItem( QStringLiteral( "f" ), QStringLiteral( "json" ) );
    query.addQueryItem( QStringLiteral( "geometryType" ), QStringLiteral( "esriGeometryPoint" ) );
    query.addQueryItem( QStringLiteral( "geometry" ), QStringLiteral( "{x: %1, y: %2}" ).arg( point.x(), 0, 'f' ).arg( point.y(), 0, 'f' ) );
    //  query.addQueryItem( "sr", mCrs.postgisSrid() );
    query.addQueryItem( QStringLiteral( "layers" ), QStringLiteral( "all:%1" ).arg( dataSource.param( QStringLiteral( "layer" ) ) ) );
    query.addQueryItem( QStringLiteral( "imageDisplay" ), QStringLiteral( "%1,%2,%3" ).arg( width ).arg( height ).arg( dpi ) );
    query.addQueryItem( QStringLiteral( "mapExtent" ), QStringLiteral( "%1,%2,%3,%4" ).arg( extent.xMinimum(), 0, 'f' ).arg( extent.yMinimum(), 0, 'f' ).arg( extent.xMaximum(), 0, 'f' ).arg( extent.yMaximum(), 0, 'f' ) );
    query.addQueryItem( QStringLiteral( "tolerance" ), QStringLiteral( "10" ) );
    queryUrl.setQuery(query);
    QVariantList queryResults = QgsArcGisRestUtils::queryServiceJSON( queryUrl, mErrorTitle, mError ).value( QStringLiteral( "results" ) ).toList();

    QMap<int, QVariant> entries;

    if ( format == QgsRaster::IdentifyFormatText )
    {
        for ( const QVariant &result : queryResults )
        {
            const QVariantMap resultMap = result.toMap();
            QVariantMap attributesMap = resultMap[QStringLiteral( "attributes" )].toMap();
            QString valueStr;
            for ( auto it = attributesMap.constBegin(); it != attributesMap.constEnd(); ++it )
            {
                valueStr += QStringLiteral( "%1 = %2\n" ).arg( it.key(), it.value().toString() );
            }
            entries.insert( entries.size(), valueStr );
        }
    }
    else if ( format == QgsRaster::IdentifyFormatFeature )
    {
        for ( const QVariant &result : queryResults )
        {
            const QVariantMap resultMap = result.toMap();

            QgsFields fields;
            const QVariantMap attributesMap = resultMap[QStringLiteral( "attributes" )].toMap();
            QgsAttributes featureAttributes;
            for ( auto it = attributesMap.constBegin(); it != attributesMap.constEnd(); ++it )
            {
                fields.append( QgsField( it.key(), QVariant::String, QStringLiteral( "string" ) ) );
                featureAttributes.append( it.value().toString() );
            }
            QgsCoordinateReferenceSystem crs;
            std::unique_ptr< QgsAbstractGeometry > geometry = QgsArcGisRestUtils::parseEsriGeoJSON( resultMap[QStringLiteral( "geometry" )].toMap(), resultMap[QStringLiteral( "geometryType" )].toString(), false, false, &crs );
            QgsFeature feature( fields );
            feature.setGeometry( QgsGeometry( std::move( geometry ) ) );
            feature.setAttributes( featureAttributes );
            feature.setValid( true );
            QgsFeatureStore store( fields, crs );
            QMap<QString, QVariant> params;
            params[QStringLiteral( "sublayer" )] = resultMap[QStringLiteral( "layerName" )].toString();
            params[QStringLiteral( "featureType" )] = attributesMap[resultMap[QStringLiteral( "displayFieldName" )].toString()].toString();
            store.setParams( params );
            store.addFeature( feature );
            entries.insert( entries.size(), qVariantFromValue( QList<QgsFeatureStore>() << store ) );
        }
    }
    return QgsRasterIdentifyResult( format, entries );
}

void QgsAmsProvider::readBlock( int /*bandNo*/, const QgsRectangle &viewExtent, int width, int height, void *data, QgsRasterBlockFeedback *feedback )
{
    Q_UNUSED( feedback );  // TODO: make use of the feedback object

    // TODO: optimize to avoid writing to QImage
    draw( viewExtent, width, height );
    if ( mCachedImage.width() != width || mCachedImage.height() != height )
    {
        QgsDebugMsg( "Unexpected image size for block" );
        return;
    }
    std::memcpy( data, mCachedImage.constBits(), mCachedImage.bytesPerLine() * mCachedImage.height() );
}

bool QgsAmsProvider::isTiled() const
{
    return mInfo.tileInfo.lods.size() > 0;
}

int QgsAmsProvider::getNumberOfXTilesAtLevel(int level) const
{
    if (!isTiled())
        return 2 << level;

    double res = getResolution(level);
    double cols = mExtent.width() / res;
    int tiles = ceil(cols / mInfo.tileInfo.tileWidth);

    return tiles;
}

int QgsAmsProvider::getNumberOfYTilesAtLevel(int level) const
{
    if (!isTiled())
        return 1 << level;

    double res = getResolution(level);
    double cols = mExtent.height() / res;
    int tiles = ceil(cols / mInfo.tileInfo.tileHeight);

    return tiles;
}

LiRectangle QgsAmsProvider::tileXYToRectangle(int x, int y, int level) const
{
    return mMapProjection->toWgs84(toRectangle(tileXYToNativeRectangle(x, y, level)));
}

LiRectangle QgsAmsProvider::tileXYToNativeRectangle(int x, int y, int level) const
{
    if (!isTiled()) {
        return toRectangle(mMapProjection->toNative(computeTileExtent(x, y, level)));
    }

    double ox = mInfo.tileInfo.x;
    double oy = mInfo.tileInfo.y;
    double res = getResolution(level);

    double tileSpaceX = mInfo.tileInfo.tileWidth * res;
    double tileSpaceY = mInfo.tileInfo.tileHeight * res;

    double west = ox + tileSpaceX * x;
    double east = west + tileSpaceX;
    double north = oy - tileSpaceY * y;
    double south = north - tileSpaceY;

    return LiRectangle(west, south, east, north);
}

LiRectangle QgsAmsProvider::rectangleToNativeRectangle(const LiRectangle &rectangle) const
{
    return toRectangle(mMapProjection->toNative(rectangle));
}

Cartesian2 QgsAmsProvider::positionToTileXY(const Cartographic &position, int level) const
{
    // outside the bounds of the tiling scheme
    if (!mExtent84.contains(position))
        return Cartesian2();

    if (!isTiled())
    {
        int xTiles = getNumberOfXTilesAtLevel(level);
        int yTiles = getNumberOfYTilesAtLevel(level);

        LiRectangle rc = LiRectangle::MAX_VALUE;
        double xTileWidth = rc.width() / xTiles;
        double yTileHeight = rc.height() / yTiles;

        int tx = qBound<int>(0, (position.longitude - rc.west) / xTileWidth, xTiles - 1);
        int ty = qBound<int>(0, (rc.north - position.latitude) / yTileHeight, yTiles - 1);

        return Cartesian2(tx, ty);
    }

    auto pos = mMapProjection->project(position);

    double res = getResolution(level);
    double spaceX = mInfo.tileInfo.tileWidth * res;
    double spaceY = mInfo.tileInfo.tileHeight * res;

    double ox = mInfo.tileInfo.x;
    double oy = mInfo.tileInfo.y;

    int tx = (pos.x - ox) / spaceX;
    int ty = (oy - pos.y) / spaceY;

    return Cartesian2(tx, ty);
}

int QgsAmsProvider::tileWidth() const
{
    return isTiled() ? mInfo.tileInfo.tileWidth : 256;
}

int QgsAmsProvider::tileHeight() const
{
    return isTiled() ? mInfo.tileInfo.tileHeight : 256;
}

int QgsAmsProvider::minimumLevel() const
{
    return isTiled() ? mInfo.tileInfo.lods.first().level : 0;
}

int QgsAmsProvider::maximumLevel() const
{
    return isTiled() ? mInfo.tileInfo.lods.last().level : 100;
}

int QgsAmsProvider::computeLevel(const LiRectangle &rectangle) const
{
    if (!isTiled())
        return -1;

    LiRectangle rc = mTilingScheme->rectangleToNativeRectangle(rectangle);

    const auto &lodEntries = mInfo.tileInfo.lods;

    int level = 0;
    double targetRes = 1.5 * rc.width() / mInfo.tileInfo.tileWidth;
    double resolution = lodEntries.first().resolution;

    for ( const auto &lodEntry : lodEntries )
    {
        level = lodEntry.level;
        resolution = lodEntry.resolution;
        if ( resolution <= targetRes )
        {
            break;
        }
    }

    return level;
}

QUrl QgsAmsProvider::getTileUrl(int x, int y, int level)
{
    if (isTiled())
        return QUrl( mInfo.url + QStringLiteral( "/tile/%1/%2/%3" ).arg( level ).arg( y ).arg( x ) );

    QgsRectangle viewExtent = mMapProjection->toNative(computeTileExtent(x, y, level));
    QgsDataSourceUri dataSource( dataSourceUri() );
    QUrl url( dataSource.param( QStringLiteral( "url" ) ) + "/export" );
    QUrlQuery query;
    query.addQueryItem( QStringLiteral( "bbox" ), QStringLiteral( "%1,%2,%3,%4" )
                        .arg( viewExtent.xMinimum(), 0, 'f', -1 )
                        .arg( viewExtent.yMinimum(), 0, 'f', -1 )
                        .arg( viewExtent.xMaximum(), 0, 'f', -1 )
                        .arg( viewExtent.yMaximum(), 0, 'f', -1 ) );
    query.addQueryItem( QStringLiteral( "size" ), QStringLiteral( "%1,%2" ).arg( tileWidth() ).arg( tileHeight() ) );
    query.addQueryItem( QStringLiteral( "format" ), dataSource.param( QStringLiteral( "format" ) ) );
    query.addQueryItem( QStringLiteral( "layers" ),
                        QStringLiteral( "show:%1" ).arg( dataSource.param( QStringLiteral( "layer" ) ) ) );
    query.addQueryItem( QStringLiteral( "transparent" ), QStringLiteral( "true" ) );
    query.addQueryItem( QStringLiteral( "f" ), QStringLiteral( "image" ) );
    url.setQuery(query);

    return url;
}
