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
	
	//���ļ���ͳ������ƽ��ֵ��
	std::map<int, int> readMapFromFile(const std::string& filename);
	//д�ļ�:���֣�һ���ǽ�<int,int>����һ����<int,double>
	void writeRecordsToFile(const std::map<int, int>& data, const std::string& filename);
	void writeRecordsToFile(const std::map<int, double>& data, const std::string& filename);
	//ͳ���������ƽ��ֵ
	void sum();

};

