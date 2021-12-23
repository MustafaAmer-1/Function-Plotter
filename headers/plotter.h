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

    bool isBinaryOp(QChar e);
    bool isSign(QChar e);
    bool isValidOperand(QChar e);

public:
    static Plotter* getPlotter(QString function_str = "");

    bool validate();
};

#endif // PLOTTER_H
