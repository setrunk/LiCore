#ifndef LIIOREQUEST_H
#define LIIOREQUEST_H

#include "licore_global.h"

class LiIORequestPrivate;

class LiFileIORequest
{
public:
    LiFileIORequest();
    explicit LiFileIORequest(const QUrl &url);

    QUrl url() const;
    void setUrl(const QUrl &url);

private:
    QSharedPointer<LiIORequestPrivate> d;
};

#endif // LIIOREQUEST_H
