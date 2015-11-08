#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "snakeshowboard.h"
#include "snake.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void runGame();

private:
    Ui::MainWindow *ui;

    void drawDesk();

    SnakeBoardState *snakeBoardState;
    SnakeShowBoard * snakeShowBoard;

    QLabel * gameInfoLabel;
    QLCDNumber *lcdNumberScore;
    bool gameOver;

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void keyUpSignal();
    void keyDownSignal();
    void keyLeftSignal();
    void keyRightSignal();

private slots:
    void initGameSlot();

    void setScoreShowSlot();
    void gameOverSlot();

};

#endif // MAINWINDOW_H
