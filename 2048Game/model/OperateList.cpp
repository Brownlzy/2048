#include "OperateList.h"

void OperateList::clear()
{
	operateList.clear();
}

void OperateList::addOperate(Operate* p)
{
	operateList.push_back(p);
}
