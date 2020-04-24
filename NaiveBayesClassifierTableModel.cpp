#include "NaiveBayesClassifierTableModel.h"

NaiveBayesClassifierTableModel::NaiveBayesClassifierTableModel()
	: _classifier(nullptr)
{

}

void NaiveBayesClassifierTableModel::setClassifier
(
	NaiveBayesClassifier* classifier
)
{
	beginResetModel();
	_classifier = classifier;
	_words = classifier->trainedWords();
	_categories = _classifier->categoryLabels();
	endResetModel();
}

int NaiveBayesClassifierTableModel::rowCount
(
	const QModelIndex& index
)	const
{
	return _words.count();
}

int NaiveBayesClassifierTableModel::columnCount
(
	const QModelIndex& index
)	const
{
	return _classifier->numberOfCategories();
}

QVariant NaiveBayesClassifierTableModel::data
(
	const QModelIndex& index, 
	int role
)	const
{
	QVariant result;

	if (index.row() < 0 || index.row() > rowCount() || index.column() < 0 || index.column() > columnCount())
		return QVariant();


	switch (role)
	{
	case Qt::DisplayRole:
		result = _classifier->conditionalProbability(_words[index.row()], index.column());
		break;

	default:
		break;
	}

	return result;
}

QVariant NaiveBayesClassifierTableModel::headerData
(
	int section,
	Qt::Orientation orientation,
	int role
)	const
{
	QVariant result;

	if (section < 0 || section > _words.count() || role != Qt::DisplayRole)
		return result;

	if (orientation == Qt::Vertical)
	{
		return _words[section];
	}
	else
	{
		return _categories[section];
	}
}