QT += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    MainWindow.cpp \
    NaiveBayesClassifier.cpp

FORMS += \
    MainWindow.ui

HEADERS += \
    MainWindow.h \
    NaiveBayesClassifier.h
