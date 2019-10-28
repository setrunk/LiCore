#ifndef URLTEMPLATE_H
#define URLTEMPLATE_H

#include "licore_global.h"
#include "rectangle.h"

class TilingScheme;
class UrlSchemeZeroPadding;

/**
 * @brief
 * URL模板，解析URL地址的参数，根据LOD层级，X方向以及Y方向生成数据地址。
 */
class LICORE_EXPORT UrlTemplate
{
public:
    /**
     * @brief
     *
     * @param url
     * @param tilingScheme
     */
    UrlTemplate(const QUrl &url, TilingScheme *tilingScheme);

    /**
     * @brief
     *
     * @param x
     * @param y
     * @param level
     * @return QUrl
     */
    QUrl buildUrl(int x, int y, int level);

private:
    /**
     * @brief
     *
     */
    struct PartFunc
    {
        /**
         * @brief
         *
         */
        PartFunc() {}
        /**
         * @brief
         *
         * @param n
         * @param i
         */
        PartFunc(const QString &n, int i = -1) : name(n), partIndex(i) {}
        QString name; /**< TODO: describe */
        int partIndex; /**< TODO: describe */
    };

    /**
     * @brief
     *
     * @param x
     * @param y
     * @param level
     * @param partIndex
     * @return QString
     */
    QString partFunction(int x, int y, int level, int partIndex);
    /**
     * @brief
     *
     * @param key
     * @param value
     * @return QString
     */
    QString padWithZerosIfNecessary(const QString &key, const QString &value);
    /**
     * @brief
     *
     * @param url
     * @param tagList
     */
    void urlTemplateToParts(const QString &url, const QStringList &tagList);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param level
     * @return LiRectangle
     */
    LiRectangle computeDegrees(int x, int y, int level);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @param level
     * @return LiRectangle
     */
    LiRectangle computeProjected(int x, int y, int level);

    QUrl _url; /**< TODO: describe */
    TilingScheme *_tilingScheme; /**< TODO: describe */
    int _maximumLevel; /**< TODO: describe */
    int _tileWidth; /**< TODO: describe */
    int _tileHeight; /**< TODO: describe */
    UrlSchemeZeroPadding *_urlSchemeZeroPadding; /**< TODO: describe */
    QStringList _tags; /**< TODO: describe */
    QVector<PartFunc> _urlParts; /**< TODO: describe */
    QStringList _subdomains; /**< TODO: describe */
    bool _isLocal; /**< TODO: describe */

};

#endif // URLTEMPLATE_H
