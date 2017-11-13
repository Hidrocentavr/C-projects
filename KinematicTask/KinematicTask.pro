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
    matrix.cpp \
    gazebo.cpp

HEADERS += \
    matrix.h \
    list.h

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += /usr/local/include/gazebo-9/
DEPENDPATH += /usr/local/include/gazebo-9/

INCLUDEPATH += /usr/include/ignition/math3/
DEPENDPATH += /usr/include/ignition/math3/

INCLUDEPATH += /usr/include/ignition/transport3/
DEPENDPATH += /usr/include/ignition/transport3/

INCLUDEPATH += /usr/include/ignition/msgs0/
DEPENDPATH += /usr/include/ignition/msgs0/

INCLUDEPATH += /usr/include/sdformat-5.2/
DEPENDPATH += /usr/include/sdformat-5.2/
