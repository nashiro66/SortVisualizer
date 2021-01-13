#ifndef ANIMATE_H
#define ANIMATE_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QPen>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "mainwindow.h"





class animation{
public:
    animation();
    ~animation();
    void render(int,QVector<int>,int);

private:

    int width;
    std::vector<QGraphicsRectItem *> rect;
    std::vector<QGraphicsLineItem *> line;

};


#endif // ANIMATE_H
