TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

HEADERS += \
    lyapunov/contourplotlyap.h \
    lyapunov/lyapunov.h \
    systems/vdp3baseds.h \
    systems/vdp3phaseds.h \
    systems/vdp3ringds.h \
    systems/vdpx2extbase.h \
    systems/vdpx3extbase.h \
    systems/vpd3ringbaseds.h \
    vector/build_consts.h \
    vector/equations.h \
    vector/linearalgebra.h \
    vector/params.h \
    vector/state.h \
    plot/contourplot.h \
    systems/vdp3ExtDS.h

SOURCES += \
    lyapunov/lyapunov-chart.cpp \
    systems/vdp3baseds.cpp \
    systems/vdp3phaseds.cpp \
    systems/vdp3ringds.cpp \
    systems/vdpx2extbase.cpp \
    systems/vdpx3extbase.cpp \
    systems/vpd3ringbaseds.cpp \
    systems/vdp3ExtDS.cpp


