#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "NaiveBayesClassifier.h"

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void browseForTrainingDirectory();
    void browseForClassifierOpenFile();
    void browseForClassifierSaveFile();

    void openTrainingDirectory(const QString& directory);

    void runClassifier();

private:
    void generateTableModel();

    NaiveBayesClassifier _classifier;
};

#endif // MAINWINDOW_H
