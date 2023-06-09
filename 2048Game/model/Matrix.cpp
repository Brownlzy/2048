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
