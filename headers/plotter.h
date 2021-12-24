#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>

class Plotter : public QObject
{
    Q_OBJECT

private:
    inline static Plotter* plotterSingleton;
    QString function_str;
    bool isExpValid;

    Plotter(QString str);

    bool checkBrackets(QString str);

public:
    static Plotter* getPlotter(QString function_str = "");

    bool validate();

    void plot(double from_x, double to_x, double from_fun, double to_fun);
};

#endif // PLOTTER_H
