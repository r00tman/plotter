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
    ast.cpp \
    text_stream.cpp \
    token_reader.cpp \
    aggregate_node.cpp

HEADERS  += widget.h \
    ast.h \
    text_stream.h \
    token_reader.h \
    aggregate_node.h
