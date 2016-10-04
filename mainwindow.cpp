#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <stdio.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化随机数生成器
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);


    score = 0;
    SnakeFrame *frame;
    for(int i=0;i<Width;i++)
    {
        for(int j = 0;j<High;j++)
        {
            frame = new SnakeFrame();
            frame->setFrameBody(SnakeFrameStyle::Empty);
            world[i][j] = frame;
            ui->gamelayout->addWidget(frame,i,j);
        }
    }
    //初始化一条笨蛇
    snakeBody.push_front(QPoint(1,0));
    snakeBody.push_front(QPoint(1,1));
    paintWorld();

    makeFood();
    timer = new QTimer();
    QObject::connect(ui->startButton,SIGNAL(clicked()),this,SLOT(game()));
    QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(game()));
    timer->start(200);
}

void MainWindow::main()
{

}

void MainWindow::paintWorld()
{
    for(int i = 0;i<snakeBody.length();i++)
    {
        world[snakeBody.at(i).x()][snakeBody.at(i).y()]->setFrameBody(SnakeFrameStyle::Body);
    }
}

void MainWindow::snakeMove(QPoint nextStep)
{
    world[snakeBody.last().x()][snakeBody.last().y()]->setFrameBody(SnakeFrameStyle::Empty);

    qDebug() << "Fun:snakeMove:3" << endl;
    snakeBody.pop_back();
    qDebug() << "Fun:snakeMove:start nextStepx:" << nextStep.x() << "y:"<< nextStep.y() << endl;
    world[nextStep.x()][nextStep.y()]->setFrameBody(SnakeFrameStyle::Body);
    qDebug() << "Fun:snakeMove:1" << endl;
    snakeBody.push_front(nextStep);
    qDebug() << "Fun:snakeMove:2" << endl;


}

int MainWindow::makeFood()
{
    int x,y;
    while(1)
    {
        x = qrand()%Width;
        y = qrand()%High;
        qDebug() << "Fun:makefood" << endl;
        if((x >=0 && x<=Width)&&(y>=0 && y<=High))
        {
            if(world[x][y]->getFrameType() == SnakeFrameStyle::Empty)
            {
                qDebug() << "Fun:makefood:while" << endl;
                world[x][y]->setFrameBody(SnakeFrameStyle::Food);
                food.setX(x);
                food.setY(y);
                break;
            }
        }
    }
    return 0;
}
void MainWindow::snakeGrow(QPoint newBody)
{
    world[newBody.x()][newBody.y()]->setFrameBody(SnakeFrameStyle::Body);
    snakeBody.push_front(newBody);
}
void MainWindow::game()
{
//寻路过程特殊情况，
    {
        qDebug() <<"makefood" << endl;
        bfs.BFS_init();
        QPoint nextStep = bfs.GetNextStep(world,snakeBody.first(),food);
        if(nextStep.x() == -1)//找不到蛇头与食物的可用路径，此时找寻蛇尾位置。
        {
            nextStep = bfs.GetNextStep(world,snakeBody.first(),snakeBody.last());
            qDebug() << "snake end find" << endl;

        }
        if(nextStep == food)
        {
            snakeGrow(food);
            score++;
            ui->label->setText(QString::number(score));
            makeFood();
            return;
        }
        if(nextStep.x() == -1)
        {
            QMessageBox::information(this,"提示","Game Over!!");
            this->close();

        }
        qDebug() << "getNextStep:x:" << nextStep.x() << " y:" << nextStep.y() << endl;
        snakeMove(nextStep);
        qDebug() << "snakeMove" << endl;

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
