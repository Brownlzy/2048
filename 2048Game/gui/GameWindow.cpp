#pragma execution_character_set("utf-8")

#include "GameWindow.h"
#include <QLabel>
#include <QTimer>
#include <QMessageBox>

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
    setWindowTitle("2048");
    setFixedSize(361, 400);
    board = new Board(ui.widget);
    board->show();

    levelLabel=new QLabel("局数：1");
    nowLabel = new QLabel("得分：0");
    avgLabel = new QLabel("平均：0");
    maxLabel = new QLabel("最高：0");
    ui.statusBar->addWidget(levelLabel, 1);
    ui.statusBar->addWidget(nowLabel, 1);
    ui.statusBar->addWidget(maxLabel, 1);
    ui.statusBar->addWidget(avgLabel, 1);

    connect(ui.actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(ui.actionEndGame, SIGNAL(triggered()), this, SLOT(endGame()));
    connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui.actionAIMode, SIGNAL(triggered()), this, SLOT(setAi()));
}

void GameWindow::setGameState(GameState state)
{
    GameWindow::state = state;
    switch (state)
    {
    case READY:
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
    levelLabel->setText("局数：" + QString::number(level));
}

void GameWindow::setNowScore(int score)
{
    nowScore = score;
    nowLabel->setText("得分：" + QString::number(score));
}

void GameWindow::setAvgScore(int score)
{
    avgScore = score;
    avgLabel->setText("平均：" + QString::number(score));
}

void GameWindow::setMaxScore(int score)
{
    maxScore = score;
    maxLabel->setText("最高：" + QString::number(score));
}

void GameWindow::keyPress(int key)
{
    if (GameUI::listener == nullptr
        || state != GAMING
        || board->isAnimating()) return;
    switch (key)
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

Matrix* GameWindow::getNowMatrix()
{
    return matrix;
}

bool GameWindow::isAnimating()
{
    return board->isAnimating();
}

int GameWindow::getGameState()
{
    return state;
}

void GameWindow::showSuccessResult()
{
    if (QMessageBox::Yes == QMessageBox::question(this, "2048", "你已经成功通关！是否再来一次？", QMessageBox::Yes, QMessageBox::No)) {
        GameUI::listener->onFuncControl(START);
    }
}

void GameWindow::newGame()
{
    if (state == GAMING) {
        GameUI::listener->onFuncControl(END);
    }
    GameUI::listener->onFuncControl(START);
}

void GameWindow::endGame()
{
    GameUI::listener->onFuncControl(END);
}

void GameWindow::quit()
{
    GameUI::listener->onFuncControl(END);
    close();
}

void GameWindow::about()
{
    QMessageBox::information(this, "关于", "balabala...", QMessageBox::Yes);
}

void GameWindow::closeEvent(QCloseEvent* event)
{
    if (state==GAMING&&
        QMessageBox::No == QMessageBox::question(this, "2048", "确定要提前结束游戏并退出吗？", QMessageBox::Yes, QMessageBox::No))
    {
        event->ignore();
    }
    else
        GameUI::listener->onFuncControl(QUIT);
}

void GameWindow::setAi()
{
    if (ui.actionAIMode->isChecked()) {
        //TODO:启动AI
    } else {
        //TODO:停止AI
    }
}

void GameWindow::showFailResult()
{
    if (QMessageBox::Yes == QMessageBox::question(this, "2048", "你已经无路可走啦！是否重试？", QMessageBox::Yes, QMessageBox::No)) {
        GameUI::listener->onFuncControl(START);
    }
}

void GameWindow::keyPressEvent(QKeyEvent* e)
{
    keyPress(e->key());
}
