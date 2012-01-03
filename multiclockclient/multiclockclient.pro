#-------------------------------------------------
#
# Project created by QtCreator 2012-01-03T19:29:21
#
#-------------------------------------------------

QT       += core gui

TARGET = multiclockclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../themeclockwidget.cpp \
    multibroadcastclient.cpp

HEADERS  += \
    ../themeclockwidget.h \
    mainwindow.h \
    multibroadcastclient.h

FORMS    += mainwindow.ui
