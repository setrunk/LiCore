#ifndef LIREQUEST_H
#define LIREQUEST_H

#include "licore_global.h"
#include "asyncfuture.h"
#include "boundingvolume.h"
#include <QNetworkRequest>

class LiRequestPrivate;
class RequestScheduler;

typedef std::function<double(void)> PriorityFunction;

class LICORE_EXPORT LiRequest
{
public:
    enum RequestState
    {
        UNISSUED = 0,
        ISSUED,
        ACTIVE,
        RECEIVED,
        CANCELLED,
        FAILED
    };

    enum RequestType
    {
        TERRAIN = 0,
        IMAGERY,
        TILES3D,
        OTHER
    };

    LiRequest();
    LiRequest(const QNetworkRequest &request,
              PriorityFunction priorityFunc,
              RequestType type,
              bool throttleByServer = true,
              bool throttle = true,
              const QString &serverKey = QString());
    LiRequest(const LiRequest &o);
    ~LiRequest();

    LiRequest &operator =(const LiRequest &o);
    bool operator ==(const LiRequest &other) const;

    QNetworkRequest request() const;

    bool isNull() const;
    bool isValid() const;
    bool isUnissued() const;
    bool isActive() const;
    bool isCanceled() const;

    void cancel();

    RequestState state() const;
    void setState(RequestState state);

    QUrl url() const;
    void setUrl(const QUrl &url);

    QString serverKey() const;
    void setServerKey(const QString &key);

    RequestType type() const;
    void setType(RequestType type);

    QVariantMap headers() const;
    void setHeader(const QVariantMap &headers);

    bool throttleByServer() const;
    bool throttle() const;

    double priority() const;
    void updatePriority();

    QFuture<QByteArray> loadArrayBuffer();
    QFuture<QImage> loadImage(bool mirrored = false);

    QFuture<QByteArray> promise() const;

private:
    void create();
    void received(const QByteArray &data);
    void failed();
    QSharedPointer<LiRequestPrivate> d_ptr;
    friend class RequestScheduler;
};

#endif // LIREQUEST_H
