#include "wmsimageryprovider.h"
#include "webmercatorprojection.h"
#include "geographictilingscheme.h"
#include "ellipsoid.h"
#include "linetworkaccessmanager.h"
#include "asyncfuture.h"
#include "lifilesystem.h"
#include "transformhelper.h"
#include "arcgistilingscheme.h"

WmsImageryProvider::WmsImageryProvider(const QString &url, QObject *parent)
    : ImageryProvider(url, new GeographicTilingScheme, parent)
{
    _ready = false;

    QUrlQuery query( url );
    query.addQueryItem("f", "json");

    QUrl queryUrl( url );
    queryUrl.setQuery(query);

    auto promise = LiFileSystem::readJson(queryUrl);
    observe(promise).subscribe([this](QJsonValue json) {
        auto serviceInfo = json.toObject().toVariantMap();
        ArcgisTilingScheme *tilingScheme = new ArcgisTilingScheme(serviceInfo);
        _tileWidth = tilingScheme->tileWidth();
        _tileHeight = tilingScheme->tileHeight();
        _maximumLevel = tilingScheme->maximumLevel();
        _rectangle = tilingScheme->rectangle();

        SAFE_DELETE(_tilingScheme);
        _tilingScheme = tilingScheme;

        _ready = true;
        _readyPromise.complete();
    }, [this, url] {
        qWarning() << "failed to load imagery layer:" << url;
        _readyPromise.cancel();
    });

//    QString errorTitle, errorText;
//    QByteArray reply = LiFileSystem::queryService( queryUrl, errorTitle, errorText );
//    if ( reply.isEmpty() )
//    {
//        qDebug() << "queryService error:" << errorText;
//        return;
//    }

//    // Parse data
//    QJsonParseError jsonpe;
//    QVariantMap serviceInfo = QJsonDocument::fromJson(reply, &jsonpe).toVariant().toMap();
//    if (jsonpe.error != QJsonParseError::NoError)
//    {
//        qDebug() << "QJsonDocument::fromJson error:" << jsonpe.errorString();
//        return;
//    }

//    ArcgisTilingScheme *tilingScheme = new ArcgisTilingScheme(serviceInfo);

//    _tileWidth = tilingScheme->tileWidth();
//    _tileHeight = tilingScheme->tileHeight();
//    _maximumLevel = tilingScheme->maximumLevel();
//    _rectangle = tilingScheme->rectangle();

//    SAFE_DELETE(_tilingScheme);
//    _tilingScheme = tilingScheme;

    //    _ready = true;
}

QUrl WmsImageryProvider::buildImageUrl(int x, int y, int level)
{
    return QUrl(QString("%1/tile/%2/%3/%4").arg(_url).arg(level).arg(y).arg(x));
}

int WmsImageryProvider::computeImageryLevel(const LiRectangle &rectangle) const
{
    ArcgisTilingScheme *scheme = (ArcgisTilingScheme*)tilingScheme();
    double dst = 1.5 * rectangle.width();

    for (int i = 0; i < maximumLevel(); ++i)
    {
        double resolution = scheme->resolution(i);
        if (_tileWidth * resolution <= dst)
            return i;
    }

    return maximumLevel();
}
