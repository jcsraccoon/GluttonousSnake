#include "snakepiece.h"

SnakePiece::SnakePiece()
{

}

SnakePiece::~SnakePiece()
{

}

void SnakePiece::moveSnakeGoingPiece(Direction moveDirection)
{
    snakeDirection = moveDirection;

    if ( Up == snakeDirection )
    {
        pieceY = pieceY-1;
    }
    else if ( Down == snakeDirection )
    {
        pieceY = pieceY+1;
    }
    else if ( Left == snakeDirection )
    {
        pieceX = pieceX-1;
    }
    else if ( Right == snakeDirection )
    {
        pieceX = pieceX+1;
    }
}

void SnakePiece::oppsiteMoveSnakeGoingPiece(Direction moveDirection)
{
    if ( Up == moveDirection )
    {
        moveSnakeGoingPiece(Down);
    }
    else if ( Down == moveDirection )
    {
        moveSnakeGoingPiece(Up);
    }
    else if ( Left == moveDirection )
    {
        moveSnakeGoingPiece(Right);
    }
    else if ( Right == moveDirection )
    {
        moveSnakeGoingPiece(Left);
    }
}
