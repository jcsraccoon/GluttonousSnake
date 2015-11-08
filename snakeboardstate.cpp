#include "snakeboardstate.h"
#include "ui_snakeboardstate.h"

SnakeBoardState::SnakeBoardState(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SnakeBoardState)
{
    ui->setupUi(this);

}

SnakeBoardState::~SnakeBoardState()
{
    delete ui;
}

void SnakeBoardState::initBoard()
{
    mySnake = new Snake;
    boardState = new QVector<QVector<PieceShape> >;

    QVector<PieceShape> state(BoardWidth, NoShape);
    for ( int i = 0 ; i < BoardWidth; i++ )
    {
        boardState->push_back(state);
    }

    score = 0;
    level = 1;

    timer.start(250, this);

    this->mapTheSnake();        //show the snake at the first time
    this->randomFood();     //when the snake has been mapped, show the food
}

void SnakeBoardState::timerEvent(QTimerEvent *event)
{
    if ( event->timerId() == timer.timerId() )
    {
        this->oneLineMove();
    }
}

void SnakeBoardState::tryMove(Direction keyDirection)
{
    mySnake->moveTheSnake(keyDirection);
    int x = mySnake->getSnakeHead().getPieceX();
    int y = mySnake->getSnakeHead().getPieceY();

    if ( x < 0 || x >= BoardWidth ) //if the snake head run out of the map
    {
        emit gameOverSignal();
        timer.stop();
        return;
    }
    if ( y < 0 || y >= BoardWidth )
    {
        emit gameOverSignal();
        timer.stop();
        return;
    }
    if ( SnakeShape == (*boardState)[x][y] )    //if the snake head rush it's body
    {
        emit gameOverSignal();
        timer.stop();
        return;
    }
    if ( FoodShape == (*boardState)[x][y] )
    {
        mySnake->snakePlus();
        this->randomFood();
        this->scoreUp();
    }

    this->mapTheSnake();        //映射地图
}

void SnakeBoardState::oneLineMove()
{
    this->tryMove(mySnake->getSnakeHead().getSnakeDirection());
}

void SnakeBoardState::mapTheSnake()
{
    for ( int i = 0; i < BoardWidth; i++ )
    {
        for ( int j = 0; j < BoardWidth; j++ )
        {
            if ( SnakeShape == (*boardState)[i][j] )
            {
                (*boardState)[i][j] = NoShape;
            }
        }
    }

    int x,y;
    QLinkedList<SnakePiece> *snakelist = mySnake->getSnakeList();

    QMutableLinkedListIterator<SnakePiece> myIterator(*snakelist);
    while ( myIterator.hasNext() )
    {
        x = myIterator.peekNext().getPieceX();
        y = myIterator.peekNext().getPieceY();

        (*boardState)[x][y] = SnakeShape;

        myIterator.next();
    }

    emit repaintSignal();
}

const QVector<QVector<PieceShape> > *SnakeBoardState::getBoardState()
{
    return boardState;
}

void SnakeBoardState::upMoveSlot()
{
    //屏蔽蛇的正方向与相反方向的键盘事件
    if ( Up == mySnake->getSnakeHead().getSnakeDirection()  || Down == mySnake->getSnakeHead().getSnakeDirection() )
    {
        return;
    }
    this->tryMove(Up);
    this->speedUp(level);      /*-- 防止keyPressEvent与timeEvent产生的延迟与冲突，每次键盘事件出发时，重新开启定时器 --*/
}

void SnakeBoardState::downMoveSlot()
{
    if ( Down == mySnake->getSnakeHead().getSnakeDirection() || Up == mySnake->getSnakeHead().getSnakeDirection() )
    {
        return;
    }
    this->tryMove(Down);
    this->speedUp(level);
}

void SnakeBoardState::leftMoveSlot()
{
    if ( Left == mySnake->getSnakeHead().getSnakeDirection() || Right == mySnake->getSnakeHead().getSnakeDirection() )
    {
        return;
    }
    this->tryMove(Left);
    this->speedUp(level);
}

void SnakeBoardState::rightMoveSlot()
{
    if ( Right == mySnake->getSnakeHead().getSnakeDirection() || Left == mySnake->getSnakeHead().getSnakeDirection() )
    {
        return;
    }
    this->tryMove(Right);
    this->speedUp(level);
}

void SnakeBoardState::scoreUp()
{
    score++;

    if ( score % 4 == 0  && level <= 6 )
    {
        level++;
    qDebug() << level;
        this->speedUp(level);
    }
    emit scoreChangedSignal();
}

int SnakeBoardState::getScoreNumber()
{
    return score;
}

void SnakeBoardState::randomFood()
{
    int x = qrand() % BoardWidth;
    int y = qrand() % BoardWidth;

    if ( NoShape == (*boardState)[x][y] )
    {
        (*boardState)[x][y] = FoodShape;
    }
    else
    {
        randomFood();
    }
}

void SnakeBoardState::speedUp(int level)
{
    timer.start(250 - level*20, this);
}
