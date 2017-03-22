#-------------------------------------------------
#
# Project created by QtCreator 2016-09-25T17:32:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LyricDetective
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    invertedindex.cpp \
    lrctotxt.cpp \
    vectorspacemodel.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    invertedindex.h \
    lrctotxt.h \
    vectorspacemodel.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    resources.qrc

RC_FILE = qrc.rc
