#pragma once
#include "../abstract/ControllListener.h"
#include "../model/Matrix.h"
#include"../model/OperateList.h"

class Move
{
public:
	
	static OperateList move(Direction control, Matrix* matrix,int *score);
};

