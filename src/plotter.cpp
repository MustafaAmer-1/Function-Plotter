#include "plotter.h"

#define openingBr(x) (x == '(' || x == '{' || x == '[')
#define closingBr(x) (x == ')' || x == '}' || x == ']')
#define isBinaryOp(e) (e == '*' || e == '/' || e == '^')
#define isSign(e) (e == '-' || e == '+')
#define isValidOperand(e) (e.isDigit() || e == 'x' || e == '.')
#define equvBr(e) (e == ')') ? '(' : (e == '}')? '{' : '['
#define priority(e) (e=='@')? 3 : (e=='^')? 2 : (e=='*' || e=='/')? 1 : 0

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

void Plotter::validate(){
    bool op = 0;
    QStack<QChar> brackes;
    for (int i = 0; i < function_str.size(); i++) {
        QChar* c = &function_str[i];
        if(c->isDigit() || (*c == '.' && i<function_str.size()-1 && *(c+1)!='.')) op = 1;
        else if(*c == 'x'){
            if(i > 0 && ((c-1)->isDigit() || *(c-1) == 'x'))
                throw new ExpressionException("mistake in '" + function_str.mid(i-1, 2) + "'\nuse '*' for multiplication");
            if(i < function_str.size()-1 && ((c+1)->isDigit() || *(c+1) == 'x'))
                throw new ExpressionException("mistake in '" + function_str.mid(i, 2) + "'\nuse '*' for multiplication");
            op = 1;
        }
        else if(isBinaryOp(*c)){
            if(!op){
                if(i == 0)
                    throw new ExpressionException("exepression cannot start with " + function_str.left(1));
                throw new ExpressionException("mistake in '" + function_str.mid(i-1, 2) + "' at index " + QString::number(i-1));
            }
            op = 0;
        }
        else if(isSign(*c)){
            if(i == 0 || openingBr(*(c-1)) || isBinaryOp(*(c-1)) || isSign(*(c-1))) continue; //unary
            // if(!op) throw new ExpException("mistake in " + function_str.mid(i-1, 2));
            op = 0;
        }
        else if(openingBr(*c)){
            if(op) throw new ExpressionException("mistake in '" + function_str.mid(i-1, 2) + "'\nuse '*' for multiplication");
            brackes.push(*c);
        }
        else if(closingBr(*c)){
            QChar eq = equvBr(*c);
            if(!op){
                if(i == 0) throw new ExpressionException("mistake in bracket '" + function_str.left(1) + "' cannot start with closing braket");
                else throw new ExpressionException("mistake in '" + function_str.mid(i-1, 2) + "' at index " + QString::number(i-1));
            }
            if(brackes.empty() || eq != brackes.top())
                throw new ExpressionException("mistake in bracket '" + function_str.mid(i, 1) + "' at index " + QString::number(i));
            if(i<function_str.size()-1 && !isBinaryOp(*(c+1)) && !isSign((*(c+1))) && !closingBr(*(c+1)))
                throw new ExpressionException("mistake in '" + function_str.mid(i, 2) + + "'\nuse '*' for multiplication");
            brackes.pop();
        }
        else throw new ExpressionException("Invalid Character '" + function_str.mid(i, 1) + "' at index " + QString::number(i));
    }
    if(!op) throw new ExpressionException("mistake in '" + function_str.right(2) + "' exepression cannot end with " + function_str.right(1));
    if(!brackes.empty())
        throw new ExpressionException("mistake in end of expression there is opening bracket '"+ QString(brackes.top()) + "' without closing one");
}

void Plotter::plot(QCustomPlot* plotWidget, double from_x, double to_x, double from_fun, double to_fun, int points_no){
    QVector<double> x(points_no+1), y(points_no+1);
    double m = (to_x-from_x)/points_no;
    for (int i = 0; i < points_no+1; i++) {
        x[i] = m*i + from_x;
        y[i] = this->evaluate(this->function_str, x[i]);
    }
    plotWidget->graph(0)->setData(x, y);
    plotWidget->xAxis->setLabel("x");
    plotWidget->yAxis->setLabel("fun");
    plotWidget->xAxis->setRange(from_x, to_x);
    plotWidget->yAxis->setRange(from_fun, to_fun);
    plotWidget->replot();
}

void Plotter::eval(QStack<double> &operands, QChar opr){
    double res, opd2, opd1=0;
    opd2 = operands.top();
    operands.pop();
    if(!operands.empty()) opd1 = operands.top();
    if(opr != '@') operands.pop();
    if(opr == '+') res = opd1+opd2;
    else if(opr == '-') res = opd1-opd2;
    else if(opr == '*') res = opd1*opd2;
    else if(opr == '/') res = opd1/opd2;
    else if(opr == '@') res = -1*opd2;
    else if(opr == '^') res = qPow(opd1, opd2);
    operands.push(res);
}

double Plotter::evaluate(QString str, double varValue){
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
                else val += (str[i].unicode() - '0') / (cnt*10.0);
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
                eval(operands, ops.top());
                ops.pop();
            }
            ops.pop();
        }
        else{
            if(isSign(str[i]) && (i== 0 || openingBr(str[i-1]) || isBinaryOp(str[i-1]) || isSign(str[i-1]) )){ //unary
                if(str[i] == '-') ops.push('@');
                continue;
            }
            int pr = priority(str[i]);
            while(!ops.isEmpty()){
                int topPr = priority(ops.top());
                if(pr > topPr || openingBr(ops.top())) break;
                eval(operands, ops.top());
                ops.pop();
            }
            ops.push(str[i]);
        }
    }

    while(!ops.isEmpty()){
        eval(operands, ops.top());
        ops.pop();
    }

    return operands.top();
}
