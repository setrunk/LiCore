#include "liprovidermanager.h"
#include <QCoreApplication>
#include <qgsdataprovider.h>
#include <qgsprovidermetadata.h>
#include "qgsamsprovider.h"

// typedefs for provider plugin functions of interest
typedef QString providerkey_t();
typedef QString description_t();
typedef bool    isprovider_t();
typedef QString fileVectorFilters_t();
typedef void buildsupportedrasterfilefilter_t( QString & theFileFiltersString );
typedef QString databaseDrivers_t();
typedef QString directoryDrivers_t();
typedef QString protocolDrivers_t();
//typedef int dataCapabilities_t();
//typedef QgsDataItem * dataItem_t(QString);

// typedef for the QgsDataProvider class factory
typedef QgsDataProvider * classFactoryFunction_t( const QString * );

// typedef for the unload dataprovider function
typedef void cleanupProviderFunction_t();

// This should be QWidget, not QDialog
typedef QWidget * selectFactoryFunction_t( QWidget * parent, Qt::WindowFlags fl );

LiProviderManager::LiProviderManager()
{
    QDir mLibraryDirectory = QCoreApplication::applicationDirPath() + "/plugins";

    mLibraryDirectory.setSorting( QDir::Name | QDir::IgnoreCase );
    mLibraryDirectory.setFilter( QDir::Files | QDir::NoSymLinks );
    mLibraryDirectory.setNameFilters( QStringList( "*.dll" ) );

    qDebug() << QString( "Checking %1 for provider plugins" ).arg( mLibraryDirectory.path() );

    if ( mLibraryDirectory.count() == 0 )
    {
        QString msg = QObject::tr( "No QGIS data provider plugins found in:\n%1\n" ).arg( mLibraryDirectory.path() );
        msg += QObject::tr( "No vector layers can be loaded. Check your QGIS installation" );
        qDebug() << msg;

//        QgsMessageOutput* output = QgsMessageOutput::createMessageOutput();
//        output->setTitle( QObject::tr( "No Data Providers" ) );
//        output->setMessage( msg, QgsMessageOutput::MessageText );
//        output->showMessage();
        return;
    }

    // provider file regex pattern, only files matching the pattern are loaded if the variable is defined
//    QString filePattern = getenv( "QGIS_PROVIDER_FILE" );
//    QRegExp fileRegexp;
//    if ( !filePattern.isEmpty() )
//    {
//        fileRegexp.setPattern( filePattern );
//    }

    for ( const QFileInfo& fi : mLibraryDirectory.entryInfoList() )
    {
//        if ( !fileRegexp.isEmpty() )
//        {
//            if ( fileRegexp.indexIn( fi.fileName() ) == -1 )
//            {
//                QDebug( "provider " + fi.fileName() + " skipped because doesn't match pattern " + filePattern );
//                continue;
//            }
//        }

        QLibrary myLib( fi.filePath() );
        if ( !myLib.load() )
        {
            qDebug() << QString( "Checking %1: ...invalid (lib not loadable): %2" ).arg( myLib.fileName(), myLib.errorString() );
            continue;
        }

        //MH: Added a further test to detect non-provider plugins linked to provider plugins.
        //Only pure provider plugins have 'type' not defined
        isprovider_t *hasType = reinterpret_cast< isprovider_t * >( cast_to_fptr( myLib.resolve( "type" ) ) );
        if ( hasType )
        {
            qDebug() << QString( "Checking %1: ...invalid (has type method)" ).arg( myLib.fileName() );
            continue;
        }

        // get the description and the key for the provider plugin
        isprovider_t *isProvider = reinterpret_cast< isprovider_t * >( cast_to_fptr( myLib.resolve( "isProvider" ) ) );
        if ( !isProvider )
        {
            qDebug() << QString( "Checking %1: ...invalid (no isProvider method)" ).arg( myLib.fileName() );
            continue;
        }

        // check to see if this is a provider plugin
        if ( !isProvider() )
        {
            qDebug() << QString( "Checking %1: ...invalid (not a provider)" ).arg( myLib.fileName() );
            continue;
        }

        // looks like a provider. get the key and description
        description_t *pDesc = reinterpret_cast< description_t * >( cast_to_fptr( myLib.resolve( "description" ) ) );
        if ( !pDesc )
        {
            qDebug() << QString( "Checking %1: ...invalid (no description method)" ).arg( myLib.fileName() );
            continue;
        }

        providerkey_t *pKey = reinterpret_cast< providerkey_t * >( cast_to_fptr( myLib.resolve( "providerKey" ) ) );
        if ( !pKey )
        {
            qDebug() << QString( "Checking %1: ...invalid (no providerKey method)" ).arg( myLib.fileName() );
            continue;
        }

        // add this provider to the provider map
        mProviders[pKey()] = new QgsProviderMetadata( pKey(), pDesc(), myLib.fileName() );

        // load database drivers
        databaseDrivers_t *pDatabaseDrivers = reinterpret_cast< databaseDrivers_t * >( cast_to_fptr( myLib.resolve( "databaseDrivers" ) ) );
        if ( pDatabaseDrivers )
        {
            mDatabaseDrivers = pDatabaseDrivers();
        }

        // load directory drivers
        directoryDrivers_t *pDirectoryDrivers = reinterpret_cast< directoryDrivers_t * >( cast_to_fptr( myLib.resolve( "directoryDrivers" ) ) );
        if ( pDirectoryDrivers )
        {
            mDirectoryDrivers = pDirectoryDrivers();
        }

        // load protocol drivers
        protocolDrivers_t *pProtocolDrivers = reinterpret_cast< protocolDrivers_t * >( cast_to_fptr( myLib.resolve( "protocolDrivers" ) ) );
        if ( pProtocolDrivers )
        {
            mProtocolDrivers = pProtocolDrivers();
        }

        // now get vector file filters, if any
        fileVectorFilters_t *pFileVectorFilters = reinterpret_cast< fileVectorFilters_t * >( cast_to_fptr( myLib.resolve( "fileVectorFilters" ) ) );
        if ( pFileVectorFilters )
        {
            QString fileVectorFilters = pFileVectorFilters();

            if ( !fileVectorFilters.isEmpty() )
                mVectorFileFilters += fileVectorFilters;

            qDebug() << QString( "Checking %1: ...loaded ok (%2 file filters)" ).arg( myLib.fileName() ).arg( fileVectorFilters.split( ";;" ).count() );
        }

        // now get raster file filters, if any
        // this replaces deprecated QgsRasterLayer::buildSupportedRasterFileFilter
        buildsupportedrasterfilefilter_t *pBuild =
                reinterpret_cast< buildsupportedrasterfilefilter_t * >( cast_to_fptr( myLib.resolve( "buildSupportedRasterFileFilter" ) ) );
        if ( pBuild )
        {
            QString fileRasterFilters;
            pBuild( fileRasterFilters );

            qDebug() << "raster filters: " + fileRasterFilters;
            if ( !fileRasterFilters.isEmpty() )
                mRasterFileFilters += fileRasterFilters;

            qDebug() << QString( "Checking %1: ...loaded ok (%2 file filters)" ).arg( myLib.fileName() ).arg( fileRasterFilters.split( ";;" ).count() );
        }
    }
}

LiProviderManager::~LiProviderManager()
{

}

LiProviderManager *LiProviderManager::instance()
{
    static LiProviderManager m;
    return &m;
}

QgsDataProvider *LiProviderManager::provider(const QString &providerKey, const QString &dataSource)
{
    if (providerKey == QLatin1String("arcgismapserver")) {
        return new QgsAmsProvider(dataSource, QgsDataProvider::ProviderOptions());
    }

    auto it = mProviders.find(providerKey);
    if (it == mProviders.end())
        return nullptr;

    QgsProviderMetadata * md = it->second;
    QString libPath = md->library();

    QLibrary myLib( libPath );
    qDebug() << "Library name is " + myLib.fileName();

    if ( !myLib.load() )
    {
      qDebug() << QObject::tr( "Failed to load %1: %2" ).arg( libPath, myLib.errorString() );
      return nullptr;
    }

    classFactoryFunction_t *classFactory = reinterpret_cast< classFactoryFunction_t * >( cast_to_fptr( myLib.resolve( "classFactory" ) ) );
    if ( !classFactory )
    {
      qDebug() << QString( "Failed to load %1: no classFactory method" ).arg( libPath );
      return nullptr;
    }

    QgsDataProvider *dataProvider = classFactory( &dataSource );
    if ( !dataProvider )
    {
      qDebug() << QObject::tr( "Unable to instantiate the data provider plugin %1" ).arg( libPath );
      myLib.unload();
      return nullptr;
    }

    qDebug() << QString( "Instantiated the data provider plugin: %1" ).arg( dataProvider->name() );

    return dataProvider;
}
