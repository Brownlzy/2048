#pragma once
#include "../abstract/GameUI.h"
#include "../abstract/ControllListener.h"
#include "generate.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <QDateTime>

#include <cstdlib>
#include <ctime>
#include <QTime>
#include<QMessageBox>
#include <QWidget>
#include<qdebug.h>
#include <QRandomGenerator>

//#define TEST_ARRAY
#define START_NUM_COUNT 2

class MainControl:public ControllListener
{
private:
	GameUI* gui;
	Matrix* matrix=nullptr;
	static int round;
	std::map<int, int>records;
	int score=0;
	int maxs = 0;
	int aves = 0;

	bool isClassic = true;
	bool isNew =false;
	void init();
	void initGame();
	void quitGame();
	struct Ns {
		int i;
		int j;
	};

public:
	MainControl(GameUI* gui);
	void judgeEnd(Matrix matrix);
	void onArrowControl(Direction control);
	void onFuncControl(FuncControl control);
	
	void writeRecordsToFile(const std::map<int, int>& data, const QString filename);

	void addNewNumber(Matrix* matrix, OperateList* opl);

    void getLargest();
	void average();
	void SetAll();

	static OperateList* move(Direction direction, Matrix* matrix, int* score, bool* isNew);

};

