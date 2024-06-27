#ifndef BOARD_H
#define BOARD_H

#include "../include/DesignModel/subject.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <QVector>
#include <QString>

class Tile;

enum Direction { UP, DOWN, LEFT, RIGHT };

// Board 类继承自 被观察者类Subject
class Board:public Subject
{
public:
    // 构造函数
    Board(int dimension);
    // 拷贝构造函数
    Board(const Board& other);
    // 析构函数
    ~Board();
    // 将棋盘重置为初始状态（除了两个 2 之外其他都为空）
    void resret();
    // 获取指定位置的数字块
    Tile* getTile(int i, int j);
    // 获取棋盘维度
    int getDimension() const { return dimension; }
    // 移动数字块
    void move(Direction direction);
    // 检查棋盘是否已满
    bool full() const;
    // 获取上回合得分
    int getPointsScoredLastRound() const { return pointsScoredLastRound; }
    // 检查上回合是否发生瓷砖碰撞
    bool isTileCollisionLastRound() const { return tileCollisionLastRound; }
    // 检查是否还有可能的移动
    bool movePossible() const;

private:

    // 棋盘维度
    void init();
    // 生成一个随机的空闲位置
    QVector<int> freePosition();
    // 判断当前棋盘状态是否与传入的棋盘发生改变
    bool changed(Board& other)const;
    // 判断位置是否在边界内
    bool inbounds(int i,int j);
    // 改变状态！！（瓷砖碰撞和上回合得分）
    void moveHorizontally(int i, int j, Direction dir);
    void moveVertically(int i, int j, Direction dir);
    void handleCollision(int i, int j);

    // 为下一次移动进行一些重新初始化
    void prepareForNextMove();
private:
    // 棋盘矩阵
    QVector<QVector<Tile*>> board;
    int dimension;
    // 初始化一个空的棋盘
    // 上回合得分
        int pointsScoredLastRound;
    // 上回合是否发生数字块碰撞
        bool tileCollisionLastRound;

};

#endif // BOARD_H
