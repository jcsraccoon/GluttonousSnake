#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QtWidgets>
#include "snakepiece.h"
#include "boardsize.h"

namespace Ui {
class Snake;
}

class Snake : public QWidget
{
    Q_OBJECT

public:
    explicit Snake(QWidget *parent = 0);
    ~Snake();

    void initSnake();
    void snakePlus();       //蛇加长
    void moveTheSnake(Direction moveDirection);

    SnakePiece getSnakeHead();
    QLinkedList<SnakePiece> *getSnakeList();

private:
    Ui::Snake *ui;

    QLinkedList<SnakePiece> snakeList;
};

#endif // SNAKE_H
