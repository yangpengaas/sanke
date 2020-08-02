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

const int Width = 11;
const int High = 11;
//test123
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
