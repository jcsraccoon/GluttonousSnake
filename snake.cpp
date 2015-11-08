#include "snake.h"
#include "ui_snake.h"

Snake::Snake(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Snake)
{
    ui->setupUi(this);

    this->initSnake();

}

Snake::~Snake()
{
    delete ui;
}

void Snake::initSnake()
{  
    for ( int i = 0 ; i < 4 ; i++ )     //初始化蛇
    {
        SnakePiece piece(BoardWidth / 2, BoardWidth / 2 + i, Up );
        snakeList << piece;
    }
}

void Snake::snakePlus()
{
    QMutableLinkedListIterator<SnakePiece> tempIterator(snakeList);
    tempIterator.toBack();  //移动到最后一节

    SnakePiece lastPiece = tempIterator.peekPrevious();

    lastPiece.oppsiteMoveSnakeGoingPiece(lastPiece.getSnakeDirection());

    snakeList << lastPiece;
}

void Snake::moveTheSnake(Direction moveDirection)   //在蛇头前加一点，将最后一点移除，形成蛇的移动
{
    QMutableLinkedListIterator<SnakePiece> tempIterator(snakeList);
    SnakePiece headPlusPiece = tempIterator.peekNext(); //取得原蛇头信息
    headPlusPiece.moveSnakeGoingPiece(moveDirection);

    tempIterator.insert(headPlusPiece);
    snakeList.removeLast();
}

SnakePiece  Snake::getSnakeHead()
{
    QLinkedListIterator<SnakePiece> tempIterator(snakeList);
    return tempIterator.peekNext();
}

QLinkedList<SnakePiece> *Snake::getSnakeList()
{
    return &snakeList;
}
