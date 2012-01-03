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
    ../iyptclockclient/broadcastclient.cpp

HEADERS  += \
    ../themeclockwidget.h \
    mainwindow.h \
    ../iyptclockclient/broadcastclient.h

FORMS    += mainwindow.ui
