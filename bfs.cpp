#include "bfs.h"
#include <iostream>

BFS::BFS()
{

}
void BFS::BFS_init()
{
    mapArrCounter = 0;
    bfsQueue.clear();//bfs 队列
    aimPoint.curNum = 0;
    aimPoint.perNum = 0;
    aimPoint.point = QPoint(-1,-1);

}


static availablePoint getAvailablePoint(bool world[Width][High],QPoint snakeHead,QPoint aim)
{
    //Head 右面的节点
//    qDebug() << "BFS:getavailablePoint:snakeHead x:" << snakeHead.x() << " y:" << snakeHead.y() << endl;
//    qDebug() << "BFS:getavailablePoint:aim x:" << aim.x() << " y:" << aim.y() << endl;
    availablePoint avaPoint;
    avaPoint.isSuccess = false;
    avaPoint.count =0;
    if((snakeHead.x() == aim.x()&&(snakeHead.y() == aim.y())))
    {
        avaPoint.isSuccess = true;
        return avaPoint;
    }
    int x = snakeHead.x();
    int y = snakeHead.y()+1;
    if((x <Width && x>=0) && (y<High &&y>=0))//判断该点是否越界
    {
        if(world[x][y] == false)//判断该点是否可用
        {

            avaPoint.avaliableDir.push_front(QPoint(x,y));
            avaPoint.count++;
        }
    }
    //Head 左面的节点
    x = snakeHead.x();
    y = snakeHead.y()-1;
    if((x <Width && x>=0) && (y<High &&y>=0))//判断该点是否越界
    {
        if(world[x][y] == false)//判断该点是否可用
        {
            avaPoint.avaliableDir.push_front(QPoint(x,y));
            avaPoint.count++;
        }
    }
    //Head 上边的节点
    x = snakeHead.x()-1;
    y = snakeHead.y();
    if((x <Width && x>=0) && (y<High &&y>=0))//判断该点是否越界
    {
        if(world[x][y] == false)//判断该点是否可用
        {
            avaPoint.avaliableDir.push_front(QPoint(x,y));
            avaPoint.count++;
        }
    }
    //Head 下边的节点
    x = snakeHead.x()+1;
    y = snakeHead.y();
    if((x <Width && x>=0) && (y<High &&y>=0))//判断该点是否越界
    {
        if(world[x][y] == false)//判断该点是否可用
        {
            avaPoint.avaliableDir.push_front(QPoint(x,y));
            avaPoint.count++;
        }
    }
    if(avaPoint.count == 0)
        avaPoint.isSuccess = false;
    return avaPoint;
}

//bfs寻路函数，分四个方向探索路径
bool BFS::bfs(bool world[Width][High],QPoint snakeHead,QPoint aim)
{
    //debug
//    for(int i=0;i<Width;i++)
//    {
//        for(int j=0;j<High;j++)
//        {
//            std::cout << world[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

    //获取可用路径
    qDebug() << "BFS:bfs:aim x:" << aim.x() << " y:" << aim.y() << endl;
    availablePoint avaPoint;
    mapArr[0].point = snakeHead;
    mapArr[0].perNum = -1;
    mapArr[0].curNum = mapArrCounter;
    qDebug() << "vector flags" << endl;
    pathQueue temp;
    temp.curNum = mapArrCounter;
    temp.perNum = -1;
    temp.point = snakeHead;
    bfsQueue.enqueue(temp);
    pathQueue curPoint;

    while(0 != bfsQueue.length())
    {

//        qDebug() << "bfsQueue:length:" << bfsQueue.length() << endl;
//        qDebug() << "flag" << endl;
//        for(int i=0;i<Width;i++)
//        {
//            for(int j=0;j<High;j++)
//            {
//                std::cout << world[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout <<std::endl;
//        qDebug() << "flag1" << endl;
        temp = bfsQueue.dequeue();
//        qDebug() << "BFS:bfs:curPoint x:" << curPoint.x() << " y:" << curPoint.y() << endl;
//        qDebug() << "BFS:bfs:aim x:" << aim.x() << " y:" << aim.y() << endl;
        avaPoint = getAvailablePoint(world,temp.point,aim);
        if(avaPoint.isSuccess == true)
        {
            qDebug() << "isSuccess" << endl;
            aimPoint = temp;
            return avaPoint.isSuccess;
        }
        world[temp.point.x()][temp.point.y()] = true;//
//        qDebug() << "avaPoint.couty:" <<avaPoint.count << endl;
        for(int i=0;i<avaPoint.count;i++)
        {
            mapArrCounter = mapArrCounter +1;
//            qDebug() << "BFS:bfs:avapoint           x:" << avaPoint.avaliableDir.at(i).x() << " y:" << avaPoint.avaliableDir.at(i).y() << endl;
            mapArr[mapArrCounter].point = avaPoint.avaliableDir.at(i);
//            qDebug() << "flag2" << endl;
            mapArr[mapArrCounter].curNum = mapArrCounter;
            mapArr[mapArrCounter].perNum = temp.curNum;
//            qDebug() << "flag3" << endl;
            bfsQueue.enqueue(mapArr[mapArrCounter]);

        }

    }

    return avaPoint.isSuccess;
}
QPoint BFS::GetNextStep(SnakeFrame* world[Width][High],QPoint snakeHead,QPoint aim)
{
    //QPoint retPoint;
    bool tempWorld[Width][High];
    for(int i=0;i<Width;i++)
    {
        for(int j=0;j<High;j++)
        {
            if(world[i][j]->getFrameType() != SnakeFrameStyle::Body)
                tempWorld[i][j] = false;
            else
                tempWorld[i][j] = true;
        }
    }
    bool ret = bfs(tempWorld,snakeHead,aim);
    if(ret)
    {
        while(aimPoint.perNum != 0 )
        {
            qDebug() << "aimPoint:curNum:" << aimPoint.curNum << endl;
            qDebug() << "aimPoint.perNum:" << aimPoint.perNum << endl;
            qDebug() << "aimPoint.point.x:" << aimPoint.point.x() << endl;
            qDebug() << "aimPoint.point.y:" << aimPoint.point.y() << endl << endl;
            aimPoint = mapArr[aimPoint.perNum];
        }
    }
    else
    {
        mapArrCounter --;
        if(mapArrCounter == 0)
        return QPoint(-1,-1);
    }




    return aimPoint.point;
}
