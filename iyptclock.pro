# -------------------------------------------------
# Project created by QtCreator 2010-06-10T14:15:18
# -------------------------------------------------
QT += core \
    gui \
    widgets \
    concurrent \
    svg \
    svgwidgets \
    network
TARGET = iyptclock
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    themeclock.cpp \
    listcontroller.cpp \
    broadcastserver.cpp \
    stagelistmodel.cpp \
    qresizablelabel.cpp \
    autosave.cpp \
    aboutdialog.cpp
HEADERS += mainwindow.h \
    themeclock.h \
    listcontroller.h \
    broadcastserver.h \
    stagelistmodel.h \
    qresizablelabel.h \
    autosave.h \
    aboutdialog.h
FORMS += mainwindow.ui \
    aboutdialog.ui
INCLUDEPATH += /opt/local/include/
include(themeclockwidget.pri)

OTHER_FILES += \
    iclocklogo.svg \
    iclocklogo-64x64.png

RESOURCES += \
    resources.qrc
