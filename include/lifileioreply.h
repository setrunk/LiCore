#ifndef LIIOREPLY_H
#define LIIOREPLY_H

#include "licore_global.h"
#include <QNetworkReply>

class LiFileIOThread;
class LiFileIORequest;
class LiFileIOReplyPrivate;

class LiFileIOReply : public QObject
{
    Q_OBJECT
public:
    explicit LiFileIOReply(QObject *parent = 0);
    explicit LiFileIOReply(const LiFileIORequest &request, QObject *parent = 0);
    ~LiFileIOReply();

    LiFileIORequest request() const;
    void setRequest(const LiFileIORequest &request);

    bool hasError() const;
    QByteArray readAll();

signals:
    void finished();

private:
    QScopedPointer<LiFileIOReplyPrivate> d;
    friend class LiFileIOThread;
};

#endif // LIIOREPLY_H
