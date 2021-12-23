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

bool Plotter::isBinaryOp(QChar e){
    return (e == '*' || e == '/' || e == '^');
}

bool Plotter::isSign(QChar e){
    return (e == '-' || e == '+');
}

bool Plotter::isValidOperand(QChar e){
    return e.isDigit() || e == 'x';
}

bool Plotter::validate(){
    if(isExpValid) return 1;
    if(function_str.size() < 3){
        if(function_str.size() == 0) return isExpValid = 1;
        else if(function_str.size() == 1) return isExpValid = (function_str[0].isDigit() || function_str[0] == 'x');
        else return isExpValid = (isSign(function_str[0]) && (function_str[1].isDigit() || function_str[1] == 'x'));
    }
    if(Plotter::isBinaryOp(function_str[0]) || Plotter::isBinaryOp(function_str.back()) || Plotter::isSign(function_str.back())) return isExpValid = 0;

    for(int i = 1; i < function_str.size(); i++){
        if(Plotter::isBinaryOp(function_str[i])){
            if(!isValidOperand(function_str[i-1]) || (!isValidOperand(function_str[i+1]) && !isSign(function_str[i+1])))
                return isExpValid = 0;
        }
        else if(isSign(function_str[i])){
            if((!isValidOperand(function_str[i-1]) && !isBinaryOp(function_str[i-1])) || !isValidOperand(function_str[i+1]))
                return isExpValid = 0;
        }
    }
    return isExpValid = 1;
}
