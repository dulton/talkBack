#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T15:27:47
#
#-------------------------------------------------

QT       -= core gui

TARGET = Talkback
TEMPLATE = lib

DEFINES += TALKBACK_LIBRARY

SOURCES += talkback.cpp \
    talkbackmanager.cpp \
    ../common/talkbacklock.cpp \
    talkbackcore.cpp

HEADERS += talkback.h\
        talkback_global.h \
    talkbackmanager.h \
    ../common/talkbacklock.h \
    talkbackcore.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
INCLUDEPATH +=$$PWD/../common
INCLUDEPATH +=$$PWD/../../include

CONFIG(release, debug|release){
RELDIR = release
}else{
RELDIR = debug
}
unix{

}else{
DESTDIR = $$PWD/../../bin/$${RELDIR}/
}
