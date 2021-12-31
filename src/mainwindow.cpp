/**
 * @file mainwindow.cpp
 * @author Mustafa Amer (eng.MustafaAmer0@gmail.com)
 * @brief MainWindow class implementation
 * @version 0.1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "plotter.h"

/**
 * @brief Construct a new Main Window object
 * 
 * @param parent - the parent widget for this window
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plotWidget->addGraph();
}

/**
 * @brief Destroy the Main Window object
 * 
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/**
 * @brief signal method which get executed when clicking at the plot button
 * the method first check for the input function expression, displaying messages with any wrong input. 
 * then check for the input ranges for x and the function to be plotted
 * then call the plot method from Plotter class with the input data
 * 
 */
void MainWindow::on_plotButton_clicked()
{
    QString function_str = ui->fun_input_widget->text();
    if(function_str.isEmpty()) return;
    Plotter* plotter = Plotter::getPlotter(function_str);
    try {
        plotter->validate();
    }
    catch (ExpressionException *e) {
        QMessageBox::critical(this, "Invalid function",
                           "the input function is invalid\n"
                           + e->msg +
                           "\nplease try again!");
        return;
    }
    double from_x = ui->from_x_spin->value();
    double to_x = ui->to_x_spin->value();
    double from_fun = ui->from_fun_spin->value();
    double to_fun = ui->to_fun_spin->value();

    int points_no = ui->points_no->value();
    if(from_x > to_x){
        QMessageBox::critical(this, "Invalid input range",
                           "the input range for x is invalid please try again!");
    }
    else if(from_fun > to_fun){
        QMessageBox::critical(this, "Invalid input range",
                           "the input range for function is invalid please try again!");
    }
    else{
        try{
            plotter->plot(ui->plotWidget, from_x, to_x, from_fun, to_fun, points_no);
        }
        catch(...){
            QMessageBox::critical(this, "Invalid function",
                               "the input function is invalid\n"
                               "please try again!");
        }
    }
}

