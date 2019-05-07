#ifndef LITHREADIO_H
#define LITHREADIO_H

#include "licore_global.h"

class LiFileIOReply;
class LiFileIORequest;

class LiFileIOThread : public QThread
{
    Q_OBJECT
public:
    explicit LiFileIOThread(QObject *parent = 0);
    ~LiFileIOThread();

    static LiFileIOThread *instance();

    void shutdown();

    QFuture<QByteArray> addWork(const LiFileIORequest &request);
    QFuture<QByteArray> addWork(const QUrl &url);
    int workCount();

protected:
    void run();

signals:

private:
    QAtomicInt m_running;
    QSemaphore m_semaphore;
    QMutex m_mutex;
    QQueue<LiFileIOReply *> m_works;
};

#endif // LITHREADIO_H
