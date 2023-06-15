#pragma once

#include <QObject>
#include "../model/Matrix.h"
#include <QMetaObject>

#undef slots
#include <Python.h>
#include "../abstract/GameUI.h"
#include "AI.h"
#define slots Q_SLOTS

class Ai2048  : public QObject
{
	Q_OBJECT

private:
	PyObject* pythonModule = nullptr;
	PyObject* initPython();
	void releasePython();
	Direction dir=NONE;
	AI* a;

public:
	Direction getDirection();
	explicit Ai2048(QObject *parent=0);
	~Ai2048();
	void init();

signals:
	void sendResult(int key);

public slots:
	int getBestMove1(Matrix* mat, int n);
	int getBestMove2(Matrix* mat);
};
