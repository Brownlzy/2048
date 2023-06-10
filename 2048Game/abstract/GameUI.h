#pragma once
#include "ControllListener.h"
#include "../model/Matrix.h"
#include "../model/OperateList.h"
#include "../model/enmu.h"

class GameUI {
protected:
    ControllListener* listener;
public:
    virtual void setGameState(GameState state) = 0;
    virtual void setNowMatrix(Matrix* matrix) = 0;
    virtual void setNewMatrix(Matrix* matrix) = 0;
    virtual void operate(OperateList* opl) = 0;
    virtual void setLevel(int level) = 0;
    virtual void setNowScore(int score) = 0;
    virtual void setAvgScore(int score) = 0;
    virtual void setMaxScore(int score) = 0;
    void setControlListener(ControllListener* listener) {
        GameUI::listener = listener;
    }
};
