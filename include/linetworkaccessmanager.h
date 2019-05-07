#ifndef LINETWORKACCESSMANAGER_H
#define LINETWORKACCESSMANAGER_H

#include "licore_global.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class LICORE_EXPORT LiNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit LiNetworkAccessManager(QObject *parent = 0);
    virtual ~LiNetworkAccessManager();

    static LiNetworkAccessManager *instance();

    bool printMessage() const;
    void setPrintMessage(bool printMessage);

    quint64 cacheSizeOfBytes() const; // default = 1024*1024*1024 (1 GB)
    void setCacheSizeOfBytes(quint64 cacheSizeOfBytes);

signals:

public slots:

private:
    void setupDefaultProxyAndCache();

    bool mInitialized;
    bool m_printMessage;
    quint64 m_cacheSizeOfBytes;
    static LiNetworkAccessManager *smMainNAM;
};

#endif // LINETWORKACCESSMANAGER_H
