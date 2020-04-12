#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
};

#endif // MAINWINDOW_H
