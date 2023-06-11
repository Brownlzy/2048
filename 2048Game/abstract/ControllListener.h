#pragma once
#include "../model/enmu.h"
class ControllListener
{
public:
    virtual void onArrowControl(Direction control) = 0;
    virtual void onFuncControl(FuncControl control) = 0;
};
