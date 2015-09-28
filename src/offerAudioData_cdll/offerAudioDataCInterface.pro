#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T15:13:08
#
#-------------------------------------------------

QT       -= core gui

TARGET = offerAudioDataCInterface
TEMPLATE = lib

DEFINES += OFFERAUDIODATACINTERFACE_LIBRARY

SOURCES += \
    AudioData.cpp

HEADERS += \
    ../../include/AudioData.h \
    ../../include/TalkBackDataTypeCommon.h \
    ../../include/TalkbackInterfaceCommon.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH +=$$PWD/../../include
INCLUDEPATH +=$$PWD/../common
INCLUDEPATH +=$$PWD/../offerAudioData_c++dll


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
LIBS += -L$$/home/talkback/bin/$${RELDIR}/ -lOfferAudioData
}else{
LIBS += -L$$PWD/../../bin/$${RELDIR}/ -lOfferAudioData
}
