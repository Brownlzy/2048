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
	//λ�����꣬���ھ����еĿհ׸�����
	struct Ns {
		int i;
		int j;
	};
	int ma[4][4];
public:

	generate();
	//���������2
	void addNewNumber(Matrix *m);
};

