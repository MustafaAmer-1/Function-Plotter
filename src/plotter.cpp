#include "plotter.h"

Plotter::Plotter(QString str)
{
    this->function_str = str;
}

Plotter* Plotter::getPlotter(QString function_str){
    if(!plotterSingleton)
        plotterSingleton = new Plotter(function_str);
    else plotterSingleton->function_str = function_str;

    return plotterSingleton;
}
