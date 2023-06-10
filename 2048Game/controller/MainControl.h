#pragma once
#include "../abstract/GameUI.h"
#include "../abstract/ControllListener.h"
#include "../generate/generate.h"
#include <map>
class MainControl:public ControllListener
{
private:
	GameUI* gui;
	Matrix* matrix;
	static int round;
	std::map<int, int>records;
	generate gen;
	int score=0;
	void init();

public:
	MainControl(GameUI* gui);
	void judgeEnd(Matrix matrix);
	void onArrowControl(Direction control);
	void onFuncControl(FuncControl control);
};

