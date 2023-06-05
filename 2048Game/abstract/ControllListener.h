#pragma once
class ControllListener
{
    enum ArrowControl { UP, DOWN, LEFT, RIGHT };
    enum FuncControl { START, END };
    virtual void onArrowControl(ArrowControl control) = 0;
    virtual void onFuncControl(FuncControl control) = 0;
};

