QT += widgets qml qml-private quick core-private opengl network xml concurrent quickwidgets sql

TEMPLATE = app
TARGET = testapp

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/../../x64/debug
} else {
    DESTDIR = $$PWD/../../x64/release
}

DEFINES +=  _UNICODE \
            CORE_EXPORT=__declspec(dllimport)\
            M_PI_2=1.57079632679489661923 \
            M_PI=3.14159265358979323846

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../x64/debug/ -llicored -lliextrasd
    LIBS += -L$$PWD/../../QGIS3.2_x64/debug/lib -lqgis_core
} else {
    LIBS += -L$$PWD/../../x64/release/ -llicore -lliextras
    LIBS += -L$$PWD/../../QGIS3.2_x64/release/lib -lqgis_core
}

INCLUDEPATH += $$PWD/../../QGIS3.2_x64/include

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../liextras

SOURCES += \
    main.cpp \
    sample.cpp

HEADERS += \
    sample.h
