#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameWindow.h"
#include "../abstract/GameUI.h"
#include "Board.h"
#include <QKeyEvent>

class GameWindow : public QMainWindow , public GameUI
{
    Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr);
    ~GameWindow();
    void initView();
    void setGameState(GameState state);
    void setNowMatrix(Matrix* matrix);
    void operate(OperateList opl);
    void setNowScore(int score);
    void setMaxScore(int score);

private:
    Ui::GameWindowClass ui;
    Board* board;
    Matrix* matrix;
    int nowScore = 0;
    int maxScore = 0;

    void showSuccessResult();
    void showFailResult();

public slots:
    void keyPressEvent(QKeyEvent* e);
};
