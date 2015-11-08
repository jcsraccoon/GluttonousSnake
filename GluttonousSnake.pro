#-------------------------------------------------
#
# Project created by QtCreator 2015-09-29T19:25:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GluttonousSnake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    snakeshowboard.cpp \
    snakeboardstate.cpp \
    snake.cpp \
    snakepiece.cpp

HEADERS  += mainwindow.h \
    snakeshowboard.h \
    snakeboardstate.h \
    snake.h \
    snakepiece.h \
    boardsize.h

FORMS    += mainwindow.ui \
    snakeshowboard.ui \
    snakeboardstate.ui \
    snakepiece.ui \
    snake.ui
