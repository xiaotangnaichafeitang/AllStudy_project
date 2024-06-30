#include "../include/Game_2048/core/board.h"
#include "../include/Game_2048/core/tile.h"

using namespace std;
Board::Board(int dimension)
{
    pointsScoredLastRound = 0;
    tileCollisionLastRound = false;
    this->dimension = dimension;
    init();
}

Board::Board(const Board &other)
{
    dimension = other.dimension;
    init();
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if(other.board[i][j] == NULL)
            {
                board[i][j] = NULL;
            }else {
                board[i][j] = new Tile(*(other.board[i][j]));
            }
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            delete board[i][j];
            board[i][j] = NULL;
        }
    }
}

void Board::reset()
{
    pointsScoredLastRound = 0;
    tileCollisionLastRound = false;

    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }

    QVector<int> start = freePosition();
    board[start[0]][start[1]] = new Tile();
    start = freePosition();
    board[start[0]][start[1]] = new Tile();
}

Tile* Board::getTile(int i, int j)
{
    return board[i][j];
}

int Board::getDimension() const { return dimension; }

void Board::move(Direction direction)
{
    Board pre_move_board(*this);

    prepareForNextMove();

    switch (direction) {
    case UP:
        for (int i = 0; i < dimension; ++i)
            for (int j = 0; j < dimension; ++j)
                moveVertically(i,j,UP);
        break;
    case DOWN:
        for (int i = dimension-1; i >= 0; --i)
            for (int j = 0; j < dimension; ++j)
                moveVertically(i,j,DOWN);
        break;
    case LEFT:
        for (int i = 0; i < dimension; ++i)
            for (int j = 0; j < dimension; ++j)
                moveHorizontally(i,j,LEFT);
        break;
    case RIGHT:
        for (int i = 0; i < dimension; ++i)
            for (int j = dimension-1; j >= 0; --j)
                moveHorizontally(i,j, RIGHT);
    }

    // 如果棋盘发生了变化（并且没有发生块碰撞），则放置一个新的数字块
    if (changed(pre_move_board) /*&& !tileCollisionLastRound*/) {
        QVector<int> newpos = freePosition();
        board[newpos[0]][newpos[1]] = new Tile();
    }
    // 通知观察者们
    notifyObservers();
}

bool Board::full() const
{
    bool full = true;
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            if (board[i][j] == NULL)
                full = false;
    return full;
}

bool Board::isTileCollisionLastRound() const { return tileCollisionLastRound; }

int Board::getPointsScoredLastRound() const { return pointsScoredLastRound; }

bool Board::movePossible() const
{
    if (full()) {
        // 检查是否还可以移动
        Board newBoard(*this);
        newBoard.move(UP);
        if (changed(newBoard)) {
            return true;
        }
        newBoard.move(DOWN);
        if (changed(newBoard)) {
            return true;
        }
        newBoard.move(LEFT);
        if (changed(newBoard)) {
            return true;
        }
        newBoard.move(RIGHT);
        if (changed(newBoard)) {
            return true;
        }

        // no possible move
        return false;
    }
    else {
        return true;
    }
}

void Board::init()
{
    board.resize(dimension);
    for (int i = 0; i < dimension; ++i)
        board[i].resize(dimension);
    for (int i = 0; i < dimension; ++i)
        for (int j = 0; j < dimension; ++j)
            board[i][j] = nullptr;
}


QVector<int> Board:: freePosition()
{
    QVector<int> pos;
    if(full()){
        pos.append(-1);
        pos.append(-1);
    }else{
        int i,j;
        do{
            i = rand() % dimension;
            j = rand() % dimension;
        }while(board[i][j] != NULL);
        pos.append(i);
        pos.append(j);
    }
    return pos;
}

bool Board::changed(Board &other) const
{
    if (dimension != other.dimension){
        return false;
    }
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; ++j){
            if ( ( (board[i][j] == NULL && other.board[i][j] != NULL) ||
                 (board[i][j] != NULL && other.board[i][j] == NULL) ) ||
                ( (board[i][j] != NULL && other.board[i][j] != NULL) &&
                 board[i][j]->getValue() != other.board[i][j]->getValue()) )
            {
                return true;
            }
        }

    }
    return false;
}

bool Board::inbounds(int i, int j)
{

    return (i >= 0 && j >= 0 && i < dimension && j < dimension);

}

void Board::moveHorizontally(int i, int j, Direction dir)
{
    if (board[i][j] != NULL) {
        bool tileCollision = false;
        int newj;
        if (dir == RIGHT)
            newj = j + 1;
        // to the left to the left
        else
            newj = j - 1;

        // 沿着 dir 方向继续移动，直到遇到障碍或者越界
        while (inbounds(i,newj) && board[i][newj] == NULL) {
            if (dir == RIGHT)
                newj++;
            else
                newj--;
        }

        // 越界处理或者...
        if (!inbounds(i,newj)) {
            if (dir == RIGHT)
                board[i][dimension-1] = board[i][j];
            else
                board[i][0] = board[i][j];
        }
        // ... 发生了碰撞
        else {
            // 与数值相同的块发生碰撞
            if (board[i][newj]->getValue() == board[i][j]->getValue() &&
                !board[i][newj]->getUpgratedThisMove()) {

                tileCollision = true;
                handleCollision(i, newj);
            }
            // 与数值不同的块发生碰撞，将当前块放置在其旁边
            else {
                if (dir == RIGHT)
                    board[i][newj-1] = board[i][j];
                else
                    board[i][newj+1] = board[i][j];
            }
        }
        // 如果移动了多步或者与相邻块合并，则移除原始块
        if ( (dir == RIGHT && newj-1 != j) || (dir == LEFT && newj+1 != j) || tileCollision )
            board[i][j] = NULL;

        if (tileCollision)
            tileCollisionLastRound = true;
    }
}

void Board::moveVertically(int i, int j, Direction dir)
{
    if (board[i][j] != NULL) {
        bool tileCollision = false;
        int newi;
        if (dir == UP)
            newi = i - 1;
        // 向下移动
        else
            newi = i + 1;

        // 沿着 dir 方向继续移动，直到遇到障碍或者越界
        while (inbounds(newi,j) && board[newi][j] == NULL) {
            if (dir == UP)
                newi--;
            else
                newi++;
        }

        // 越界处理或者...
        if (!inbounds(newi,j)) {
            if (dir == UP)
                board[0][j] = board[i][j];
            else
                board[dimension-1][j] = board[i][j];
        }
        // ... 发生了碰撞
        else {
            // 与数值相同的块发生碰撞
            if (board[newi][j]->getValue() == board[i][j]->getValue() &&
                !board[newi][j]->getUpgratedThisMove()) {
                tileCollision = true;
                handleCollision(newi, j);
            }
            // 与数值不同的块发生碰撞，将当前块放置在其旁边
            else {
                if (dir == UP)
                    board[newi+1][j] = board[i][j];
                else
                    board[newi-1][j] = board[i][j];
            }
        }
        // 如果移动了多步或者与相邻块合并，则移除原始块
        if ( (dir == UP && newi+1 != i) || (dir == DOWN && newi-1 != i) || tileCollision )
            board[i][j] = NULL;

        if (tileCollision)
            tileCollisionLastRound = true;
    }
}

void Board::handleCollision(int i, int j)
{
    board[i][j]->upgrade();
    board[i][j]->setUpgratedThisMove(true);
    pointsScoredLastRound += board[i][j]->getValue();
}

void Board::prepareForNextMove()
{
    tileCollisionLastRound = false;
    pointsScoredLastRound = 0;
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (board[i][j] != nullptr) {
                board[i][j]->setUpgratedThisMove(false);
            }
        }
    }
}

// TODO感觉上面可以优化成
// Board::Board(int dimension)
//     : dimension(dimension), pointsScoredLastRound(0), tileCollisionLastRound(false) {
//     init();
// }

// Board::Board(const Board &other)
//     : dimension(other.dimension), pointsScoredLastRound(0), tileCollisionLastRound(false) {
//     init();
//     for (int i = 0; i < dimension; ++i) {
//         for (int j = 0; j < dimension; ++j) {
//             if (other.board[i][j] == nullptr) {
//                 board[i][j] = nullptr;
//             } else {
//                 board[i][j] = new Tile(*(other.board[i][j]));
//             }
//         }
//     }
// }

// Board::~Board() {
//     for (int i = 0; i < dimension; ++i) {
//         for (int j = 0; j < dimension; ++j) {
//             delete board[i][j];
//             board[i][j] = nullptr;
//         }
//     }
// }

// void Board::init() {
//     board.resize(dimension);
//     for (int i = 0; i < dimension; ++i) {
//         board[i].resize(dimension);
//         for (int j = 0; j < dimension; ++j) {
//             board[i][j] = nullptr;
//         }
//     }
// }


