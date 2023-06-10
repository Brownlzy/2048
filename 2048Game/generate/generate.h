#pragma once
#include "../model/Matrix.h"
#include <cstdlib>
#include <ctime>
#include <QTime>
#include<QMessageBox>
#include <QWidget>
#include<qdebug.h>
#define SIZE 4
class generate
{
	//位置坐标，用于矩阵中的空白格搜索
	struct Ns {
		int i;
		int j;
	};
	int ma[4][4];
public:

	generate();
	//生成随机数2
	void addNewNumber(Matrix *m);
};

