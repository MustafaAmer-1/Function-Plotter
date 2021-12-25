#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include "qcustomplot.h"

class Plotter : public QObject
{
    Q_OBJECT

private:
    inline static Plotter* plotterSingleton;
    QString function_str;
    bool isExpValid;

    Plotter(QString str);

    bool checkBrackets(QString str);
    double eval(double opd1, double opd2, QChar opr);

public:
    static Plotter* getPlotter(QString function_str = "");

    bool validate();

    void plot(QCustomPlot* plotWidget, double from_x, double to_x, int points_no);

    double evaluate(QString function_str, double varValue);
};

#endif // PLOTTER_H
