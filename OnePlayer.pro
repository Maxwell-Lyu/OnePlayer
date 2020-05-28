# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

QT       += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT	+= multimedia

TEMPLATE = app
TARGET = OnePlayer

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += \
    static

HEADERS += \
    include/OnePlayer.h \
    include/CoverWidget.h \
    include/LyricWidget.h
SOURCES += \
    src/CoverWidget.cpp \
    src/OnePlayer.cpp \
    src/main.cpp \
    src/LyricWidget.cpp
FORMS += src/OnePlayer.ui
RESOURCES += OnePlayer.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/lib/ -ltag -lz

INCLUDEPATH += \
    $$PWD/include \
    /usr/lib/gcc/x86_64-linux-gnu/9/include/

DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libtag.a

DISTFILES += \
    src/OnePlayer.qss
