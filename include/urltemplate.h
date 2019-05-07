#ifndef URLTEMPLATE_H
#define URLTEMPLATE_H

#include "licore_global.h"
#include "rectangle.h"

class TilingScheme;
class UrlSchemeZeroPadding;

class LICORE_EXPORT UrlTemplate
{
public:
    UrlTemplate(const QUrl &url, TilingScheme *tilingScheme);

    QUrl buildUrl(int x, int y, int level);

private:
    struct PartFunc
    {
        PartFunc() {}
        PartFunc(const QString &n, int i = -1) : name(n), partIndex(i) {}
        QString name;
        int partIndex;
    };

    QString partFunction(int x, int y, int level, int partIndex);
    QString padWithZerosIfNecessary(const QString &key, const QString &value);
    void urlTemplateToParts(const QString &url, const QStringList &tagList);
    LiRectangle computeDegrees(int x, int y, int level);
    LiRectangle computeProjected(int x, int y, int level);

    QUrl _url;
    TilingScheme *_tilingScheme;
    int _maximumLevel;
    int _tileWidth;
    int _tileHeight;
    UrlSchemeZeroPadding *_urlSchemeZeroPadding;
    QStringList _tags;
    QVector<PartFunc> _urlParts;
    QStringList _subdomains;
    bool _isLocal;

};

#endif // URLTEMPLATE_H
