#-------------------------------------------------
#
# Project created by QtCreator 2017-07-19T17:58:34
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_cngwrapperintegratedtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    testintegration.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    testintegration.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CngWrapper/release/ -lCngWrapper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CngWrapper/debug/ -lCngWrapper

INCLUDEPATH += $$PWD/../CngWrapper
DEPENDPATH += $$PWD/../CngWrapper

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/release/libCngWrapper.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/debug/libCngWrapper.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/release/CngWrapper.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/debug/CngWrapper.lib

win32: LIBS += -lbcrypt
