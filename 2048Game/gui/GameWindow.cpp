#include "GameWindow.h"
#include <QLabel>
#include <QTimer>

GameWindow::GameWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initView();
    setFocusPolicy(Qt::StrongFocus);
}

GameWindow::~GameWindow()
{
}

void GameWindow::initView()
{
    setFixedSize(360, 400);
    board = new Board(ui.widget);
    board->show();
    levelLabel=new QLabel(QString::fromLocal8Bit("局数：1"));
    nowLabel = new QLabel(QString::fromLocal8Bit("得分：0"));
    avgLabel = new QLabel(QString::fromLocal8Bit("平均：0"));
    maxLabel = new QLabel(QString::fromLocal8Bit("最高：0"));
    //nowLabel->setAlignment(Qt::AlignCenter);
    //avgLabel->setAlignment(Qt::AlignCenter);
    //maxLabel->setAlignment(Qt::AlignRight);
    ui.statusBar->addWidget(levelLabel, 1);
    ui.statusBar->addWidget(nowLabel, 1);
    ui.statusBar->addWidget(maxLabel, 1);
    ui.statusBar->addWidget(avgLabel, 1);
}

void GameWindow::setGameState(GameState state)
{
    switch (state)
    {
    case READY:
        board->setNowMatrix(new Matrix());
        break;
    case GAMING:
        break;
    case SUCCESS:
        showSuccessResult();
        break;
    case FAILED:
        showFailResult();
        break;
    default:
        break;
    }
}

void GameWindow::setNowMatrix(Matrix* matrix)
{
    this->matrix = matrix;
    board->setNowMatrix(matrix);
}

void GameWindow::setNewMatrix(Matrix* matrix)
{
    this->matrix = matrix;
    board->setNewMatrix(matrix);
}

void GameWindow::operate(OperateList* opl)
{
    board->operate(opl);
}

void GameWindow::setLevel(int level)
{
    nowLevel = level;
    levelLabel->setText(QString::fromLocal8Bit("局数：") + QString::number(level));
}

void GameWindow::setNowScore(int score)
{
    nowScore = score;
    nowLabel->setText(QString::fromLocal8Bit("得分：") + QString::number(score));
}

void GameWindow::setAvgScore(int score)
{
    avgScore = score;
    avgLabel->setText(QString::fromLocal8Bit("平均：") + QString::number(score));
}

void GameWindow::setMaxScore(int score)
{
    maxScore = score;
    maxLabel->setText(QString::fromLocal8Bit("最高：") + QString::number(score));
}

void GameWindow::showSuccessResult()
{
}

void GameWindow::showFailResult()
{
}

void GameWindow::keyPressEvent(QKeyEvent* e)
{
    if (GameUI::listener == nullptr||board->isAnimating()) return;
    switch (e->key())
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        GameUI::listener->onArrowControl(UP);
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        GameUI::listener->onArrowControl(DOWN);
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        GameUI::listener->onArrowControl(LEFT);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        GameUI::listener->onArrowControl(RIGHT);
        break;
    default:
        break;
    }
}
