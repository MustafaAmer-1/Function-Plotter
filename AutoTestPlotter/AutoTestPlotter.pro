QT += testlib
QT -= gui

CONFIG += c++11

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../headers/

SOURCES +=  tst_testplotter.cpp

HEADERS += \
    ../../headers/plotter.h

SOURCES += \
    ../../src/plotter.cpp
