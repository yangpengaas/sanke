#ifndef SnakeFrame_H
#define SnakeFrame_H

#include <QWidget>
#include <QColor>
#include <QPalette>
#include <qpainter.h>
#include <QPaintEvent>
#include <QBrush>
#include "global.h"

class SnakeFrame : public QWidget
{
public:
    SnakeFrameStyle bodyType;

    SnakeFrame();
    void setFrameBody(SnakeFrameStyle style);
    int getFrameType();

};



#endif // SnakeFrame_H
