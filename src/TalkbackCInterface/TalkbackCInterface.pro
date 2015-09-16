#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T14:24:47
#
#-------------------------------------------------

QT       -= core gui

TARGET = TalkbackCInterface
TEMPLATE = lib

DEFINES += TALKBACKCINTERFACE_LIBRARY

SOURCES += \
    TalkbackCInterface.cpp

HEADERS += \
    ../../include/TalkbackCInterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
INCLUDEPATH +=$$PWD/../../include
INCLUDEPATH +=$$PWD/../common
INCLUDEPATH +=$$PWD/../Talkback
CONFIG(release, debug|release){
RELDIR = release
}else{
RELDIR = debug
}
unix{
DESTDIR = /home/talkback/bin/$${RELDIR}
}else{
DESTDIR = $$PWD/../../bin/$${RELDIR}/
}
unix{
LIBS += -L/home/talkback/bin/$${RELDIR}/ -lTalkback
}else{
LIBS += -L$$PWD/../../bin/$${RELDIR}/ -lTalkback
}
