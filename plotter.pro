#-------------------------------------------------
#
# Project created by QtCreator 2013-10-20T19:13:56
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = plotter
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    coordinate_system.cpp \
    f.cpp \
    render_thread.cpp \
    render_widget.cpp

HEADERS  += widget.h \
    f.h \
    coordinate_system.h \
    render_thread.h \
    render_widget.h

QMAKE_CXXFLAGS +=-fopenmp
QMAKE_LFLAGS += -fopenmp
