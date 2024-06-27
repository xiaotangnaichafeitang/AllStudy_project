#ifndef TILE_H
#define TILE_H

// 定义一个常量倍数
#define EXP_MULTIPLIER 2

// Tile 类表示棋盘上的一个数字块
class Tile
{
public:
    // 默认构造函数，初始化值为2，并且本次移动未升级
    Tile(){value = 2; upgratedThisMove = false;};
    // 拷贝构造函数,从另外一个Tile对象复制值
    Tile(const Tile& other){ this->value = other.value; }
    // 带参数构造函数,初始化值为传入的参数
    Tile(int value){ this->value = value;}
    // 获取数字块的当前值
    int getValue(){return value;}
    //将数字块的值乘以EXP_MULTIPLIER进行升级
    void upgrade(){
        // value *= EXP_MULTIPLIER;
        value <<= 1;
    }
    // 设置瓷砖是否在本次移动中被升级
    void setUpgratedThisMove(bool updated) { this->upgratedThisMove = updated; }

    // 获取瓷砖是否在本次移动中被升级的状态
    bool getUpgratedThisMove() const { return this->upgratedThisMove; }

private:
    // 数字块值
    int value;
    // 数字块是否在本次移动中被升级
    bool upgratedThisMove;
};

#endif // TILE_H
