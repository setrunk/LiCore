#ifndef URLTEMPLATEIMAGERYPROVIDER_H
#define URLTEMPLATEIMAGERYPROVIDER_H

#include "licore_global.h"
#include "imageryprovider.h"
#include "rectangle.h"

class UrlTemplate;
class UrlSchemeZeroPadding;

class LICORE_EXPORT UrlTemplateImageryProvider : public ImageryProvider
{
    Q_OBJECT
public:
    UrlTemplateImageryProvider(const QString &url,
                               TilingScheme *tilingScheme,
                               int maximumLevel,
                               int minimumLevel = 0,
                               int tileWidth = 256,
                               int tileHeight = 256,
                               bool hasAlphaChannel = true,
                               QObject *parent = 0);

    virtual void requestImage(int x, int y, int level, Imagery *imagery, PriorityFunction priorityFunc);
    virtual QUrl buildImageUrl(int x, int y, int level);

private:
    QImage createEmptyImage();

    QSharedPointer<UrlTemplate> _urlTemplate;
};

#endif // URLTEMPLATEIMAGERYPROVIDER_H
