#include "Matrix.h"
#include <QDebug>

Matrix::Matrix()
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			matrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& ma)
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			matrix[i][j] = ma.matrix[i][j];
		}
	}
}

Matrix::Matrix(int array[4][4])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matrix[i][j] = array[i][j];
		}
	}
}

Matrix::~Matrix()
{
	if (line != nullptr)
		delete[] line;
}

int Matrix::getNumberIn(int x, int y)
{
	return matrix[x][y];
}

void Matrix::setNumberIn(int x, int y, const int value)
{
	matrix[x][y] = value;
}

int* Matrix::getLineOnX(int x)
{
	return matrix[x];
}

void Matrix::setLineOnX(int x, const int* values)
{
	for (int i = 0; i < 4; i++) {
		matrix[x][i]=values[i];
	}
}

int* Matrix::getLineOnY(int y)
{
	int linex[4];
	for (int i = 0; i < 4; i++) {
		linex[i] = matrix[i][y];
	}
	return linex;
}

void Matrix::setLineOnY(int y, const int* values)
{
	for (int i = 0; i < 4; i++) {
		matrix[i][y]=values[i];
	}
}

int* Matrix::getLineOn(Direction d, int no)
{
	if (line != nullptr)
		delete[] line;
	switch (d)
	{
	case Matrix::UP:
		line = new int[4];
		for (int i = 0; i < 4; i++) {
			line[i] = matrix[i][no];
		}
		return line;
	case Matrix::DOWN:
		line = new int[4];
		for (int i = 0; i < 4; i++) {
			line[i] = matrix[3-i][no];
		}
		return line;
	case Matrix::RIGHT:
		line = new int[4];
		for (int i = 0; i < 4; i++) {
			line[i] = matrix[no][3-i];
		}
		return line;
	case Matrix::LEFT:
		line = new int[4];
		for (int i = 0; i < 4; i++) {
			line[i] = matrix[no][i];
		}
		return line;
	default:
		return nullptr;
	}
}

void Matrix::setLineOn(Direction d, int no, const int* values)
{
	switch (d)
	{
	case Matrix::UP:
		for (int i = 0; i < 4; i++) {
			matrix[i][no] = values[i];
		}
		break;
	case Matrix::DOWN:
		for (int i = 0; i < 4; i++) {
		matrix[3 - i][no] =	line[i];
		}
		break;
	case Matrix::RIGHT:
		for (int i = 0; i < 4; i++) {
		matrix[no][3 - i] = line[i];
		}
		break;
	case Matrix::LEFT:
		for (int i = 0; i < 4; i++) {
		matrix[no][i] = line[i];
		}
		break;
	default:
		break;
	}
}

void Matrix::printToConsole()
{
	QString line;
	qDebug() << "";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			line.append(QString::number(matrix[i][j])+"\t\t");
		}
		qDebug().noquote() << line;
		line = "";
	}
}

void Matrix::printToConsole(QString title)
{
	qDebug().noquote() << title;
	printToConsole();
}
