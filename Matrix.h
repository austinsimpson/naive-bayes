#pragma once

#include <QObject>
#include <QSharedDataPointer>

#include <math.h>
#include <functional>

#include "MatrixRef.h"

class MatrixData : public QSharedData
{
public:
	MatrixData()
	{
		_rowCount = 0;
		_columnCount = 0;
		_matrixValues = nullptr;
	}

	MatrixData(int rowCount, int columnCount)
	{
		int elementCount = rowCount * columnCount;
		_matrixValues = new double[elementCount];
		memset(_matrixValues, 0, sizeof(double) * elementCount);
		_rowCount = rowCount;
		_columnCount = columnCount;
	}

	MatrixData(int rowCount, int columnCount, double* data)
	{
		_matrixValues = data;
		_rowCount = rowCount;
		_columnCount = columnCount;
	}

	MatrixData(const MatrixData& other) : QSharedData(other), _matrixValues(other._matrixValues), _rowCount(other.rowCount()), _columnCount(other.columnCount())
	{

	}

	MatrixData* clone()
	{
		MatrixData* result = new MatrixData(rowCount(), columnCount());
		memcpy(result->_matrixValues, _matrixValues, sizeof(double) * rowCount() * columnCount());
		return result;
	}

	~MatrixData()
	{
		if (_matrixValues != nullptr)
		{
			delete[] _matrixValues;
		}
	}

	inline double value(int row, int column) const
	{
		double result = nan("");
		if (0 <= row && row < _rowCount && 0 <= column && column < _columnCount)
		{
			result = _matrixValues[row * columnCount() + column];
		}
		return result;
	}

	inline void setValue(int row, int column, double value)
	{
		if (0 <= row && row < _rowCount && 0 <= column && column < _columnCount)
		{
			_matrixValues[row * _columnCount + column] = value;
		}
	}

	inline int rowCount() const
	{
		return _rowCount;
	}

	inline int columnCount() const
	{
		return _columnCount;
	}

    inline void resize(int newRowCount, int newColumnCount)
    {
		int newSize = newRowCount * newColumnCount;
        double* newData = new double[newSize];
        memset(newData, 0.0, sizeof(double) * newRowCount * newColumnCount);

		int min = _columnCount < newColumnCount ? _columnCount : newColumnCount;
        for (int i = 0; i < _rowCount && i < newRowCount; ++i)
        {
            memcpy(newData + (i * newColumnCount), _matrixValues + (i * _columnCount), min * sizeof(double));
        }

        delete[] _matrixValues;
        _matrixValues = newData;
        _rowCount = newRowCount;
        _columnCount = newColumnCount;
    }

	inline const double* data() const
	{
		return _matrixValues;
	}

	inline bool isValid() const
	{
		return _matrixValues != nullptr && _rowCount > 0 && _columnCount > 0;
	}

private:
	double* _matrixValues;
	int _rowCount;
	int _columnCount;
};


class Matrix
{
public:
	Matrix();
	Matrix(int rowCount, int columnCount);
	Matrix(const Matrix& other);
	Matrix(int rowCount, int columnCount, double* data);
	Matrix(int rowCount, int columnCount, std::function<double(int, int)> function);

	~Matrix();

	Matrix& operator= (const Matrix& other);
	bool operator == (const Matrix& other);
	bool operator != (const Matrix& other);

	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);

	inline const double* getData() const { return _matrixData->data(); }

	double value(int row, int column) const;
	void setValue(int row, int column, double value);
    void resize(int newRowCount, int newColumnCount);

	inline int rowCount() const
	{
		return _matrixData.data()->rowCount();
	}

	inline MatrixRef row(int row)
	{
		return MatrixRef(*this, row, 0, 1, columnCount());
	}
	
	int columnCount() const
	{
		return _matrixData.data()->columnCount();
	}

	inline MatrixRef column(int column)
	{
		return MatrixRef(*this, 0, column, rowCount(), 1);
	}
	
	inline bool isValid() const
	{
		return _matrixData.constData()->isValid();
	}

	bool isReducedRowEchelonForm() const;

	Matrix multiply(const Matrix& other);
	void scale(double factor);

	double convolve(const Matrix& other) const;


	static Matrix Identity(int size);

	Matrix rowEchelonForm() const;
	Matrix reducedRowEchelonForm();

    QString toString();
	Matrix transpose();

private:
	void scaleRow(int row, double factor);
	void swapRows(int first, int second);
	void pivot(int pivotRow, int targetRow, double scalar);

	QSharedDataPointer<MatrixData> _matrixData;
};

template<> inline MatrixData* QSharedDataPointer<MatrixData>::clone()
{
	return d->clone();
}


#ifdef USE_CUDA
struct CudaMatrix;
CudaMatrix matrixToCudaMatrix(const Matrix& matrix);
#endif
