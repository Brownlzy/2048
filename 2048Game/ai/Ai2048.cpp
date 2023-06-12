#include "Ai2048.h"
#include <QDir>

PyObject* Ai2048::initPython()
{
	Py_SetPythonHome(L"E:\\CODE\\Project\\2048\\python\\");
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		printf("error!");
		PyErr_Print();	//��ӡ����
		return nullptr;
	}
	//�Ȼ��py�ļ����ڵ�·��������Ҫ����·��
	QString path = QDir::currentPath();
	path = path.replace("\\", "/");
	//qDebug() << path;
	path = "sys.path.append('" + path + "/pycode" + "')";
	QByteArray temp = path.toLocal8Bit();
	//������python����·��
	PyRun_SimpleString("import sys");
	PyRun_SimpleString(temp.data());
	PyRun_SimpleString("sys.path.append('E:\\CODE\\Project\\2048\\python\\Lib\\site-packages')");
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
