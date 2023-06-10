#include "MainControl.h"
#include "Move.h"

int array[4][4]= { 0,0,0,2,0,0,0,2,2,0,0,4,0,0,4,8 };
int test[4][4] = { 0,0,0,0,
				  4,0,0,0,
				  0,0,0,0,
				  2,0,0,0 };

void MainControl::init()
{
	gui->setControlListener(this);
	matrix=new Matrix(array);
	gui->setNowMatrix(matrix);
	matrix->printToConsole();
}


MainControl::MainControl(GameUI* gui)
{
	this->gui = gui;
	init();
}

void MainControl::onArrowControl(Direction control) {

	OperateList opl=Move::move(control,matrix);
	matrix->printToConsole();
	gui->operate(opl);
	gui->setNowMatrix(matrix);
}

void MainControl::onFuncControl(FuncControl control) {

}

