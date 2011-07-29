# -------------------------------------------------
# Project created by QtCreator 2010-06-10T14:15:18
# -------------------------------------------------
QT += svg \
    phonon \
    network
TARGET = iyptclock
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    themeclock.cpp \
    listcontroller.cpp \
    broadcastserver.cpp
HEADERS += mainwindow.h \
    themeclock.h \
    listcontroller.h \
    broadcastserver.h
FORMS += mainwindow.ui
include(themeclockwidget.pri)
