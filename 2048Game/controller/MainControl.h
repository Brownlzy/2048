#pragma once
#include "../abstract/GameUI.h"
#include "../abstract/ControllListener.h"
#include "../generate/generate.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
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
	
	//读文件（统计最大和平均值）
	std::map<int, int> readMapFromFile(const std::string& filename);
	//写文件:两种，一种是将<int,int>，另一种是<int,double>
	void writeRecordsToFile(const std::map<int, int>& data, const std::string& filename);
	void writeRecordsToFile(const std::map<int, double>& data, const std::string& filename);
	//统计最大数和平均值
	void sum();

};

