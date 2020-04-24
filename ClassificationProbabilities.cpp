#include "ClassificationProbabilities.h"

ClassificationProbabilities::ClassificationProbabilities
(
	int size,
	const QVector<QString>& labels
)
{
	for (int i = 0; i < size || i < labels.count(); ++i)
	{
		_probabilities.push_back(1.0);
	}

	_labels = labels;
}



qreal& ClassificationProbabilities::operator[]
(
	int index
)
{
	return _probabilities[index];
}

QVector<qreal>::iterator ClassificationProbabilities::begin()
{
	return _probabilities.begin();
}


QVector<qreal>::iterator ClassificationProbabilities::end()
{
	return _probabilities.end();
}


QVector<qreal>::const_iterator ClassificationProbabilities::cbegin() const
{
	return _probabilities.constBegin();
}


QVector<qreal>::const_iterator ClassificationProbabilities::cend() const
{
	return _probabilities.constEnd();
}

const QString& ClassificationProbabilities::getLabel
(
	int index 
)	const
{
	return _labels[index];
}


QPair<int, qreal> ClassificationProbabilities::mostProbable() const
{
	auto iter = std::max_element(_probabilities.begin(), _probabilities.end());
	return qMakePair(iter - _probabilities.begin(), *iter);
}