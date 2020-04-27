QT += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

FORMS += \
    MainWindow.ui

HEADERS += \
    BinaryMatrixSerializer.h \
    ClassificationProbabilities.h \
    IMatrixSerializer.h \
    MainWindow.h \
    Matrix.h \
    MatrixRef.h \
    NaiveBayesClassifier.h \
    NaiveBayesClassifierTableModel.h

SOURCES += \
    BinaryMatrixSerializer.cpp \
    ClassificationProbabilities.cpp \
    MainWindow.cpp \
    Matrix.cpp \
    MatrixRef.cpp \
    NaiveBayesClassifier.cpp \
    NaiveBayesClassifierTableModel.cpp \
    main.cpp

RESOURCES += \
    Resources.qrc
