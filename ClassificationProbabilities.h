#pragma once

#include <QVector>


class ClassificationProbabilities
{
public:
	ClassificationProbabilities(int size, const QVector<QString>& labels = QVector<QString>());

	qreal& operator[](int index);
	QPair<int, qreal> mostProbable() const;


	QVector<qreal>::iterator begin();
	QVector<qreal>::iterator end();


	QVector<qreal>::const_iterator cbegin() const;
	QVector<qreal>::const_iterator cend() const;


	const QString& getLabel(int index) const;
private:
	QVector<QString> _labels;
	QVector<qreal> _probabilities;
};

