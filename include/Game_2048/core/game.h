#ifndef GAME_H
#define GAME_H

#define WINNING_VALUE 2048

#include "../include/Game_2048/core/board.h"
#include "../include/DesignModel/subject.h"

class Game : public Subject
{
public:
    // 构造函数，初始化一个指定维度的游戏
    Game(int dimension);
    // 析构函数，释放游戏资源
    ~Game();
// 重新开始游戏，初始化游戏状态
    void restart();
    // 判断游戏是否结束
    bool isGameOver() const { return gameOver; }
    // 获取游戏棋盘对象的指针
    Board* getGameBoard() const { return board; }
    // 根据移动方向移动棋盘
    void move(Direction dir);

    // 判断游戏是否达到胜利状态
    // 即是否存在一个棋子的值等于 WINNING_VALUE
    bool won() const;
    // 获取当前游戏分数
    int getScore() const { return score; }


private:
    Board* board;
    bool gameOver;
    int score;
};
#endif // GAME_H
