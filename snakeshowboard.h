#ifndef SNAKESHOWBOARD_H
#define SNAKESHOWBOARD_H

#include <QWidget>
#include <QtWidgets>
#include "snakeboardstate.h"

namespace Ui {
class SnakeShowBoard;
}

class SnakeShowBoard : public QWidget
{
    Q_OBJECT

public:
    explicit SnakeShowBoard(QWidget *parent = 0);
    ~SnakeShowBoard();

    void setShowBoardState( const QVector<QVector<PieceShape> > * );

private:
    Ui::SnakeShowBoard *ui;

    const QVector<QVector<PieceShape> > *showBoardState;
    void drawSnakePieceRect(QPainter &painter, int x, int y, PieceShape shape);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void repaintShowBoardSlot();
};

#endif // SNAKESHOWBOARD_H
