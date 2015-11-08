#ifndef SNAKEPIECE_H
#define SNAKEPIECE_H

#include <QtWidgets>

enum Direction {Up, Down, Left, Right};

class SnakePiece
{
public:
    SnakePiece( int in_x, int in_y, Direction in_temp ) : pieceX(in_x), pieceY(in_y), snakeDirection(in_temp) {}
    SnakePiece();
    ~SnakePiece();

    int getPieceX() { return pieceX; }
    int getPieceY() { return pieceY; }
    Direction getSnakeDirection() { return snakeDirection; }

    void moveSnakeGoingPiece(Direction moveDirection);   //计算要移动点的坐标
    void oppsiteMoveSnakeGoingPiece(Direction moveDirection);   //增加蛇，按照蛇尾点的相反方向加一点
private:
    int pieceX;
    int pieceY;
    Direction snakeDirection;
};

#endif // SNAKEPIECE_H
