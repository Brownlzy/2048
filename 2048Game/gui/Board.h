#pragma once

#include <QWidget>
#include "ui_Board.h"
#include "Number.h"
#include "../model/Matrix.h"
#include "../model/OperateList.h"

class Board : public QWidget
{
	Q_OBJECT

public:
	Board(QWidget *parent = nullptr);
	~Board();
	void initView();
	void setNowMatrix(Matrix* matrix);
	void operate(OperateList opl);

private:
	Ui::BoardClass ui;
	Number*** numbers;
};
