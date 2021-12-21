#include <QtTest>

// add necessary includes here
#include "plotter.h"

class TestPlotter : public QObject
{
    Q_OBJECT

private slots:
    void validate();
    void validate_data();
};

void TestPlotter::validate()
{
    QFETCH(QString, expression);
    QFETCH(bool, validity);

    QCOMPARE(Plotter::getPlotter(expression)->validate(), validity);
}

void TestPlotter::validate_data(){
    QTest::addColumn<QString>("expression");
    QTest::addColumn<bool>("validity");

    QTest::newRow("valid exp") << "x^2+5x+35*12*x+70" << true;
    QTest::newRow("statring wrong")     << "*x+5" << false;
    QTest::newRow("ending wrong") << "x+5*" << false;
    QTest::newRow("middle wrong") << "x^9+50x++95*2*x+702" << false;
}

QTEST_APPLESS_MAIN(TestPlotter)

#include "tst_testplotter.moc"
