#-------------------------------------------------
#
# Project created by QtCreator 2014-05-11T17:31:09
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = torus-chart
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += torus/torus-chart-main.cpp \
    systems/vpd3ringbaseds.cpp \
    systems/vdpx3extbase.cpp \
    systems/vdpx2extbase.cpp \
    systems/vdp3ringds.cpp \
    systems/vdp3phaseds.cpp \
    systems/vdp3ExtDS.cpp \
    systems/vdp3baseds.cpp

HEADERS += torus/windingnumbers.h \
    plot/contourplot.h \
    systems/vpd3ringbaseds.h \
    systems/vdpx3extbase.h \
    systems/vdpx2extbase.h \
    systems/vdp3ringds.h \
    systems/vdp3phaseds.h \
    systems/vdp3ExtDS.h \
    systems/vdp3baseds.h \
    vector/state.h \
    vector/params.h \
    vector/linearalgebra.h \
    vector/equations.h \
    vector/build_consts.h \
    torus/toruschart.h
