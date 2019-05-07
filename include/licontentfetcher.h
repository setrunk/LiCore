#ifndef LICONTENTFETCHER_H
#define LICONTENTFETCHER_H

#include "licore_global.h"
#include "asyncfuture.h"
#include <QNetworkReply>

class LiWorkerThread;

class LICORE_EXPORT LiContentFetcher : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        Buffer = 0,
        Image,
        Json
    };

    explicit LiContentFetcher();
    virtual ~LiContentFetcher();

    QFuture<QVariant> fetchContent( const QNetworkRequest &req, Type type = Buffer );
    QFuture<QVariant> fetchContent( const QUrl& url, Type type = Buffer );

    QByteArray readAll();
    QString contentAsString();
    QImage contentAsImage();
    QJsonDocument contentAsJson();

    bool ready() const { return m_contentLoaded; }
    QNetworkReply::NetworkError error() const { return m_reply ? m_reply->error() : QNetworkReply::NoError; }

private slots:
    void contentLoaded();

private:
    void doFetch();
    void cancel();
    void complete();
    QTextCodec *codecForHtml( QByteArray &array ) const;

    Type m_type = Buffer;
    QNetworkRequest m_request;
    QNetworkReply* m_reply;
    QVariant m_result;
    Deferred<QVariant> m_defer;
    bool m_contentLoaded;

    static LiWorkerThread *m_workerThread;
};

#endif // LICONTENTFETCHER_H
