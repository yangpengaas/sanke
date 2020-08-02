#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "snakeframe.h"
#include "bfs.h"
#include "global.h"
#include <QPushButton>
#include <QProcess>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintWorld();
    void snakeMove(QPoint nextStep);
    int makeFood();
    void snakeGrow(QPoint newBody);
    ~MainWindow();



private:
    SnakeFrame* world[Width][High];
    Direction dir;
    QList<QPoint> snakeBody;
    Ui::MainWindow *ui;
    QPoint food;
    BFS bfs;
    QTimer *timer;
    int score;

public slots:
        void game();

};

#endif // MAINWINDOW_H
