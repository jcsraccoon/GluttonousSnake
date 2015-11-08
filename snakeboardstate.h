#ifndef SNAKEBOARDSTATE_H
#define SNAKEBOARDSTATE_H

#include <QWidget>
#include <QtWidgets>
#include "snake.h"

enum PieceShape {NoShape, FoodShape, SnakeShape};

namespace Ui {
class SnakeBoardState;
}

class SnakeBoardState : public QWidget
{
    Q_OBJECT

public:
    explicit SnakeBoardState(QWidget *parent = 0);
    ~SnakeBoardState();

    void initBoard();
    void tryMove(Direction keyDirection);
    void oneLineMove();
    void randomFood();
    void speedUp(int level);

    void mapTheSnake();

    void scoreUp();
    int getScoreNumber();
    const QVector<QVector<PieceShape> > *getBoardState();

private:
    Ui::SnakeBoardState *ui;

    Snake *mySnake;
    QVector<QVector<PieceShape> > *boardState;

    int score;
    int level;
    QBasicTimer timer;

protected:
    void timerEvent(QTimerEvent *event);

signals:
    void repaintSignal();
    void scoreChangedSignal();
    void gameOverSignal();

private slots:
    void upMoveSlot();
    void downMoveSlot();
    void leftMoveSlot();
    void rightMoveSlot();
};

#endif // SNAKEBOARDSTATE_H
