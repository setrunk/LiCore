#ifndef FUTURE_H
#define FUTURE_H

#include <QFuture>
#include <QByteArray>
#include <QImage>
#include <QJsonValue>

typedef QFuture<void> Future;
typedef QFuture<void> Promise;
typedef QFuture<QByteArray> BufferPromise;
typedef QFuture<QImage> ImagePromise;
typedef QFuture<QJsonValue> JsonPromise;

#endif // FUTURE_H
