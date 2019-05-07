#ifndef LIPLUGINIMAGERYPROVIDER_H
#define LIPLUGINIMAGERYPROVIDER_H

#include "liextrasglobal.h"
#include "imageryprovider.h"

class LiProviderInterface;

class LIEXTRAS_EXPORT LiPluginImageryProvider : public ImageryProvider
{
    Q_OBJECT
public:
    explicit LiPluginImageryProvider(const QString &providerKey, const QString &url, QObject *parent = 0);

    QUrl buildImageUrl(int x, int y, int level);
    int computeImageryLevel(const LiRectangle &rectangle) const;

private:
    QString m_providerKey;
    QString m_sourceUrl;
    LiProviderInterface *m_interface;
};

#endif // LIPLUGINIMAGERYPROVIDER_H
