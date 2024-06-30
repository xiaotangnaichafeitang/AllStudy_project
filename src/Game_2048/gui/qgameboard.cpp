#include "../include/Game_2048/core/board.h"
#include "../include/Game_2048/core/game.h"
#include "../include/Game_2048/core/tile.h"

#include "../include/Game_2048/gui/qgameboard.h"
#include "../include/Game_2048/gui/qresetbutton.h"
#include "../include/Game_2048/gui/qtile.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>

QGameBoard::~QGameBoard()
{
    delete game;
}

QGameBoard::QGameBoard(QWidget *parent) :
    QWidget(parent)
{
    // 设置游戏板的初始大小为650x450像素
    resize(650,450);
    // 创建垂直布局管理器
    mainLayout = new QVBoxLayout();
    // 将主布局设置为当前窗口的布局
    setLayout(mainLayout);
    // 初始化游戏板布局为NULL
    boardLayout = NULL;

    // 创建游戏对象并注册为观察者
    game = new Game(4); // 创建一个4x4的游戏对象
    game->registerObserver(this);// 注册当前窗口为游戏的观察者

    // 创建GUI游戏板并绘制初始状态
    gui_board.resize(game->getGameBoard()->getDimension());
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i)
        gui_board[i].resize(game->getGameBoard()->getDimension());
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i)
        for (int j = 0; j < game->getGameBoard()->getDimension(); ++j)
            gui_board[i][j] = NULL;
    drawBoard(); // 绘制游戏板的初始状态

    // create the score widget and add it to the board
    score = new QLabel(QString("SCORE: %1").arg(game->getScore()));
    score->setStyleSheet("QLabel { color: rgb(235,224,214); font: 16pt; }");
    score->setFixedHeight(50);
    mainLayout->insertWidget(1, score, 0, Qt::AlignRight);

    // 样式表
    setStyleSheet("QGameBoard { background-color: rgb(187,173,160) }");

    connect(gameOverWindow.getResetBtn(), SIGNAL(clicked()), this, SLOT(resetGame()));
}

void QGameBoard::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        game->move(UP);
        break;
    case Qt::Key_Left:
        game->move(LEFT);
        break;
    case Qt::Key_Right:
        game->move(RIGHT);
        break;
    case Qt::Key_Down:
        game->move(DOWN);
        break;
    }
}

void QGameBoard::notify()
{
    if (game->isGameOver())
        gameOverWindow.show();

    if (game->won())
        score->setText(QString("You hit 2048, congratulations! Keep playing to increase your score.\t\t SCORE: %1").arg(game->getScore()));
    else
        score->setText(QString("SCORE: %1").arg(game->getScore()));

    drawBoard();
}

void QGameBoard::drawBoard()
{
    delete boardLayout;
    boardLayout = new QGridLayout();
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i) {
        for (int j = 0; j < game->getGameBoard()->getDimension(); ++j) {
            delete gui_board[i][j];
            gui_board[i][j] = new QTile(game->getGameBoard()->getTile(i,j));
            boardLayout->addWidget(gui_board[i][j], i, j);
            gui_board[i][j]->draw();
        }
    }
    mainLayout->insertLayout(0, boardLayout);
}

void QGameBoard::resetGame()
{
    game->restart();
    drawBoard();
    score->setText(QString("SCORE: %1").arg(game->getScore()));
    gameOverWindow.hide();
}
