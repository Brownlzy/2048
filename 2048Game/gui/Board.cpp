#include "Board.h"
#include <QGridLayout>

Board::Board(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setGeometry(0, 0, 360, 360);
	initView();
}

Board::~Board()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			delete numbers[i][j];
		}
		delete [] numbers[i];
	}
	delete numbers;
}

void Board::initView()
{
	QRect qr(0, 0, 360, 360);
	ui.boardGrid->setGeometry(qr);
	numbers = new Number ** [4];
	for (int i = 0; i < 4; i++) {
		numbers[i] = new Number*[4];
		for (int j = 0; j < 4; j++) {
			numbers[i][j] = new Number(this);
			ui.boardGrid->addWidget(numbers[i][j],i,j,1,1,Qt::AlignJustify);
			numbers[i][j]->setValue(0);
		}
	}
}

void Board::setNowMatrix(Matrix* matrix)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			numbers[i][j]->setValue(matrix->getNumberIn(i, j));
		}
	}
}

void Board::operate(OperateList opl)
{

}
