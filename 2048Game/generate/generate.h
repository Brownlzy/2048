#pragma once
#include "../model/Matrix.h"
#include <cstdlib>
#include <ctime>
#include <QTime>
#include<QMessageBox>
#include <QWidget>
#define SIZE 4
class generate
{
	QWidget *widget;
	int score;
	struct Ns {
		int i;
		int j;
	};
	int ma[4][4];
public:
	generate();

	void addNewNumber();
};

