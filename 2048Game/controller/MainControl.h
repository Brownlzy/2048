#pragma once
#include "../abstract/GameUI.h"
#include "../abstract/ControllListener.h"
#include "generate.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <QDateTime>

//#define TEST_ARRAY
#define START_NUM_COUNT 2

class MainControl:public ControllListener
{
private:
	GameUI* gui;
	Matrix* matrix=nullptr;
	static int round;
	std::map<int, int>records;
	generate gen;
	int score=0;
	int maxs = 0;
	int aves = 0;

	bool isClassic = true;
	bool isNew =false;
	void init();
	void initGame();
	void quitGame();

public:
	MainControl(GameUI* gui);
	void judgeEnd(Matrix matrix);
	void onArrowControl(Direction control);
	void onFuncControl(FuncControl control);
	
	std::map<int, int> readMapFromFile(const std::string& filename);
	void writeRecordsToFile(const std::map<int, int>& data, const QString filename);

    void getLargest();
	void average();
	void SetAll();

};

