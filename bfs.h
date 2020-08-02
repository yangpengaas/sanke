#ifndef BFS_H
#define BFS_H

#include "snakeframe.h"
#include "global.h"



class BFS
{
private:
//    QPoint worldMap[Width*High];
    pathQueue mapArr[Width*High*100];//路径记录数组
//    QVector<pathQueue>mapArr;
    int mapArrCounter;
    QQueue<pathQueue> bfsQueue;//bfs 队列
    pathQueue aimPoint;

public:
    BFS();
    void BFS_init();//初始化BFS所需数据
    QPoint GetNextStep(SnakeFrame* world[Width][High],QPoint sankeHead,QPoint aim);
    bool bfs(bool world[Width][High],QPoint snakeHead,QPoint aim);


};

#endif // BFS_H
