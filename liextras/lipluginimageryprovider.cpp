#include "lipluginimageryprovider.h"
#include "geographictilingscheme.h"
#include "qgsamsprovider.h"
#include "qgswmsprovider.h"
#include "liproviderinterface.h"

LiPluginImageryProvider::LiPluginImageryProvider(const QString &providerKey, const QString &url, QObject *parent)
    : ImageryProvider(url, new GeographicTilingScheme(), parent)
    , m_providerKey(providerKey)
    , m_sourceUrl(url)
{
    _ready = false;

    auto promise = QtConcurrent::run([=] {
        QgsRasterDataProvider *p = nullptr;
        if (providerKey == QLatin1String("arcgismapserver")) {
            p = new QgsAmsProvider(url);
        } else if (providerKey == QLatin1String("wms")) {
            p = new QgsWmsProvider(url);
        }

        if (p && !p->isValid()) {
            delete p;
            p = nullptr;
        }
        return p;
    });

    observe(promise).subscribe([=](QgsRasterDataProvider *p) {
        if (p) {
            if (providerKey == QLatin1String("arcgismapserver")) {
                auto pp = qobject_cast<QgsAmsProvider*>(p);
                m_interface = pp->providerInterface();
                _tilingScheme = pp->tilingScheme();
            } else if (providerKey == QLatin1String("wms")) {
                auto pp = qobject_cast<QgsWmsProvider*>(p);
                m_interface = pp->providerInterface();
                _tilingScheme = pp->tilingScheme();
                if (pp->isXyzTiles())
                    setUserAgent(QStringLiteral("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36"));
//                setUserAgent(QStringLiteral("Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0;"));
            }

            _rectangle = _tilingScheme->rectangle();
            _tileWidth = m_interface->tileWidth();
            _tileHeight = m_interface->tileHeight();
            _minimumLevel = m_interface->minimumLevel();
            _maximumLevel = m_interface->maximumLevel();

            _ready = true;
            _readyPromise.complete();
        } else {
            _readyPromise.cancel();
        }
    });
}

QUrl LiPluginImageryProvider::buildImageUrl(int x, int y, int level)
{
    return m_interface->getTileUrl(x, y, level);
}

int LiPluginImageryProvider::computeImageryLevel(const LiRectangle &rectangle) const
{
    return m_interface->computeLevel(rectangle);
}
