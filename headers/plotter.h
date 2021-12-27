#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QStack>
#include "qcustomplot.h"

class Plotter : public QObject
{
    Q_OBJECT

private:
    inline static Plotter* plotterSingleton;
    QString function_str;

    Plotter(QString str);

    void eval(QStack<double> &operands, QChar opr);

public:
    static Plotter* getPlotter(QString function_str = "");

    void validate();

    void plot(QCustomPlot* plotWidget, double from_x, double to_x, double from_fun, double to_fun, int points_no);

    double evaluate(QString function_str, double varValue);
};

class ExpressionException : public QException{
public:
    QString msg;
    ExpressionException(QString msg=""){
        this->msg = msg;
    }
};

#endif // PLOTTER_H
