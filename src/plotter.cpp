#include "plotter.h"

Plotter::Plotter(QString str)
{
    this->function_str = str;
    isExpValid = 0;
}

Plotter* Plotter::getPlotter(QString function_str){
    if(!plotterSingleton)
        plotterSingleton = new Plotter(function_str);
    else{
        plotterSingleton->function_str = function_str;
        plotterSingleton->isExpValid = 0;
    }

    return plotterSingleton;
}

bool Plotter::isExpression(QChar e){
    if(e == '+' || e == '-' || e == '*' || e == '/' || e == '^') return 1;
    return 0;
}

bool Plotter::validate(){
    if(isExpValid) return 1;
    if(function_str.size() < 3) return isExpValid = 0;
    if(Plotter::isExpression(function_str[0]) || Plotter::isExpression(function_str.back())) return isExpValid = 0;

    for(int i = 1; i < function_str.size(); i++){
        if(Plotter::isExpression(function_str[i])){
            if((!function_str[i-1].isDigit() && function_str[i-1]!='x') || (!function_str[i+1].isDigit() && function_str[i+1]!='x'))
                return isExpValid = 0;
        }
    }
    return isExpValid = 1;
}
