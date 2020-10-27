#-------------------------------------------------
#
# Project created by QtCreator 2017-07-15T09:15:47
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_cngwrapperunittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    testasymmetricsignature.cpp \
    testalgorithmIdentifiercollection.cpp \
    testntstatushelper.cpp \
    testhash.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../CngWrapper/release/ -lCngWrapper
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../CngWrapper/debug/ -lCngWrapper
else:unix: LIBS += -L$$OUT_PWD/../CngWrapper/ -lCngWrapper

INCLUDEPATH += $$PWD/../CngWrapper
DEPENDPATH += $$PWD/../CngWrapper

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/release/libCngWrapper.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/debug/libCngWrapper.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/release/CngWrapper.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/debug/CngWrapper.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../CngWrapper/libCngWrapper.a

HEADERS += \
    testalgorithmidentifiercollection.h \
    testasymmetricsignature.h \
    testntstatushelper.h \
    testhash.h

win32: LIBS += -lbcrypt
