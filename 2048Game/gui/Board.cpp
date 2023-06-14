#include "Board.h"
#include <QGridLayout>
#include <QTimer>

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
	numbers = new Number ** [4];
	for (int i = 0; i < 4; i++) {
		numbers[i] = new Number*[4];
		for (int j = 0; j < 4; j++) {
			numbers[i][j] = new Number(this,j*92,i*92,86,86,0);
			numbers[i][j]->setValue(0);
		}
	}
}

void Board::setNowMatrix(Matrix* matrix)
{
	Board::matrix = matrix;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			numbers[i][j]->setValue(matrix->getNumberIn(i, j));
		}
	}
}

void Board::setNewMatrix(Matrix* matrix)
{
	Board::matrix = matrix;
}

void Board::operate(OperateList* opl)
{
	if(isAnimation){
		animating = true;
		generateAnimation(opl,true);
		startAnimation();
		QTimer::singleShot(ANIMATION_DURATION, [=]() { operate2(opl); });
	}else{
		opl->~OperateList();
		setNowMatrix(matrix);
		emit animationEnded();
	}
}

bool Board::isAnimating()
{
	return animating;
}

void Board::setAnimation(bool is)
{
	isAnimation = is;
}

void Board::operate2(OperateList* opl) {
	generateAnimation(opl,false);
	startAnimation();
	QTimer::singleShot(ANIMATION_DURATION/2, [=]() { operate3(opl); });
}

void Board::operate3(OperateList* opl) {
	deleteTempNumbers();
	opl->~OperateList();
	setNowMatrix(matrix);
	animating = false;
	emit animationEnded();
}

void Board::deleteTempNumbers()
{
	while (tempNumbers.size() > 0) {
		delete tempNumbers.back();
		tempNumbers.pop_back();
	}
}

void Board::startAnimation()
{
	QPropertyAnimation* ani;
	while (animations.size() > 0) {
		ani = animations.back();
		animations.pop_back();
		ani->start(QAbstractAnimation::DeleteWhenStopped);
	}
}

void Board::generateAnimation(OperateList* opl,bool isMove)
{
	QPropertyAnimation* animation;
	Number* num;
	int value = 0;
	for (int i = 0; i < opl->getCount(); i++)
	{
		Operate* op = opl->getOperate(i);
		switch (op->getMethod())
		{
		case MOVE:
			if (!isMove) break;
			num = new Number(this, op->getPoint1().at(0) * 92, op->getPoint1().at(1) * 92, 86, 86, numbers[op->getPoint1().at(0)][op->getPoint1().at(1)]->getValue());
			num->raise();
			num->show();
			numbers[op->getPoint1().at(0)][op->getPoint1().at(1)]->setValue(0);
			tempNumbers.push_back(num);
			animation = new QPropertyAnimation(num, "geometry");
			animation->setDuration(ANIMATION_DURATION);
			animation->setStartValue(QRect(op->getPoint1().at(1) * 92, op->getPoint1().at(0) * 92, 86, 86));
			animation->setEndValue(QRect(op->getPoint2().at(1) * 92, op->getPoint2().at(0) * 92, 86, 86));
			animations.push_back(animation);
			break;
		case MERGE:
			if (!isMove) break;

			num = new Number(this, op->getPoint1().at(0) * 92, op->getPoint1().at(1) * 92, 86, 86, numbers[op->getPoint1().at(0)][op->getPoint1().at(1)]->getValue());
			num->raise();
			num->show();
			numbers[op->getPoint1().at(0)][op->getPoint1().at(1)]->setValue(0);

			tempNumbers.push_back(num);
			animation = new QPropertyAnimation(num, "geometry");
			animation->setDuration(ANIMATION_DURATION);
			animation->setStartValue(QRect(op->getPoint1().at(1) * 92, op->getPoint1().at(0) * 92, 86, 86));
			animation->setEndValue(QRect(op->getPoint3().at(1) * 92, op->getPoint3().at(0) * 92, 86, 86));
			animations.push_back(animation);

			num = new Number(this, op->getPoint2().at(0) * 92, op->getPoint2().at(1) * 92, 86, 86, numbers[op->getPoint2().at(0)][op->getPoint2().at(1)]->getValue());
			num->raise();
			num->show();
			numbers[op->getPoint2().at(0)][op->getPoint2().at(1)]->setValue(0);

			tempNumbers.push_back(num);
			animation = new QPropertyAnimation(num, "geometry");
			animation->setDuration(ANIMATION_DURATION);
			animation->setStartValue(QRect(op->getPoint2().at(1) * 92, op->getPoint2().at(0) * 92, 86, 86));
			animation->setEndValue(QRect(op->getPoint3().at(1) * 92, op->getPoint3().at(0) * 92, 86, 86));
			animations.push_back(animation);

			opl->addOperate(new NewIn(op->getPoint3().at(0),op->getPoint3().at(1), op->getValue()));
			break;
		case NEW:
			if (isMove) break;
			num = new Number(this, op->getPoint2().at(0) * 92, op->getPoint2().at(1) * 92, 0, 0, op->getValue());
			num->raise();
			num->show();
			numbers[op->getPoint1().at(0)][op->getPoint1().at(1)]->setValue(0);

			tempNumbers.push_back(num);
			animation = new QPropertyAnimation(num, "geometry");
			animation->setDuration(ANIMATION_DURATION/2);
			animation->setStartValue(QRect(op->getPoint1().at(1) * 92+43, op->getPoint1().at(0) * 92+43, 0, 0));
			animation->setEndValue(QRect(op->getPoint1().at(1) * 92, op->getPoint1().at(0) * 92, 86, 86));
			animations.push_back(animation);
			break;
		default:
			break;
		}
	}
}
