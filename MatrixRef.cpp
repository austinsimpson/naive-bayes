#include "MatrixRef.h"

#include "Matrix.h"

MatrixRef::MatrixRef
(
	Matrix& matrix
):
	_matrix(matrix),
	_rowOffset(0),
	_columnOffset(0),
	_rowCount(matrix.rowCount()),
	_columnCount(matrix.columnCount())
{

}

MatrixRef::MatrixRef
(
	Matrix& matrix,
	int rowOffset,
	int columnOffset,
	int rowCount,
	int columnCount
):
	_matrix(matrix),
	_rowOffset(rowOffset),
	_columnOffset(columnOffset),
	_rowCount(rowCount),
	_columnCount(columnCount)
{

}

MatrixRef::MatrixRef
(
	const MatrixRef& other
):
	_matrix(other._matrix),
	_rowOffset(other._rowOffset),
	_columnOffset(other._columnOffset),
	_rowCount(other._rowCount),
	_columnCount(other._columnCount)
{

}

double MatrixRef::value
(
	int row,
	int column
)   const
{
	return _matrix.value(_rowOffset + row, _columnOffset + column);
}

double MatrixRef::convolve(const Matrix& other) const
{
	double result = 0;

	for (int i = 0; i < _rowCount; i++)
	{
		for (int j = 0; j < _columnCount; j++)
		{
			result += this->value(i, j) * other.value(other.rowCount() - i - 1, other.columnCount() - j - 1);
		}
	}

	return result;
}

double MatrixRef::convolve(const MatrixRef& other) const
{
	double result = 0;

	for (int i = 0; i < _rowCount; i++)
	{
		for (int j = 0; j < _columnCount; j++)
		{
			result += this->value(i, j) * other.value(other.rowCount() - i - 1, other.columnCount() - j - 1);
		}
	}

	return result;
}

MatrixRef& MatrixRef::operator/=(double factor)
{
	if (factor != 0)
	{
		for (int j = _columnOffset; j < _columnOffset + _columnCount; ++j)
		{
			for (int i = _rowOffset; i < _rowOffset + _rowCount; ++i)
			{
				double val = _matrix.value(i, j);
				_matrix.setValue(i, j, val / factor);
			}
		}
	}
	return *this;
}
