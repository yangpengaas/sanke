#ifndef GLOBAL_H
#define GLOBAL_H
#include <QList>
#include <QPoint>
#include <QVector>
#include <QQueue>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
const int Width = 10;
const int High = 10;
//test
enum SnakeFrameStyle{
    Body,
    Food,
    Empty
};
enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
struct availablePoint
{
    QList<QPoint> avaliableDir;
    int count;
    bool isSuccess;
};
struct pathQueue
{
    QPoint point;
    int perNum;
    int curNum;
};
#endif // GLOBAL_H
