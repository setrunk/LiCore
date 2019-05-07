#ifndef IMAGERYPROVIDER_H
#define IMAGERYPROVIDER_H

#include "licore_global.h"
#include "rectangle.h"
#include "lirequest.h"
#include "asyncfuture.h"

class Imagery;
class TilingScheme;
class TileDiscardPolicy;
class QuadtreeTile;
class TerrainProvider;

/**
 * @brief
 * ImageryProvider描述ImageryLayer是如何从url服务器上获取影像数据的，
 * 提供了影像数据的范围、瓦片大小、坐标系统等信息，同时提供影像数据
 * 请求等功能。
 */
class LICORE_EXPORT ImageryProvider : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     * 构造函数
     * @param url
     * 影像数据服务的地址
     * @param tilingScheme
     * 影像数据的切片方案
     * @param parent
     */
    explicit ImageryProvider(QObject *parent = 0);

    ImageryProvider(const QString &url, TilingScheme *tilingScheme, QObject *parent = 0);

    /**
     * @brief
     * 请求影像切片数据
     * @param x
     * X方向的序号
     * @param y
     * Y方向的序号
     * @param level
     * LOD层级
     * @param imagery
     * 保存影像切片数据的对象
     * @param priorityFunc
     * 请求优先级的计算函数
     */
    virtual void requestImage(int x, int y, int level, Imagery *imagery, PriorityFunction priorityFunc);

    /**
     * @brief
     * 根据坐标序号生成相应的影像切片url地址
     * @param x
     * X方向的序号
     * @param y
     * Y方向的序号
     * @param level
     * LOD层级
     * @return QUrl
     */
    virtual QUrl buildImageUrl(int x, int y, int level) = 0;

    /**
     * @brief
     * 返回请求数据的等待信号，一旦请求完成，该信号会变成finished状态
     * @return QFuture<void>
     */
    QFuture<void> readyPromise() const { return _readyPromise.future(); }

    /**
     * @brief
     * 查询内部初始化是否已完成，一旦完成，就可以开始请求数据服务
     * @return bool
     */
    virtual bool ready() const { return _ready; }

    /**
     * @brief
     * 返回影像数据服务的url地址
     * @return QUrl
     */
    virtual QUrl url() const { return _url; }

    /**
     * @brief
     * 返回影像切片的宽度
     * @return int
     */
    virtual int tileWidth() const { return _tileWidth; }

    /**
     * @brief
     * 返回影像切片的高度
     * @return int
     */
    virtual int tileHeight() const { return _tileHeight; }

    /**
     * @brief
     * 返回影像切片的最低LOD级别
     * @return int
     */
    virtual int minimumLevel() const { return _minimumLevel; }

    /**
     * @brief
     * 返回影像切片的最高LOD级别
     * @return int
     */
    virtual int maximumLevel() const { return _maximumLevel; }

    /**
     * @brief
     * 返回影像切片是否带Alpha通道
     * @return bool
     */
    virtual bool hasAlphaChannel() const { return _hasAlphaChannel; }

    /**
     * @brief
     * 返回影像切片的范围
     * @return LiRectangle
     */
    virtual LiRectangle rectangle() const { return _rectangle; }

    /**
     * @brief
     * 查询边界为rectangle的坐标范围是否有可用的影像数据
     * @param rectangle
     * 需要查询的坐标范围
     * @return bool
     */
    virtual bool isAvailable(const LiRectangle &rectangle) const;

    /**
     * @brief
     * 查询可匹配坐标范围的可用的最高LOD级别
     * @param rectangle
     * @return int
     */
    virtual int computeImageryLevel(const LiRectangle &rectangle) const { return -1; }

    /**
     * @brief
     * 返回该服务的切片方案
     * @return TilingScheme
     */
    TilingScheme *tilingScheme() const { return _tilingScheme; }

    /**
     * @brief
     * 返回该服务的无效切片策略
     * @return TileDiscardPolicy
     */
    TileDiscardPolicy *tileDiscardPolicy() const { return _tileDiscardPolicy; }

    QString userAgent() const { return _userAgent; }
    void setUserAgent(const QString &userAgent) { _userAgent = userAgent; }

protected:
    /**
     * @brief
     * 执行加载影像切片操作，由于加载优先级的关系，可能加载会失败
     * @param url
     * 影像切片的url地址
     * @param imagery
     * 保存影像切片数据的对象
     * @param priorityFunc
     * 加载优先级的计算函数
     * @return bool 如果加载成功返回true，失败返回false
     */
    bool loadImage(const QUrl &url, Imagery *imagery, PriorityFunction priorityFunc);

    QString _url; /**< TODO: describe */
    QString _pickFeaturesUrl; /**< TODO: describe */
    QString _userAgent;
    bool _ready; /**< TODO: describe */
    Deferred<void> _readyPromise; /**< TODO: describe */
    int _tileWidth; /**< TODO: describe */
    int _tileHeight; /**< TODO: describe */
    int _maximumLevel; /**< TODO: describe */
    int _minimumLevel; /**< TODO: describe */
    bool _hasAlphaChannel; /**< TODO: describe */
    LiRectangle _rectangle; /**< TODO: describe */
    TilingScheme *_tilingScheme; /**< TODO: describe */
    TileDiscardPolicy *_tileDiscardPolicy; /**< TODO: describe */
    QString _credit; /**< TODO: describe */
    QCache<QString, QImage> _cache;
};

#endif // IMAGERYPROVIDER_H
