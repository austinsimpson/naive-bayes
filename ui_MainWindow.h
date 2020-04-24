/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *_actionOpenTrainingDir;
    QAction *_actionSave;
    QAction *_actionOpenFile;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QTableView *_bayesTableView;
    QTableView *_resultsView;
    QHBoxLayout *horizontalLayout;
    QLineEdit *_classifierInput;
    QPushButton *_computeButton;
    QLabel *_classificationLabel;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        _actionOpenTrainingDir = new QAction(MainWindow);
        _actionOpenTrainingDir->setObjectName(QString::fromUtf8("_actionOpenTrainingDir"));
        _actionSave = new QAction(MainWindow);
        _actionSave->setObjectName(QString::fromUtf8("_actionSave"));
        _actionOpenFile = new QAction(MainWindow);
        _actionOpenFile->setObjectName(QString::fromUtf8("_actionOpenFile"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        _bayesTableView = new QTableView(centralwidget);
        _bayesTableView->setObjectName(QString::fromUtf8("_bayesTableView"));

        horizontalLayout_2->addWidget(_bayesTableView);

        _resultsView = new QTableView(centralwidget);
        _resultsView->setObjectName(QString::fromUtf8("_resultsView"));

        horizontalLayout_2->addWidget(_resultsView);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        _classifierInput = new QLineEdit(centralwidget);
        _classifierInput->setObjectName(QString::fromUtf8("_classifierInput"));

        horizontalLayout->addWidget(_classifierInput);

        _computeButton = new QPushButton(centralwidget);
        _computeButton->setObjectName(QString::fromUtf8("_computeButton"));

        horizontalLayout->addWidget(_computeButton);


        verticalLayout->addLayout(horizontalLayout);

        _classificationLabel = new QLabel(centralwidget);
        _classificationLabel->setObjectName(QString::fromUtf8("_classificationLabel"));

        verticalLayout->addWidget(_classificationLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(_actionOpenTrainingDir);
        menuFile->addAction(_actionOpenFile);
        menuFile->addAction(_actionSave);
        menuFile->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        _actionOpenTrainingDir->setText(QCoreApplication::translate("MainWindow", "Open Training Folder", nullptr));
        _actionSave->setText(QCoreApplication::translate("MainWindow", "Save Classifier", nullptr));
        _actionOpenFile->setText(QCoreApplication::translate("MainWindow", "Open Classifier", nullptr));
        _computeButton->setText(QCoreApplication::translate("MainWindow", "Compute", nullptr));
        _classificationLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
