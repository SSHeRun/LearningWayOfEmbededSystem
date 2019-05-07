#-------------------------------------------------
#
# Project created by QtCreator 2019-04-02T15:21:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += network
QT += sql

TARGET = MyStockByThrinity
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pricedialog.cpp \
    settingsdlg.cpp \
    ftpclient.cpp

HEADERS  += mainwindow.h \
    pricedialog.h \
    settingsdlg.h \
    ftpclient.h

FORMS    += mainwindow.ui \
    pricedialog.ui \
    settingsdlg.ui
