#-------------------------------------------------
#
# Project created by QtCreator 2012-01-03T19:29:21
#
#-------------------------------------------------

QT       += core gui network

TARGET = multiclockclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../themeclockwidget.cpp \
    multibroadcastclient.cpp \
    signalhelper.cpp \
    sockethelper.cpp

HEADERS  += \
    ../themeclockwidget.h \
    mainwindow.h \
    multibroadcastclient.h \
    signalhelper.h \
    sockethelper.h

FORMS    += mainwindow.ui

RESOURCES += \
    ../resources.qrc
