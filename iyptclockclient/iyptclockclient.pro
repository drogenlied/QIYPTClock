#-------------------------------------------------
#
# Project created by QtCreator 2011-07-30T18:55:26
#
#-------------------------------------------------

QT       += core gui network

TARGET = iyptclockclient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../themeclockwidget.cpp \
    broadcastclient.cpp

HEADERS  += mainwindow.h \
    ../themeclockwidget.h \
    broadcastclient.h

FORMS    += mainwindow.ui

OTHER_FILES +=

INCLUDEPATH += ..

RESOURCES += \
    ../resources.qrc
