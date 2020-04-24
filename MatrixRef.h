#pragma once

class Matrix;
class MatrixRef
{
public:
	MatrixRef(Matrix& matrix);
	MatrixRef(Matrix& matrix, int rowOffset, int columnOffset, int rowCount, int columnCount);
	MatrixRef(const MatrixRef& other);

	MatrixRef& operator=(const MatrixRef& other);

	double value(int row, int column) const;
	
	double convolve(const Matrix& other) const;
	double convolve(const MatrixRef& other) const;

	MatrixRef& operator/=(double factor);

	inline int rowCount() const
	{
		return _rowCount;
	}

	inline int columnCount() const
	{
		return _columnCount;
	}

private:
	Matrix& _matrix;
	int _rowOffset;
	int _columnOffset;
	int _rowCount;
	int _columnCount;
};
