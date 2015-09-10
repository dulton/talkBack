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
    talkbackcore.cpp \
    ../common/talkbackthread.cpp \
    talkbackrtsp.cpp \
    talkbackrtp.cpp \
    ../common/sock.c \
    ../common/vlog.c \
    ../common/sdplib.c \
    ../common/_base64.c \
    ../common/authentication.c \
    ../common/_md5.c \
    talkbackrtcp.cpp \
    avt_rtspsocket.cpp

HEADERS += talkback.h\
        talkback_global.h \
    talkbackmanager.h \
    ../common/talkbacklock.h \
    talkbackcore.h \
    ../common/talkbackthread.h \
    talkbackrtsp.h \
    talkbackrtp.h \
    ../common/sock.h \
    ../common/gnu_win.h \
    talkbackrtspdef.h \
    ../common/vlog.h \
    ../common/sdplib.h \
    ../common/_base64.h \
    ../common/authentication.h \
    ../common/_md5.h \
    talkbackRtpDef.h \
    talkbackRtcpDef.h \
    talkbackrtcp.h \
    avt_rtspsocket.h

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
unix{

}else{
LIBS += -lws2_32

}
unix{

}else{
LIBS += -L$$PWD/../../bin/$${RELDIR} -lofferAudioDataCInterface
}
