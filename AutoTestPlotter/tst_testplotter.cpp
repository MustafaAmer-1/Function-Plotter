#include <QtTest>

// add necessary includes here
#include "plotter.h"

class TestPlotter : public QObject
{
    Q_OBJECT
};

QTEST_APPLESS_MAIN(TestPlotter)

#include "tst_testplotter.moc"
