QT += widgets qml qml-private quick core-private opengl network xml concurrent quickwidgets

TEMPLATE = app
TARGET = testapp

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../../x64/debug
    INCLUDEPATH += $$PWD/../../QGIS-Qt5VS2015x64/debug/include
} else {
    DESTDIR = $$PWD/../../x64/release
    INCLUDEPATH += $$PWD/../../QGIS-Qt5VS2015x64/release/include
}

win32:CONFIG(release, debug|release):{
    LIBS += -L$$PWD/../../x64/Release/ -llicore -lliextras\
        -L$$PWD/../../QGIS-Qt5VS2015x64/release/lib/ -lqgis_core -lqgis_gui -lqgis_app \
        -LC:/OSGeo4W64_2/lib/ -lqscintilla2 -lgeos_c -lgdal_i}
else:win32:CONFIG(debug, debug|release):{
    LIBS +=  -L$$PWD/../../x64/debug/ -llicored -lliextrasd\
        -L$$PWD/../../QGIS-Qt5VS2015x64/debug/lib/ -lqgis_core -lqgis_gui -lqgis_app\
        -LC:/OSGeo4W64_2/lib/ -lqscintilla2 -lgeos_c -lgdal_i}

DEFINES += _UNICODE \
         CORE_EXPORT=__declspec(dllimport)\
         M_PI_2=1.57079632679489661923 \
         M_PI=3.14159265358979323846

LIBS += -LC:/OSGeo4W64/lib/ -lqscintilla2 -lgeos_c -lgdal_i
INCLUDEPATH += C:/OSGeo4W64/include

INCLUDEPATH += $$PWD/../licore/include
INCLUDEPATH += $$PWD/../liextras

SOURCES += \
    main.cpp \
    sample.cpp

HEADERS += \
    sample.h
