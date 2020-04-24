QT += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    Matrix.cpp \
    MatrixRef.cpp \
    MainWindow.cpp \
    NaiveBayesClassifier.cpp

FORMS += \
    MainWindow.ui

HEADERS += \
    Matrix.h \
    MatrixRef.h \
    MainWindow.h \
    NaiveBayesClassifier.h
