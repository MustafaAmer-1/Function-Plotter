#include "plotter.h"
#include <QStack>

#define openingBr(x) (x == '(' || x == '{' || x == '[')
#define closingBr(x) (x == ')' || x == '}' || x == ']')

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

    if(!checkBrackets(function_str)) return isExpValid = 0;
    QString function_str_nb = "";
    for (int i = 0; i < function_str.size(); i++){
        if(openingBr(function_str[i])){
            if(i > 0 && !isSign(function_str[i-1]) && !isBinaryOp(function_str[i-1]) && !openingBr(function_str[i-1])) return isExpValid = 0;
            if(!isSign(function_str[i+1]) && !isValidOperand(function_str[i+1]) && !openingBr(function_str[i+1])) return isExpValid = 0;
        }
        else if(closingBr(function_str[i])){
            if(!isValidOperand(function_str[i-1]) && !closingBr(function_str[i-1])) return isExpValid = 0;
            if(i < function_str.size()-1 && !isSign(function_str[i+1]) && !isBinaryOp(function_str[i+1]) && !closingBr(function_str[i+1])) return isExpValid = 0;
        }
        else function_str_nb += function_str[i];
    }
    if(function_str_nb.size() < 3){
        if(function_str_nb.size() == 0) return isExpValid = 1;
        else if(function_str_nb.size() == 1) return isExpValid = (function_str_nb[0].isDigit() || function_str_nb[0] == 'x');
        else return isExpValid = (isSign(function_str_nb[0]) && (function_str_nb[1].isDigit() || function_str_nb[1] == 'x'));
    }
    if(Plotter::isBinaryOp(function_str_nb[0]) || Plotter::isBinaryOp(function_str_nb.back()) || Plotter::isSign(function_str_nb.back())) return isExpValid = 0;

    for(int i = 1; i < function_str_nb.size(); i++){
        if(Plotter::isBinaryOp(function_str_nb[i])){
            if(!isValidOperand(function_str_nb[i-1]) || (!isValidOperand(function_str_nb[i+1]) && !isSign(function_str_nb[i+1])))
                return isExpValid = 0;
        }
        else if(isSign(function_str_nb[i])){
            if((!isValidOperand(function_str_nb[i-1]) && !isBinaryOp(function_str_nb[i-1])) || !isValidOperand(function_str_nb[i+1]))
                return isExpValid = 0;
        }
    }
    return isExpValid = 1;
}

bool Plotter::checkBrackets(QString str){
    QStack<QChar> stack;
    for (int i = 0; i < str.size(); i++){
        if(openingBr(str[i])) stack.push(str[i]);
        else if(closingBr(str[i])){
            if(stack.size() == 0) return 0;
            if(str[i] == ')' && stack.top() == '(') stack.pop();
            else if(str[i] == '}' && stack.top() == '{') stack.pop();
            else if(str[i] == ']' && stack.top() == '[') stack.pop();
            else return 0;
        }
    }
    return stack.empty();
}
