#include <QApplication>

#include "MainWindow.h"

#include "Matrix.h"
#include "BinaryMatrixSerializer.h"

#include "NaiveBayesClassifier.h"

#include <QFile>
#include <QDebug>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow window;

    window.show();
    return app.exec();
}
