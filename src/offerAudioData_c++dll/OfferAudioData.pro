#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T15:02:24
#
#-------------------------------------------------

QT       -= core gui

TARGET = OfferAudioData
TEMPLATE = lib
CONFIG +=console
DEFINES += OFFERAUDIODATA_LIBRARY

SOURCES += offeraudiodata.cpp \
    ../common/talkbacklock.cpp \
    ../common/talkbackthread.cpp \
    audiocode.cpp \
    g711.cpp \
    g711_2.cpp \
    talkbackaudiodatacapture.cpp

HEADERS += offeraudiodata.h\
        offeraudiodata_global.h \
    ../common/TalkBackCommonTool.h \
    ../common/talkbacklock.h \
    ../common/talkbackthread.h \
    audiocode.h \
    g711.h \
    g711_2.h \
    talkbackaudiodatacapture.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH +=$$PWD/../common
INCLUDEPATH +=$$PWD/../../include
INCLUDEPATH += $$PWD/../openal/include

unix{

}else{
LIBS += -L$$PWD/../openal-qt -lOpenAL32
}

CONFIG(release, debug|release){
RELDIR = release
}else{
RELDIR = debug
}
unix{

}else{
DESTDIR = $$PWD/../../bin/$${RELDIR}/
}
