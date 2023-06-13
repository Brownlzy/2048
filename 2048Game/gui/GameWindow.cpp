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

    // 实例化子线程
    thread = new QThread;
    // 实例化子线程对象
    ai = new Ai2048();
    // 将子线程对象移到子线程
    ai->moveToThread(thread);
    // 线程finished->线程自己deleteLater
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    // 线程finished->线程对象deleteLater
    connect(thread, &QThread::finished, ai, &Ai2048::deleteLater);
    // 主线程发送信号->线程对象启动run函数
    connect(this, &GameWindow::getNextMove, ai, &Ai2048::getBestMove);
    // 接收线程实体运行结束发送的信号，在回调里quit，quit之后会接收到finished，然后再根据finished消息进一步操作
    connect(ai, &Ai2048::sendResult, this, &GameWindow::keyPress);

    thread->start();
}

GameWindow::~GameWindow()
{
    if (thread!=nullptr) {
        thread->quit();
        thread->wait();
        thread->deleteLater();
        thread = NULL;
        ai->~Ai2048();
    }
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

    ui.actionClassic->setChecked(true);
    ui.actionAnimation->setChecked(true);

    connect(ui.actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(ui.actionEndGame, SIGNAL(triggered()), this, SLOT(endGame()));
    connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui.actionGameRule, SIGNAL(triggered()), this, SLOT(showRule()));
    connect(ui.actionAIMode, SIGNAL(triggered()), this, SLOT(setAi()));
    connect(ui.actionClassic, SIGNAL(triggered()), this, SLOT(setClassic()));
    connect(ui.actionAnimation, SIGNAL(triggered()), this, SLOT(setAnimation()));

    connect(board, SIGNAL(animationEnded()), this, SLOT(animationEnded()));
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
    case 1:
    case Qt::Key_W:
    case Qt::Key_Up:
        GameUI::listener->onArrowControl(UP);
        break;
    case 2:
    case Qt::Key_S:
    case Qt::Key_Down:
        GameUI::listener->onArrowControl(DOWN);
        break;
    case 3:
    case Qt::Key_A:
    case Qt::Key_Left:
        GameUI::listener->onArrowControl(LEFT);
        break;
    case 4:
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
    if (ui.actionAIMode->isChecked()) {
        newGame();
    }else if (QMessageBox::Yes == QMessageBox::question(this, "2048", "你已经成功通关！是否再来一次？", QMessageBox::Yes, QMessageBox::No)) {
        GameUI::listener->onFuncControl(START);
    }
}

void GameWindow::newGame()
{
    if (state == GAMING) {
        GameUI::listener->onFuncControl(END);
    }
    GameUI::listener->onFuncControl(START);
    //if (ui.actionAIMode->isChecked())
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
    {
        GameUI::listener->onFuncControl(QUIT);
        exit(0);
    }
}

void GameWindow::setAi()
{
    if (ui.actionAIMode->isChecked()) {
        GameUI::listener->onFuncControl(ENABLEAI);
        if (state == GAMING)
            emit getNextMove(matrix,1);

    } else {
        GameUI::listener->onFuncControl(DISABLEAI);
    }
}

void GameWindow::setAnimation()
{
    board->setAnimation(ui.actionAnimation->isChecked());
}

void GameWindow::setClassic()
{
    if(ui.actionClassic->isChecked())
        GameUI::listener->onFuncControl(CLASSIC);
    else
        GameUI::listener->onFuncControl(MINFINITY);
}

void GameWindow::showRule()
{
    QMessageBox::information(this, "游戏规则", "balabala...", QMessageBox::Yes);
}

void GameWindow::animationEnded()
{
    if(ui.actionAIMode->isChecked())
    {
        if(state==GAMING)
        {
            emit getNextMove(matrix, 50);
        }
    }
}

void GameWindow::showFailResult()
{
    if (ui.actionAIMode->isChecked()) {
        newGame();
    }else if (QMessageBox::Yes == QMessageBox::question(this, "2048", "你已经无路可走啦！是否重试？", QMessageBox::Yes, QMessageBox::No)) {
        GameUI::listener->onFuncControl(START);
    }
}

void GameWindow::keyPressEvent(QKeyEvent* e)
{
    if(!ui.actionAIMode->isChecked())
        keyPress(e->key());
}
