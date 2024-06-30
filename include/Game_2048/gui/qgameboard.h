#ifndef QGAMEBOARD_H
#define QGAMEBOARD_H

#include "../include/DesignModel/observer.h"
#include "../include/Game_2048/gui/qgameoverwindow.h"

#include <QVector>
#include <QWidget>

class Game;

class QResetButton;
class QKeyEvent;
class QTile;
class QGridLayout;
class QVBoxLayout;
class QLabel;

class QGameBoard :public QWidget, public Observer
{
    Q_OBJECT
public:
    explicit QGameBoard (QWidget *parent = 0);
    ~QGameBoard();

    void notify();
private:
    Game* game;
    // 游戏面板
    QVector<QVector<QTile*> > gui_board;
    // 主布局，用于安排游戏面板和其他UI元素
    QVBoxLayout *mainLayout;
    // 网格布局，用于安排游戏面板的数据块
    QGridLayout *boardLayout;
    // 显示分数的标签
    QLabel *score;
    // 游戏结束窗口
    QGameOverWindow gameOverWindow;
    // 显示胜利信息的标签
    QLabel *youwin;

    // 绘制游戏面板的函数
    void drawBoard();
protected:
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void resetGame();
};

#endif // QGAMEBOARD_H
