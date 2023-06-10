#pragma once

#include <QWidget>
#include "ui_Board.h"
#include "Number.h"
#include "../model/Matrix.h"
#include "../model/OperateList.h"
#include <QPropertyAnimation>
#include <vector>

#define ANIMATION_DURATION 100

class Board : public QWidget
{
	Q_OBJECT

public:
	Board(QWidget *parent = nullptr);
	~Board();
	void initView();
	void setNowMatrix(Matrix* matrix);
	void setNewMatrix(Matrix* matrix);
	void operate(OperateList* opl);
	bool isAnimating();

private:
	Ui::BoardClass ui;
	Number*** numbers;
	Matrix* matrix;
	std::vector<Number*> tempNumbers;
	std::vector<QPropertyAnimation*> animations;
	bool animating = false;

	void deleteTempNumbers();
	void startAnimation();
	//void deleteAnimations();
	void generateAnimation(OperateList* opl, bool isMove);
	void operate2(OperateList* opl);
	void operate3(OperateList* opl);
};
