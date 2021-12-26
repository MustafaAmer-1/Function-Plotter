QT += testlib
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../headers/
INCLUDEPATH += ../../lib/

SOURCES +=  tst_testplotter.cpp

HEADERS += \
    ../../headers/plotter.h \
    ../../lib/qcustomplot.h

SOURCES += \
    ../../src/plotter.cpp \
    ../../lib/qcustomplot.cpp
