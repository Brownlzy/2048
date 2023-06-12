#pragma once

#include <QObject>
#include "../model/Matrix.h"
#include <QMetaObject>

#undef slots
#include <Python.h>
#include "../abstract/GameUI.h"
#define slots Q_SLOTS

class Ai2048  : public QObject
{
	Q_OBJECT

private:
	PyObject* pythonModule = nullptr;
	PyObject* initPython();
	void releasePython();
	Direction dir=NONE;

public:
	Direction getDirection();
	explicit Ai2048(QObject *parent=0);
	~Ai2048();

signals:
	void sendResult(int key);

public slots:
	int getBestMove(Matrix* mat, int n);
};
