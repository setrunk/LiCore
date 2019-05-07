#ifndef LIPROVIDERMANAGER_H
#define LIPROVIDERMANAGER_H

#include "liextrasglobal.h"
#include <qgsprovidermetadata.h>

class LIEXTRAS_EXPORT LiProviderManager
{
public:
    ~LiProviderManager();

    static LiProviderManager *instance();

    QgsDataProvider *provider(const QString& providerKey, const QString& dataSource);

private:
    LiProviderManager();

    QString mVectorFileFilters;
    QString mRasterFileFilters;
    QString mProtocolDrivers;
    QString mDirectoryDrivers;
    QString mDatabaseDrivers;
    std::map<QString, QgsProviderMetadata*> mProviders;
};

#endif // LIPROVIDERMANAGER_H
