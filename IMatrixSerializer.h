#ifndef IMATRIXSERIALIZER_H
#define IMATRIXSERIALIZER_H

#include <QIODevice>
#include "Matrix.h"

class IMatrixSerializer
{
public:
	virtual Matrix readMatrix(QIODevice* device) const = 0;
	virtual bool saveMatrix(QIODevice* device, const Matrix& saveMe) const = 0;
};

#endif // IMATRIXSERIALIZER_H
