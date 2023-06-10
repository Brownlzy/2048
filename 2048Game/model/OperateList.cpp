#include "OperateList.h"

OperateList::~OperateList()
{
	while (operateList.size() > 0) {
		delete operateList.back();
		operateList.pop_back();
	}
}

void OperateList::clear()
{
	for (size_t i = 0; i < operateList.size(); i++)
	{
		delete[] operateList[i];
	}
	operateList.clear();
}

void OperateList::addOperate(Operate* p)
{
	operateList.push_back(p);
	//p->printToConsole();
}

int OperateList::getCount()
{
	return operateList.size();
}

Operate* OperateList::getOperate(int pos)
{
	return operateList.at(pos);
}
