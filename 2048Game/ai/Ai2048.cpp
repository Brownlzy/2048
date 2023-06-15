#include "Ai2048.h"
#include <QDir>

PyObject* Ai2048::initPython()
{
	//�Ȼ��py�ļ����ڵ�·��������Ҫ����·��
	QString path = QDir::currentPath();
	path = path.replace("\\", "/");
	QString python = path + "/../python/";
	Py_SetPythonHome(python.toStdWString().c_str());
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		printf("error!");
		PyErr_Print();	//��ӡ����
		return nullptr;
	}
	//qDebug() << path;
	QString pycode = "sys.path.append('" + path + "/pycode" + "')";
	QByteArray temp = pycode.toLocal8Bit();
	//������python����·��
	PyRun_SimpleString("import sys");
	PyRun_SimpleString(temp.data());
	QString pythonLib = "sys.path.append('"+path+"/../python/Lib/site-packages')";
	temp = pythonLib.toLocal8Bit();
	PyRun_SimpleString(temp.data());
	//����ģ��
	PyObject* pModule = PyImport_ImportModule("main");
	pythonModule = pModule;
	return pModule;
}

void Ai2048::releasePython()
{
	//�������ͷ�python
	Py_Finalize();
}

void Ai2048::init()
{
	AI a;
}

Direction Ai2048::getDirection()
{
	Direction temp = dir;
	dir = NONE;
	return dir;
}

Ai2048::Ai2048(QObject *parent)
	: QObject(parent)
{
	initPython();
}

Ai2048::~Ai2048()
{
	releasePython();
}

int Ai2048::getBestMove(Matrix* mat)
{
	int** array = new int* [4];
	for (int i = 0; i < 4; ++i) {
		array[i] = new int[4];
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			array[i][j] = mat->getNumberIn(i, j);
		}
	}
	int result = a.play_game(array)+1;
	if (result)
	{
		switch (result)
		{
		case 1:
			dir = UP;
			break;
		case 2:
			dir = DOWN;
			break;
		case 3:
			dir = LEFT;
			break;
		case 4:
			dir = RIGHT;
			break;
		default:
			dir = NONE;
			break;
		}
		emit sendResult(result);
		return result;
	}
}

int Ai2048::getBestMove(Matrix * mat, int n)
{
	PyObject* pFunc = PyObject_GetAttrString(pythonModule, "get_next_best_move2");
	if (pFunc)
	{
		//���������б�
		PyObject* args = PyTuple_New(17);//����һ��python����
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
			{
				PyTuple_SetItem(args, i * 4 + j, PyLong_FromLong(mat->getNumberIn(i, j)));// ������ʽת����python��ʽ
			}
		}
		PyTuple_SetItem(args, 16, PyLong_FromLong(n));// ������ʽת����python��ʽ

		PyObject* result = PyObject_CallObject(pFunc, args);
		if (result)
		{
			long direction = PyLong_AsLong(result);
			switch (direction)
			{
			case 1:
				dir = UP;
				break;
			case 2:
				dir = DOWN;
				break;
			case 3:
				dir = LEFT;
				break;
			case 4:
				dir = RIGHT;
				break;
			default:
				dir = NONE;
				break;
			}
			emit sendResult(direction);
			return direction;
		}
	}
}
