#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>

class Plotter : public QObject
{
    Q_OBJECT

private:
    inline static Plotter* plotterSingleton;
    QString function_str;

    Plotter(QString str);

public:
    static Plotter* getPlotter(QString function_str = "");
};

#endif // PLOTTER_H
