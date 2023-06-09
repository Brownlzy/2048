#pragma once
    enum ArrowControl { UP, DOWN, LEFT, RIGHT };
    enum FuncControl { START, END };
class ControllListener
{
public:
    virtual void onArrowControl(ArrowControl control) = 0;
    virtual void onFuncControl(FuncControl control) = 0;
};

