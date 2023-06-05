#pragma once
#include "ControllListener.h"
#include "../model/Matrix.h"
class GameUI {
private:
    ControllListener* listener;
public:
    enum GameState { READY, GAMING, SUCCESS, FAILED };
    virtual void setGameState(GameState state) = 0;
    virtual void setNowMatrix(Matrix matrix) = 0;
    virtual void mergeTo(int x1, int y1, int x2, int y2, int dex, int dey) = 0;
    virtual void moveTo(int x, int y, int dx, int dy) = 0;
    virtual void newIn(int x, int y, int value) = 0;
    virtual void setNowScore(int score) = 0;
    virtual void setMaxScore(int score) = 0;
    void setControlListener(ControllListener* listener) {
        GameUI::listener = listener;
    }
};
