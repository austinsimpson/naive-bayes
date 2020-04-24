#include "BinaryMatrixSerializer.h"

#include <QDataStream>

constexpr auto kFileMagic = "MAT";

Matrix BinaryMatrixSerializer::readMatrix
(
	QIODevice* device
)	const
{
	bool isDeviceReadable = device->isOpen() || device->open(QIODevice::ReadOnly);
	if (isDeviceReadable)
	{
		char* magic = new char[4];

		QDataStream dataStream(device);
		dataStream.setVersion(QDataStream::Qt_5_14);
		auto bytesRead = dataStream.readRawData(magic, 3);
		magic[3] = '\0';

		if (QString(magic) == kFileMagic)
		{
			int rowCount = -1;
			int columnCount = -1;

			dataStream >> rowCount;
			dataStream >> columnCount;

			double* matrixData = new double[rowCount * columnCount];
			size_t bytesToRead = sizeof(double) * rowCount * columnCount;
			dataStream.readRawData((char*)matrixData, rowCount * columnCount * sizeof(double));
			return Matrix(rowCount, columnCount, matrixData);
		}
	}
	return Matrix();
}

bool BinaryMatrixSerializer::saveMatrix
(
	QIODevice* device,
	const Matrix& matrix
)	const
{
	bool result = false;

	bool isDeviceWritable = device->isOpen() || device->open(QIODevice::WriteOnly);
	if (isDeviceWritable)
	{
		QDataStream dataStream(device);
		dataStream.writeRawData(kFileMagic, 3);
		dataStream << matrix.rowCount();
		dataStream << matrix.columnCount();
		size_t numberOfBytesToWrite = sizeof(double) * matrix.rowCount() * matrix.columnCount();
		const double* matrixData = matrix.getData();
		auto bytesWritten = dataStream.writeRawData((char*)matrixData, numberOfBytesToWrite);
	}

	return result;
}