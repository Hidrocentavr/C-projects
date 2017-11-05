#-------------------------------------------------
#
# Project created by QtCreator 2017-09-23T19:29:13
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = KinematicTask
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    matrix.cpp

HEADERS += \
    matrix.h \
    list.h

QMAKE_CXXFLAGS += -std=c++0x
