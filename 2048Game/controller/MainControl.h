#pragma once
#include "../abstract/GameUI.h"
#include "../abstract/ControllListener.h"

class MainControl:public ControllListener
{
private:
	GameUI* gui;
	Matrix* matrix;
	void init();

public:
	MainControl(GameUI* gui);

	void onArrowControl(Direction control);
	void onFuncControl(FuncControl control);
};

