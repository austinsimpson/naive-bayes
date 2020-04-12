#include "MainWindow.h"

MainWindow::MainWindow
(
    QWidget* parent
):
    QMainWindow(parent),
    Ui::MainWindow()
{
    setupUi(this);
}

MainWindow::~MainWindow()
{
}
