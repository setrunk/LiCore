#ifndef WMSIMAGERYPROVIDER_H
#define WMSIMAGERYPROVIDER_H

#include "liextrasglobal.h"
#include "imageryprovider.h"

class LIEXTRAS_EXPORT WmsImageryProvider : public ImageryProvider
{
    Q_OBJECT
public:
    explicit WmsImageryProvider(const QString &url, QObject *parent = 0);

    QUrl buildImageUrl(int x, int y, int level);
    int computeImageryLevel(const LiRectangle &rectangle) const;
};

#endif // WMSIMAGERYPROVIDER_H
