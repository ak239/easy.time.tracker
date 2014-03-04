#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T22:02:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = time-tracker
TEMPLATE = app


SOURCES += main.cpp\
        trackerwindow.cpp \
    currentwindow.cpp \
    typedialog.cpp \
    autotypedialog.cpp \
    addautotypedialog.cpp \
    ltypesdialog.cpp \
    onetypedialog.cpp

HEADERS  += trackerwindow.h \
    currentwindow.h \
    typedialog.h \
    autotypedialog.h \
    addautotypedialog.h \
    ltypesdialog.h \
    onetypedialog.h

FORMS    += trackerwindow.ui \
    typedialog.ui \
    autotypedialog.ui \
    addautotypedialog.ui \
    ltypesdialog.ui \
    onetypedialog.ui
