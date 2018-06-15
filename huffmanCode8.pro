TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cc \
    huffmancode.cc \
    binnode.cc

HEADERS += \
    huffmancode.h \
    binnode.h
