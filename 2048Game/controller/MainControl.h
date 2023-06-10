#pragma once
#include "../abstract/GameUI.h"
#include "../abstract/ControllListener.h"
#include "../generate/generate.h"
class MainControl:public ControllListener
{
private:
	GameUI* gui;
	Matrix* matrix;
	generate gen;
	int score=0;
	void init();

public:
	MainControl(GameUI* gui);

	void judgeEnd(Matrix matrix);
	void onArrowControl(Direction control);
	void onFuncControl(FuncControl control);
};

