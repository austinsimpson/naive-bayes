#pragma once

#include "IMatrixSerializer.h"

class BinaryMatrixSerializer : public IMatrixSerializer
{
public:
	BinaryMatrixSerializer() = default;

	Matrix readMatrix(QIODevice* device) const;
	bool saveMatrix(QIODevice* device, const Matrix& matrix) const;
};

