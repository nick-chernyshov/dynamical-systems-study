#-------------------------------------------------
#
# Project created by QtCreator 2014-05-24T22:05:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = mode-chart
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += mode-chart/mode_chart.cpp \
    systems/lorenzExt.cpp \
    mode-chart/mode_chart.cpp

HEADERS += \
    plot/contourplot.h \
    vector/state.h \
    vector/params.h \
    vector/linearalgebra.h \
    vector/equations.h \
    vector/build_consts.h \
    systems/lorenzExt.h \
    mode-chart/mode_computer.h \
    mode-chart/mode-plot.h
