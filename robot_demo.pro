#-------------------------------------------------
#
# Project created by QtCreator 2017-01-13T15:11:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11

TARGET = robot_demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    irobotcreate.cpp \
    rplidar.cpp \
    global_planner.cpp

HEADERS  += mainwindow.h \
    irobotcreate.h \
    rplidar.h \
    navigation.h \
    lidar.h \
    grid_map.h \
    definitions.h \
    global_planner.h \
    mapping.h

FORMS    += mainwindow.ui
