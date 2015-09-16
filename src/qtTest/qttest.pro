#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T15:55:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qttest
TEMPLATE = app
CONFIG +=console

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

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

INCLUDEPATH +=$$PWD/../../include
unix{
LIBS += -L$$/home/talkback/bin/$${RELDIR}/ -lofferAudioDataCInterface
LIBS += -L$$/home/talkback/bin/$${RELDIR}/ -lTalkbackCInterface
}else{
LIBS += -L$$PWD/../../bin/$${RELDIR} -lofferAudioDataCInterface
LIBS += -L$$PWD/../../bin/$${RELDIR} -lTalkbackCInterface
}
