#include "MainWindow.h"

#include "NaiveBayesClassifierTableModel.h"

#include <QFile>
#include <QTextStream>

#include <QFileDialog>
#include <QDir>

#include <QDebug>

MainWindow::MainWindow
(
    QWidget* parent
):
    QMainWindow(parent),
    Ui::MainWindow()
{
    setupUi(this);

    connect(_actionOpenTrainingDir, &QAction::triggered, this, &MainWindow::browseForTrainingDirectory);
    connect(_actionOpenFile, &QAction::triggered, this, &MainWindow::browseForClassifierOpenFile);
    connect(_actionSave, &QAction::triggered, this, &MainWindow::browseForClassifierSaveFile);
    connect(_computeButton, &QPushButton::pressed, this, &MainWindow::runClassifier);

	_classifier.readFromFile(":/data/sentiment.mat");
	generateTableModel();
}

MainWindow::~MainWindow()
{
}

void MainWindow::browseForTrainingDirectory()
{
    const QString directoryPath = QFileDialog::getExistingDirectory(this, "Choose the root level directory to process. Categories should be distinct folders with the text files contained within them.");
    if (directoryPath.isEmpty() == false)
    {
        openTrainingDirectory(directoryPath);
        generateTableModel();
    }
}

void MainWindow::browseForClassifierOpenFile()
{
    const QString filePath = QFileDialog::getOpenFileName(this, "Find a classifier file.", QString(), "*.mat");
    if (filePath.isEmpty() == false)
    {
        _classifier.readFromFile(filePath);
        generateTableModel();
    }
}

void MainWindow::browseForClassifierSaveFile()
{
    const QString filePath = QFileDialog::getSaveFileName(this, "Save a classifier file", QString(), "*.mat");
    if (filePath.isEmpty() == false)
    {
        _classifier.saveToFile(filePath);
    }
}


void MainWindow::openTrainingDirectory
(
    const QString& directory
)
{
    _classifier.loadFromDir(directory);
}

void MainWindow::runClassifier()
{
    auto probabilities = _classifier.classify(_classifierInput->text());
    
    int index = 0;
    for (qreal prob : probabilities)
    {
        qDebug() << probabilities.getLabel(index) << ": " << QString::number(prob);
        ++index;
    }
    
    auto mostProbable = probabilities.mostProbable();
    _classificationLabel->setText(probabilities.getLabel(mostProbable.first));
	_classificationLabel->update();
}

void MainWindow::generateTableModel()
{
    NaiveBayesClassifierTableModel* tableModel = new NaiveBayesClassifierTableModel();
    tableModel->setClassifier(&_classifier);
    _bayesTableView->setModel(tableModel);
}
