#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GameWindow.h"
#include "../abstract/GameUI.h"
#include "Board.h"
#include <QKeyEvent>
#include <QCloseEvent>

class GameWindow : public QMainWindow , public GameUI
{
    Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr);
    ~GameWindow();
    void setGameState(GameState state);
    void setNowMatrix(Matrix* matrix);
    void setNewMatrix(Matrix* matrix);
    void operate(OperateList* opl);
    void setLevel(int level);
    void setNowScore(int score);
    void setAvgScore(int score);
    void setMaxScore(int score);

private:
    Ui::GameWindowClass ui;
    Board* board;
    Matrix* matrix;
    GameState state=FAILED;
    int nowLevel = 1;
    int nowScore = 0;
    int avgScore = 0;
    int maxScore = 0;
    QLabel* levelLabel;
    QLabel* nowLabel;
    QLabel* avgLabel;
    QLabel* maxLabel;

    void initView();
    void showSuccessResult();
    void showFailResult();

public slots:
    void keyPressEvent(QKeyEvent* e);
    void newGame();
    void endGame();
    void quit();
    void about();
    void closeEvent(QCloseEvent* event);
};
