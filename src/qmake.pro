TEMPLATE = app
TARGET = SmartCalc

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/controller/credit.cpp \
    ../src/model/credit_model.cpp \
    ../src/controller/deposit.cpp \
    ../src/model/deposit_model.cpp \
    ../src/controller/facade.cpp \
    ../src/main.cpp \
    ../src/controller/mainwindow.cpp \
    ../src/model/model.cpp \
    ../src/controller/plotwindow.cpp \
    ../src/temp/qcustomplot.cpp

HEADERS += \
    ../src/controller/credit.h \
    ../src/model/credit_model.h \
    ../src/controller/deposit.h \
    ../src/model/deposit_model.h \
    ../src/controller/facade.h \
    ../src/controller/mainwindow.h \
    ../src/model/model.h \
    ../src/controller/plotwindow.h \
    ../src/temp/qcustomplot.h \
    ../src/temp/temp.h

FORMS += \
    ../src/view/credit.ui \
    ../src/view/deposit.ui \
    ../src/view/mainwindow.ui \
    ../src/view/plotwindow.ui

ICON = ../src/icon.icns