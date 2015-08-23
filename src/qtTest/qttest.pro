#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T15:55:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qttest
TEMPLATE = app


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

}else{
DESTDIR = $$PWD/../../bin/$${RELDIR}/
}

INCLUDEPATH +=$$PWD/../../include
unix{

}else{
LIBS += -L$$PWD/../../bin/$${RELDIR} -lofferAudioDataCInterface
}
