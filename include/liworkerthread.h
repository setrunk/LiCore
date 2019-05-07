#ifndef LIWORKERTHREAD_H
#define LIWORKERTHREAD_H

#include "licore_global.h"

class LiWorkerThreadPrivate;

class LICORE_EXPORT LiWorkerThread : public QThread
{
    Q_OBJECT
public:
    explicit LiWorkerThread(QObject *parent = nullptr);
    ~LiWorkerThread();

    typedef std::function<void()> Task;

    QFuture<void> runTask(Task task);

private:
    QSharedPointer<LiWorkerThreadPrivate> d;
};


#endif // LIWORKERTHREAD_H
