#include "Ai2048.h"
#include <QDir>

PyObject* Ai2048::initPython()
{
	Py_SetPythonHome(L"'D:\\python\\3.9.13");
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		printf("error!");
		PyErr_Print();	//打印错误
		return nullptr;
	}
	//先获得py文件所在的路径，必须要绝对路径
	QString path = QDir::currentPath();
	path = path.replace("\\", "/");
	//qDebug() << path;
	path = "sys.path.append('" + path + "/pycode" + "')";
	QByteArray temp = path.toLocal8Bit();
	//再设置python运行路径
	PyRun_SimpleString("import sys");
	PyRun_SimpleString(temp.data());
	PyRun_SimpleString("sys.path.append('D:\\python\\3.9.13\\Lib\\site-packages')");
	//导入模块
	PyObject* pModule = PyImport_ImportModule("main");
	pythonModule = pModule;
	return pModule;
}

void Ai2048::releasePython()
{
	//结束，释放python
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
		//创建参数列表
		PyObject* args = PyTuple_New(17);//定义一个python变量
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
			{
				PyTuple_SetItem(args, i * 4 + j, PyLong_FromLong(mat->getNumberIn(i, j)));// 变量格式转换成python格式
			}
		}
		PyTuple_SetItem(args, 16, PyLong_FromLong(n));// 变量格式转换成python格式

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
