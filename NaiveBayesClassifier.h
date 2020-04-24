#ifndef NAIVEBAYESCLASSIFIER_H
#define NAIVEBAYESCLASSIFIER_H


#include <QString>
#include <QVector>

#include <QMap>

#include <QRegularExpression>

#include "Matrix.h"
#include "ClassificationProbabilities.h"

class QIODevice;

class NaiveBayesClassifier
{
public:
    NaiveBayesClassifier(int numberOfCategories = 1);

    void loadFromDir(const QString& dirPath);

    void setStopWords(const QString& filePath);
    void setStopWords(const QVector<QString>& stopWords);

    void setNumberOfCategories(int categoryCount);
    int numberOfCategories() const;

    const QVector<QString>& categoryLabels() const;
    void setCategoryLabels(const QVector<QString>& categoryLabels);

    void addTextForCategory(int categoryIndex, const QString& text);
    void generateProbabilities();

    QList<QString> trainedWords() const;

    ClassificationProbabilities classify(const QString& text) const;

    //Used for showing in the table model
    double conditionalProbability(const QString& word, int category) const;

    bool saveToFile(const QString& filePath) const;
    bool readFromFile(const QString& file);

    QString sanitizeInput(const QString& input) const;

private: 
    bool saveWords(QIODevice* device) const;
    bool openWords(QIODevice* device);

    QVector<QString> _stopWords;
    QMap<QString, int> _wordToRowMap;
    
    QVector<int> _categoryWordCounts;
    QVector<QString> _categoryLabels;

    QRegularExpression _punctuationRegex;
    QRegularExpression _newlineRegex;

    Matrix _probabilityMatrix;

    int _numberOfWords;
};

#endif // NAIVEBAYESCLASSIFIER_H
