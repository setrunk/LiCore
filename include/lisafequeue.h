#ifndef LISAFEQUEUE_H
#define LISAFEQUEUE_H

#include "licore_global.h"

template<class T>
class LICORE_EXPORT LiSafeQueue : public QList<T>
{
public:

    void enqueue(const T &t)
    {
        QMutexLocker locker(&mutex);
        append(t);
        semaphore.release(1);
    }

    T dequeue()
    {
        QMutexLocker locker(&mutex);
        return takeFirst();
    }

public:
    QMutex mutex;
    QSemaphore semaphore;
};

#endif // LISAFEQUEUE_H
