#include "GameWindow.h"
#include <QLabel>
GameWindow::GameWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initView();
    setFocusPolicy(Qt::StrongFocus);
}

GameWindow::~GameWindow()
{}

void GameWindow::initView()
{
    setFixedSize(360, 400);
    board = new Board(ui.widget);
    board->show();
}

void GameWindow::setGameState(GameState state)
{
    switch (state)
    {
    case GameUI::READY:
        board->setNowMatrix(new Matrix());
        break;
    case GameUI::GAMING:
        break;
    case GameUI::SUCCESS:
        showSuccessResult();
        break;
    case GameUI::FAILED:
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

void GameWindow::operate(OperateList opl)
{
    board->operate(opl);
}

void GameWindow::setNowScore(int score)
{
    nowScore = score;
}

void GameWindow::setMaxScore(int score)
{
    maxScore = score;
}

void GameWindow::showSuccessResult()
{
}

void GameWindow::showFailResult()
{
}

void GameWindow::keyPressEvent(QKeyEvent* e)
{
    if (GameUI::listener == nullptr) return;
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
