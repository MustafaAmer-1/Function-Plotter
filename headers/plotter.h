/**
 * @file plotter.h
 * @author Mustafa Amer (eng.MustafaAmer0@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QStack>
#include "qcustomplot.h"

/**
 * @brief Plotter class signature
 * This is a singleton class responsible for validating the function expression,
 * evaluating and plotting the graph ponits.
 * 
 */
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

/**
 * @brief This is a class exception used to report any invalid function expression
 * with useful message for the user.
 * 
 */
class ExpressionException : public QException{
public:
    QString msg;
    /**
     * @brief Construct a new Expression Exception object
     * 
     * @param msg - the message reported for the user
     */
    ExpressionException(QString msg=""){
        this->msg = msg;
    }
};

#endif // PLOTTER_H
