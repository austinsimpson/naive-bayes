#pragma once

#include <QAbstractTableModel>

#include "NaiveBayesClassifier.h"

class NaiveBayesClassifierTableModel : public QAbstractTableModel
{
public:
	NaiveBayesClassifierTableModel();

	void setClassifier(NaiveBayesClassifier* classifier);

	int rowCount(const QModelIndex& index = QModelIndex()) const;
	int columnCount(const QModelIndex& index = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::UserRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
	NaiveBayesClassifier* _classifier;
	QList<QString> _words;
	QVector<QString> _categories;
};

