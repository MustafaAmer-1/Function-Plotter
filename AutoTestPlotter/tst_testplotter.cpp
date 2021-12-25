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

    QTest::newRow("valid exp") << "x^2+5.2*x+35.32*12*x+70" << true;
    QTest::newRow("statring wrong")     << "*x+5" << false;
    QTest::newRow("ending wrong") << "x+5*" << false;
    QTest::newRow("middle wrong") << "x^9+50x++95*2*x+702" << false;
    QTest::newRow("sign test 1") << "-x" << true;
    QTest::newRow("sign test 2") << "x" << true;
    QTest::newRow("sign test 3") << "+15" << true;
    QTest::newRow("sign test 4") << "+x" << true;
    QTest::newRow("sign test 5") << "2*-x" << true;
    QTest::newRow("sign test 6") << "-x/556" << true;
    QTest::newRow("sign test 7") << "-*x" << false;
    QTest::newRow("sign test 8") << "*x" << false;
    QTest::newRow("sign test 9") << "*" << false;
    QTest::newRow("sign test 10") << "y-x" << false;
    QTest::newRow("empty") << "" << true;
    QTest::newRow("brackets test 1") << "(x*2)" << true;
    QTest::newRow("brackets test 2") << "({5*x+20}*[202*x+13])*1/x" << true;
    QTest::newRow("brackets test 3") << "({5*x+20}*[+202*y+13])*1/x" << false;
    QTest::newRow("brackets test 4") << "({5*x+20}*[202*x+13*])*1/x" << false;
    QTest::newRow("invalid operand 1") << "x2222" << false;
    QTest::newRow("invalid operand 2") << "xx5" << false;
    QTest::newRow("invalid operand 3") << "x%2222" << false;
    QTest::newRow("invalid operand 4") << "#x-2222" << false;
}

QTEST_APPLESS_MAIN(TestPlotter)

#include "tst_testplotter.moc"
