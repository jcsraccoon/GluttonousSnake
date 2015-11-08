#include "snakeshowboard.h"
#include "ui_snakeshowboard.h"

SnakeShowBoard::SnakeShowBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SnakeShowBoard)
{
    ui->setupUi(this);

    this->setFixedSize(SquarePixel*BoardWidth, SquarePixel*BoardWidth);
}

SnakeShowBoard::~SnakeShowBoard()
{
    delete ui;
}

void SnakeShowBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2));
    painter.drawRect(0,0, SquarePixel*BoardWidth, SquarePixel*BoardWidth);

    for ( int i = 0; i < BoardWidth; i++ )
    {
        for ( int j = 0; j < BoardWidth; j++ )
        {
            if ( NoShape != (*showBoardState)[i][j] )
            {
                this->drawSnakePieceRect(painter, i, j, (*showBoardState)[i][j] );
            }
        }
    }
}

void SnakeShowBoard::drawSnakePieceRect(QPainter &painter, int x, int y, PieceShape shape)
{
    painter.setPen(QPen(Qt::black, 2));

    if ( FoodShape == shape )
    {
        painter.fillRect(x * SquarePixel, y * SquarePixel, SquarePixel, SquarePixel, Qt::green);
        return;
    }
    painter.fillRect(x * SquarePixel, y * SquarePixel, SquarePixel, SquarePixel, Qt::black);
}

void SnakeShowBoard::setShowBoardState(const QVector<QVector<PieceShape> > * board)
{
    showBoardState = board;
}

void SnakeShowBoard::repaintShowBoardSlot()
{
    this->update();
}
