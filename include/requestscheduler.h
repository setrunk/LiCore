#ifndef REQUESTSCHEDULER_H
#define REQUESTSCHEDULER_H

#include "licore_global.h"
#include "asyncfuture.h"
#include "requestheap.h"
#include "cartesian3.h"
#include "cartographic.h"
#include "lirequest.h"

class FrameState;

class LICORE_EXPORT RequestScheduler
{
public:
    ~RequestScheduler();

    static RequestScheduler *instance();

    void update();

    QFuture<QByteArray> request(const LiRequest &request);
    QFuture<QByteArray> issueRequest(LiRequest &request);
    QFuture<QByteArray> startRequest(LiRequest &request);
    void cancelRequest(LiRequest &request);

    QString getServerKey(const QUrl &url);
    bool serverHasOpenSlots(const QString &serverKey);
    void getRequestReceivedFunction(LiRequest request, const QByteArray &results);
    void getRequestFailedFunction(LiRequest request);

private:
    RequestScheduler();

    struct Statistics
    {
        int numberOfAttemptedRequests = 0;
        int numberOfActiveRequests = 0;
        int numberOfCancelledRequests = 0;
        int numberOfCancelledActiveRequests = 0;
        int numberOfFailedRequests = 0;
        int numberOfActiveRequestsEver = 0;
    };
    Statistics statistics;

    void clearStatistics();
    void updateStatistics();

    void increaseActiveRequestsByServer(const QString &serverKey);
    void decreaseActiveRequestsByServer(const QString &serverKey);

    int maximumRequests = 50;
    int maximumRequestsPerServer = 6;
    bool throttleRequests = true;
    RequestHeap requestHeap;
    QVector<LiRequest> activeRequests;
    QHash<QString, int> numberOfActiveRequestsByServer;
    Cartesian3 m_cameraPosition;
    Cartographic m_cameraCartographic;
};

#endif // REQUESTSCHEDULER_H
