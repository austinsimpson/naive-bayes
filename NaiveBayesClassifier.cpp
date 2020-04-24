#include "NaiveBayesClassifier.h"

#include <QDebug>

#include <QDir>
#include <QStringList>

#include <QFile>
#include <QTextStream>
#include <QDataStream>

#include "BinaryMatrixSerializer.h"

NaiveBayesClassifier::NaiveBayesClassifier
(
	int numberOfCategories
) :
	_numberOfWords(0),
	_probabilityMatrix(2, numberOfCategories),
	_punctuationRegex("[^[:alnum:]|[:space:]]"),
	_newlineRegex("[\r]+|[\n]+"),
	_categoryWordCounts(numberOfCategories, 0)
{
}

void NaiveBayesClassifier::setNumberOfCategories
(
	int numberOfCategories
)
{
	_categoryWordCounts = QVector<int>(numberOfCategories, numberOfCategories);
    _probabilityMatrix.resize(_probabilityMatrix.rowCount(), numberOfCategories);
}

void NaiveBayesClassifier::setCategoryLabels
(
	const QVector<QString>& categoryLabels
)
{
	_categoryLabels = categoryLabels;
}

const QVector<QString>& NaiveBayesClassifier::categoryLabels() const
{
	return _categoryLabels;
}

void NaiveBayesClassifier::loadFromDir
(
	const QString& dirPath
)
{
	const QDir dir(dirPath);
	const QStringList categoryList = dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
	setNumberOfCategories(categoryList.size());
	setCategoryLabels(categoryList.toVector());

	QFile workingFile;
	int categoryIndex = 0;
	for (const QString& category : categoryList)
	{
		const QString fullPath = dirPath + "/" + category;
		const QDir categoryDir(fullPath);
		for (const QString& filePath : categoryDir.entryList({ "*.txt" }, QDir::Files, QDir::NoSort))
		{
			workingFile.setFileName(fullPath + "/" + filePath);
			if (workingFile.open(QIODevice::ReadOnly))
			{
				while (workingFile.atEnd() == false)
				{
					QByteArray fileData = workingFile.readLine();
					addTextForCategory(categoryIndex, fileData);
				}
				workingFile.close();
			}
		}
		++categoryIndex;
	}

	generateProbabilities();
}

int NaiveBayesClassifier::numberOfCategories() const
{
	return _probabilityMatrix.columnCount();
}

void NaiveBayesClassifier::addTextForCategory
(
	int categoryIndex, 
	const QString& text
)
{
	const bool isValid = _punctuationRegex.isValid();

	const QString intermediate = sanitizeInput(text);
	const QStringList splitOnText = intermediate.split(" ", Qt::SkipEmptyParts);
	for (const QString& word : splitOnText)
	{
		if (_stopWords.contains(word) == false)
		{
			int rowIndex(-1);
			if (_wordToRowMap.contains(word))
			{
				rowIndex = _wordToRowMap[word];
			}
			else
			{
				rowIndex = _numberOfWords;
				_numberOfWords++;
				_wordToRowMap[word] = rowIndex;

				if (_numberOfWords >= _probabilityMatrix.rowCount())
				{
					_probabilityMatrix.resize(_probabilityMatrix.rowCount() * 2, _probabilityMatrix.columnCount());
				}
			}
			double valueAtIndex = _probabilityMatrix.value(rowIndex, categoryIndex);
			_probabilityMatrix.setValue(rowIndex, categoryIndex, valueAtIndex + 1.0);

			_categoryWordCounts[categoryIndex]++;

		}
	}
}


void NaiveBayesClassifier::setStopWords
(
	const QString& filePath
)
{
	QVector<QString> stopWords;

	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream textStream(&file);
		while (textStream.atEnd() == false)
		{
			stopWords.push_back(textStream.readLine());
		}
		file.close();
	}

	setStopWords(stopWords);
}

void NaiveBayesClassifier::setStopWords
(
	const QVector<QString>& stopWords
)
{
	_stopWords = stopWords;
}

QList<QString> NaiveBayesClassifier::trainedWords() const
{
	return _wordToRowMap.keys();
}

void NaiveBayesClassifier::generateProbabilities()
{
	for (int i = 0; i < _probabilityMatrix.columnCount(); ++i)
	{
		_probabilityMatrix.column(i) /= _categoryWordCounts[i];
	}
}

double NaiveBayesClassifier::conditionalProbability
(
	const QString& word,
	int category
)	const
{
	return _probabilityMatrix.value(_wordToRowMap[word], category);
}


ClassificationProbabilities NaiveBayesClassifier::classify
(
	const QString& text
)	const
{
	ClassificationProbabilities result(_probabilityMatrix.columnCount(), _categoryLabels);
	for (const QString& word : sanitizeInput(text).split(" "))
	{
		if (_wordToRowMap.contains(word))
		{
			for (int currentCategory = 0; currentCategory < _probabilityMatrix.columnCount(); ++currentCategory)
			{
				result[currentCategory] *= conditionalProbability(word, currentCategory);
			}
		}
	}
	return result;
}

bool NaiveBayesClassifier::saveToFile
(
	const QString& filePath
)	const
{
	bool result = true;

	const BinaryMatrixSerializer serializer;
	QFile matrixFile(filePath);
	result &= serializer.saveMatrix(&matrixFile, _probabilityMatrix);
	matrixFile.close();

	QFile wordsFile(filePath + ".words");
	result &= saveWords(&wordsFile);

	return result;
}

QString NaiveBayesClassifier::sanitizeInput
(
	const QString& input
)	const
{
	return input.toLower().replace(_punctuationRegex, " ").replace(_newlineRegex, " ");
}

bool NaiveBayesClassifier::saveWords
(
	QIODevice* device
)	const
{
	const bool isFileWritable = device->isOpen() || device->open(QIODevice::WriteOnly);
	if (isFileWritable)
	{
		QDataStream dataStream(device);
		dataStream << _wordToRowMap;
		dataStream << _categoryLabels;
	}
	
	return isFileWritable;
}

bool NaiveBayesClassifier::readFromFile
(
	const QString& filePath
) 
{
	bool result = true;

	BinaryMatrixSerializer serializer;
	
	QFile matrixFile(filePath);
	_probabilityMatrix = serializer.readMatrix(&matrixFile);
	result &= _probabilityMatrix.isValid();

	QFile wordsFile(filePath + ".words");
	result &= openWords(&wordsFile);
	wordsFile.close();

	return result;
}

bool NaiveBayesClassifier::openWords
(
	QIODevice* device
)
{
	const bool isFileReadable = device->isOpen() || device->open(QIODevice::ReadOnly);
	if (isFileReadable)
	{
		QDataStream dataStream(device);
		dataStream >> _wordToRowMap;
		dataStream >> _categoryLabels;
	}

	return isFileReadable;
}