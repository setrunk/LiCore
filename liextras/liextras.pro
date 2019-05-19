TEMPLATE = lib

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../../x64/debug
    TARGET = LiExtrasd
} else {
    DESTDIR = $$PWD/../../x64/release
    TARGET = LiExtras
}

QT += widgets qml qml-private quick core-private network xml concurrent quickwidgets sql
CONFIG += c++11
DEFINES += LIEXTRAS_LIBRARY
DEFINES += NOMINMAX

DEFINES += _UNICODE \
         QT_NO_OPENSSL \
         CORE_EXPORT=__declspec(dllimport)\
         GUI_EXPORT=__declspec(dllimport)\
         APP_EXPORT=__declspec(dllimport)\
         M_PI_2=1.57079632679489661923 \
         M_PI=3.14159265358979323846

win32-msvc*:QMAKE_CXXFLAGS += /wd"4005"

#RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../x64/debug/ -llicored
    LIBS += -L$$PWD/../../QGIS3.2_x64/debug/lib/ -lqgis_core -lqgis_gui -lqgis_app
} else {
    LIBS += -L$$PWD/../../x64/release/ -llicore
    LIBS += -L$$PWD/../../QGIS3.2_x64/release/lib/ -lqgis_core -lqgis_gui -lqgis_app
}

LIBS += -L$$PWD/../../OSGeo4W64-3.2/lib/ -lgeos_c -lgdal_i
INCLUDEPATH += $$PWD/../../OSGeo4W64-3.2/include
INCLUDEPATH += $$PWD/../../QGIS3.2_x64/include
INCLUDEPATH += C:/OSGeo4W64/include

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../licore/core
INCLUDEPATH += $$PWD/../licore/geometry
INCLUDEPATH += $$PWD/../licore/globe
INCLUDEPATH += $$PWD/../licore/math
INCLUDEPATH += $$PWD/../licore/render
INCLUDEPATH += $$PWD/../licore/render/renderstates
INCLUDEPATH += $$PWD/../licore/scene
INCLUDEPATH += $$PWD/../licore/sceneloader
INCLUDEPATH += $$PWD/../licore/tileset
INCLUDEPATH += $$PWD/../licore/tree

HEADERS += \
    liextrasglobal.h \
    arcgistilingscheme.h \
    gisimageryprovider.h \
    wmsimageryprovider.h \
    transformhelper.h \
    liquadtreetileset.h \
    litreelayer.h \
    livectorlayer.h \
    liheatmaplayer.h \
    liprovidermanager.h \
    lipluginimageryprovider.h \
    liproviderinterface.h \
    qgsmapprojection.h \
    pmtscapabilities.h

SOURCES += \
    arcgistilingscheme.cpp \
    gisimageryprovider.cpp \
    wmsimageryprovider.cpp \
    transformhelper.cpp \
    liquadtreetileset.cpp \
    litreelayer.cpp \
    livectorlayer.cpp \
    liheatmaplayer.cpp \
    liprovidermanager.cpp \
    lipluginimageryprovider.cpp \
    qgsmapprojection.cpp \
    pmtscapabilities.cpp

RESOURCES += \
    extras.qrc

include(providers/arcgisrest/arcgisrest.pri)
include(providers/wms/wms.pri)
