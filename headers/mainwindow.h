/**
 * @file mainwindow.h
 * @author Mustafa Amer (eng.MustafaAmer0@gmail.com)
 * @brief header file containing the MainWindow class 
 * @version 0.1
 * @date 2021-12-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Qt defined class responsible for the main window of the program.
 * 
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plotButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
