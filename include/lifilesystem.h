#ifndef LIFILESYSTEM_H
#define LIFILESYSTEM_H

#include "licore_global.h"
#include "lirequest.h"
#include "future.h"

/**
 * @brief
 * 文件系统，提供异步加载网络以及本地文件资源函数。
 */
class LICORE_EXPORT LiFileSystem
{
public:
    /**
     * @brief
     * 异步加载文件资源，或者异步解码base64内容
     * @param url 文件的路径或base64数据，如 "http://hello.com/a.jpg" "file:///c:/a.jpg" "qrc:/a.jpg" "data:image/png;base64,abc..."
     * @param headers 设置http的相关参数
     * @return BufferPromise 返回信号，用于加载完成后的通知
     */
    static BufferPromise readFile(const QUrl &url);

    static QFuture<QVariant> loadResource(const QNetworkRequest &req);

    /**
     * @brief
     * 异步加载图像文件
     * @param url 图像文件的路径
     * @param mirrored 是否垂直镜像
     * @return ImagePromise 返回信号，用于加载完成后的通知
     */
    static ImagePromise readImage(const QUrl &url, bool mirrored = false);

    /**
     * @brief
     * 异步加载json文件
     * @param url json文件的路径
     * @return JsonPromise 返回信号，用于加载完成后的通知
     */
    static JsonPromise readJson(const QUrl &url);

    /**
     * @brief
     * 加载服务（非异步）
     * @param url 服务的路径
     * @param errorTitle 加载出错的标题
     * @param errorText 加载出错的信息
     * @return QByteArray 返回加载的服务内容
     */
    static QByteArray queryService( const QUrl& url, QString& errorTitle, QString& errorText );

    /**
     * @brief
     * 解析Base64编码的数据（非异步）
     * @param str 输入的文本，以"data:"开头
     * @return QByteArray 解析完成后的内容
     */
    static QByteArray dataFromUri(const QString &str);
};

#endif // LIFILESYSTEM_H
