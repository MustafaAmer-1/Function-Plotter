#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "plotter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fun_input_widget->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_plotButton_clicked()
{
    QString function_str = ui->fun_input_widget->text();
    Plotter* plotter = Plotter::getPlotter(function_str);
    if(plotter->validate()){
        double from_x = ui->from_x_spin->value();
        double to_x = ui->to_x_spin->value();
        double from_fun = ui->from_fun_spin->value();
        double to_fun = ui->to_fun_spin->value();
        if(from_x > to_x){
            QMessageBox::critical(this, "Invalid input range",
                               "the input range for x is invalid please try again!");
        }
        else if(from_fun > to_fun){
            QMessageBox::critical(this, "Invalid input range",
                               "the input range for function is invalid please try again!");
        }
        else plotter->plot(from_x, to_x, from_fun, to_fun);
    }
    else{
        QMessageBox::critical(this, "Invalid function",
                           "the input function is invalid please try again!");
    }
}

