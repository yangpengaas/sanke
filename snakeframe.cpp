#include "SnakeFrame.h"

SnakeFrame::SnakeFrame()
{

}

void SnakeFrame::setFrameBody(SnakeFrameStyle style)
{
    bodyType = style;
    switch(style)
    {
        case Body:
            this->setStyleSheet("background-color:red");
        break;
        case Food:
            this->setStyleSheet("background-color:yellow");
        break;
        case Empty:
            this->setStyleSheet("background-color:gray");
        break;
        default:

        break;

    }

}
int SnakeFrame::getFrameType()
{
    return bodyType;
}
