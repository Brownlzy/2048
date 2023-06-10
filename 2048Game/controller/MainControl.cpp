#include "MainControl.h"
#include "Move.h"
#include <QDebug>



int array[4][4]= { 0,0,0,2,
				   2,0,0,2,
				   2,0,0,4,
				   0,0,4,8 };
int inita[4][4] = { 0,0,0,0,
				  0,0,0,0,
				  0,0,0,0,
				  0,0,0,0 };

int MainControl::round = 0;

void MainControl::init()
{
	gui->setControlListener(this);
	matrix=new Matrix(inita);
	gen.addNewNumber(matrix);
	gen.addNewNumber(matrix);
	gui->setNowMatrix(matrix);
	matrix->printToConsole();
}


MainControl::MainControl(GameUI* gui)
{
	this->gui = gui;
	init();
}

void MainControl::onArrowControl(Direction control) {
	OperateList* opl = new OperateList;
	*opl=Move::move(control,matrix,&score);
	qDebug() << score;
	generate gen;
	gen.addNewNumber(matrix);
	gui->setNowScore(score);
	matrix->printToConsole();
	gui->setNowMatrix(matrix);
	gui->operate(*opl);
	judgeEnd(*matrix);
}


void MainControl::judgeEnd(Matrix matrix)
{
	int flag=0;
	for (int x = 0; x < 4; x++)
	{
		if (flag != 0)
			break;
		int* ax = matrix.getLineOnX(x);
		for (int i = 0; i < 4; i++)
		{
			if(ax[i] == 2048)
			{
				gui->setGameState(GameUI::SUCCESS);
				flag = -1;
				records.insert(std::pair<int, int>(round,score));
				break;
			}
			if (ax[i] == 0||ax[i] == matrix.getNumberIn(x+1,i)|| ax[i] == matrix.getNumberIn(x, i+1))
			{
				flag = -1;
				break;
			}
		}
	}
	if(flag==0)
	{
	gui->setGameState(GameUI::FAILED);
	records.insert(std::pair<int, int>(round, score));
	}
}

void MainControl::onFuncControl(FuncControl control) {
	if (control == START)
		round++;
	else
		records.insert(std::pair<int, int>(round, score));
}

