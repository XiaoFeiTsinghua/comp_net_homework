#-------------------------------------------------
#
# Project created by QtCreator 2014-11-29T13:12:00
#
#-------------------------------------------------

QT       += core gui
QT += network widgets
QT += multimedia multimediawidgets
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_tcp_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    file_server.cpp \
    file_client.cpp \
    interface.cpp \
    online_video.cpp \
    MatToQImage.cpp \
    choosewidget.cpp \
    friendlistwidget.cpp \
    friendwidget.cpp \
    headbutton.cpp \
    logindialog.cpp \
    user.cpp \
    widget.cpp \
    chatdialog.cpp \
    textedit_new.cpp

HEADERS  += mainwindow.h \
    file_server.h \
    file_client.h \
    interface.h \
    online_video.h \
    MatToQImage.h \
    choosewidget.h \
    friendlistwidget.h \
    friendwidget.h \
    headbutton.h \
    logindialog.h \
    user.h \
    widget.h \
    chatdialog.h \
    textedit_new.h

FORMS    += mainwindow.ui \
    file_server.ui \
    file_client.ui \
    interface.ui \
    online_video.ui \
    widget.ui \
    server.ui \
    chatdialog.ui

INCLUDEPATH += D:\software\OpenCV\bin32\install\include \
                D:\software\OpenCV\bin32\install\include\opencv \
                D:\software\OpenCV\bin32\install\include\opencv2

LIBS += -L"D:\software\OpenCV\bin32\install\x64\mingw\bin"
LIBS += -lopencv_core249 -lopencv_highgui249 -lopencv_imgproc249

RESOURCES += \
    main.qrc

OTHER_FILES += \
    chats_chosen.jpg \
    chats_not_chosen.jpg \
    friends_chosen.jpg \
    friends_not_chosec.jpg \
    groups_chosen.jpg \
    groups_not_chosen.jpg \
    logo.jpg \
    photo.jpg \
    photo_gjq.jpg \
    tray.jpg \
    close.png \
    min.png
