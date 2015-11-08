#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qsrand(time(NULL));
    this->setFixedSize(450,400);
    this->setWindowTitle("贪吃的大葱");
    this->runGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runGame()
{
    snakeBoardState = new SnakeBoardState;
    snakeShowBoard = new SnakeShowBoard;

    gameOver = false;

    snakeBoardState->initBoard();
    snakeShowBoard->setShowBoardState(snakeBoardState->getBoardState());

    this->drawDesk();
}

void MainWindow::drawDesk()
{
    QWidget *myWidget = new QWidget;
    this->setCentralWidget(myWidget);

    QPushButton *buttonStart = new QPushButton("开始");
    QPushButton *buttonPause = new QPushButton("暂停");
    QPushButton *buttonQuit = new QPushButton("退出");

    QLabel *labelScore = new QLabel("Score");
    labelScore->setAlignment(Qt::AlignCenter);
    lcdNumberScore = new QLCDNumber(3);

    gameInfoLabel = new QLabel;
    gameInfoLabel->setText("good luck");

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(gameInfoLabel);
    rightLayout->addSpacing(70);
    rightLayout->addWidget(labelScore);
    rightLayout->addWidget(lcdNumberScore);
    rightLayout->addWidget(buttonStart);
    rightLayout->addWidget(buttonPause);
    rightLayout->addWidget(buttonQuit);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(snakeShowBoard);
    mainLayout->addLayout(rightLayout);

    myWidget->setLayout(mainLayout);

    connect(buttonStart, SIGNAL(clicked()), this, SLOT(initGameSlot()));
    connect(buttonQuit, SIGNAL(clicked()), this, SLOT(close()));

    connect(snakeBoardState, SIGNAL(repaintSignal()), snakeShowBoard, SLOT(repaintShowBoardSlot()));
    connect(snakeBoardState, SIGNAL(scoreChangedSignal()), this, SLOT(setScoreShowSlot()));
    connect(snakeBoardState, SIGNAL(gameOverSignal()), this, SLOT(gameOverSlot()));

    connect(this, SIGNAL(keyUpSignal()), snakeBoardState, SLOT(upMoveSlot()));
    connect(this, SIGNAL(keyDownSignal()), snakeBoardState, SLOT(downMoveSlot()));
    connect(this, SIGNAL(keyLeftSignal()), snakeBoardState, SLOT(leftMoveSlot()));
    connect(this, SIGNAL(keyRightSignal()), snakeBoardState, SLOT(rightMoveSlot()));

}

void MainWindow::initGameSlot()
{
    gameOver = false;

    snakeBoardState->initBoard();
    snakeShowBoard->setShowBoardState(snakeBoardState->getBoardState());

    gameInfoLabel->setText("good luck");
    lcdNumberScore->display(0);

    snakeShowBoard->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if ( gameOver )
    {
        return;
    }

    if ( event->key() == Qt::Key_Up || event->key() == Qt::Key_W )
    {
        emit keyUpSignal();
    }
    if ( event->key() == Qt::Key_Down || event->key() == Qt::Key_S )
    {
        emit keyDownSignal();
    }
    if ( event->key() == Qt::Key_Left || event->key() == Qt::Key_A )
    {
        emit keyLeftSignal();
    }
    if ( event->key() == Qt::Key_Right || event->key() == Qt::Key_D )
    {
        emit keyRightSignal();
    }
}

void MainWindow::setScoreShowSlot()
{
    lcdNumberScore->display(snakeBoardState->getScoreNumber());
}

void MainWindow::gameOverSlot()
{
    gameInfoLabel->setText("game over");
    gameOver = true;
}
