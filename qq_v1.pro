#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T20:47:57
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qq_v1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    friendwidget.cpp \
    user.cpp \
    headbutton.cpp \
    choosewidget.cpp \
    logindialog.cpp

HEADERS  += widget.h \
    friendwidget.h \
    user.h \
    headbutton.h \
    choosewidget.h \
    logindialog.h

FORMS    += widget.ui

RESOURCES += \
    main.qrc
