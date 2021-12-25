#include "plotter.h"
#include <QStack>

#define openingBr(x) (x == '(' || x == '{' || x == '[')
#define closingBr(x) (x == ')' || x == '}' || x == ']')
#define isBinaryOp(e) (e == '*' || e == '/' || e == '^')
#define isSign(e) (e == '-' || e == '+')
#define isValidOperand(e) (e.isDigit() || e == 'x' || e == '.')
#define equvBr(e) (e == ')') ? '(' : (e == '}')? '{' : '['
#define priority(e) (e=='^')? 2 : (e=='*' || e=='/')? 1 : 0

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
    if(isBinaryOp(function_str_nb[0]) || isBinaryOp(function_str_nb.back()) || isSign(function_str_nb.back())
            || (!isValidOperand(function_str_nb[0]) && !isSign(function_str_nb[0])) || (function_str_nb[0] == 'x' && function_str_nb[1].isDigit())) return isExpValid = 0;

    for(int i = 1; i < function_str_nb.size(); i++){
        if(isBinaryOp(function_str_nb[i])){
            if(!isValidOperand(function_str_nb[i-1]) || (i < function_str_nb.size()-1 && !isValidOperand(function_str_nb[i+1]) && !isSign(function_str_nb[i+1])))
                return isExpValid = 0;
        }
        else if(isSign(function_str_nb[i])){
            if((!isValidOperand(function_str_nb[i-1]) && !isBinaryOp(function_str_nb[i-1])) || (i < function_str_nb.size()-1 && !isValidOperand(function_str_nb[i+1])))
                return isExpValid = 0;
        }
        else if(!isValidOperand(function_str_nb[i])) return isExpValid = 0;
        else if(function_str_nb[i] == 'x' && (function_str_nb[i-1].isDigit() || (i < function_str_nb.size()-1 && function_str_nb[i+1].isDigit()))) return isExpValid = 0;
    }
    return isExpValid = 1;
}

bool Plotter::checkBrackets(QString str){
    QStack<QChar> stack;
    for (int i = 0; i < str.size(); i++){
        if(openingBr(str[i])) stack.push(str[i]);
        else if(closingBr(str[i])){
            if(stack.size() == 0) return 0;
            if(equvBr(str[i]) == stack.top()) stack.pop();
            else return 0;
        }
    }
    return stack.empty();
}

void Plotter::plot(double from_x, double to_x, double from_fun, double to_fun){

}

double Plotter::eval(double opd1, double opd2, QChar opr){
    if(opr == '+') return opd1+opd2;
    if(opr == '-') return opd1-opd2;
    if(opr == '*') return opd1*opd2;
    if(opr == '/') return opd1/opd2;
    return qPow(opd1, opd2);
}

double Plotter::evaluate(QString str, int varValue){
    QStack<double> operands;
    QStack<QChar> ops;

    for (int i = 0; i < str.size(); i++) {
        if(str[i].isDigit()){
            double val = 0;
            bool lft = 1;
            int cnt = 1;
            while(i < str.size() && (str[i].isDigit() || str[i] == '.')){
                if(str[i] != '.' && lft) val = val*10 + str[i].unicode() - '0';
                else if(str[i] == '.') lft = 0;
                else{
                    val += (str[i].unicode() - '0') / (cnt*10.0);
                }
                i++;
            }
            i--;
            operands.push(val);
        }
        else if(str[i] == 'x') operands.push(varValue);
        else if(openingBr(str[i])) ops.push(str[i]);
        else if(closingBr(str[i])){
            QChar b = equvBr(str[i]);
            while(ops.top() != b){
                double operand2 = operands.top();
                operands.pop();
                double operand1 = operands.top();
                operands.pop();
                double res = eval(operand1, operand2, ops.top());
                ops.pop();
                operands.push(res);
            }
            ops.pop();
        }
        else{
            int pr = priority(str[i]);
            if(!ops.isEmpty()){
                while(!ops.isEmpty()){
                    int topPr = priority(ops.top());
                    if(pr > topPr || openingBr(ops.top())) break;
                    double operand2 = operands.top();
                    operands.pop();
                    double operand1 = operands.top();
                    operands.pop();
                    double res = eval(operand1, operand2, ops.top());
                    ops.pop();
                    operands.push(res);
                }
            }
            ops.push(str[i]);
        }
    }

    while(!ops.isEmpty()){
        double operand2 = operands.top();
        operands.pop();
        double operand1 = operands.top();
        operands.pop();
        double res = eval(operand1, operand2, ops.top());
        ops.pop();
        operands.push(res);
    }

    return operands.top();
}
