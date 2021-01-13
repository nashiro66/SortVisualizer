#ifndef SORT_H
#define SORT_H
#include <QVector>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QRandomGenerator>
#include <QTime>
#include <QPen>
#include <QGraphicsItem>
#include <QApplication>
#include <QTimer>
#include <QEventLoop>
#include <QGraphicsView>
#include "math.h"

//色の定義
#define GREEN QColor(55, 200, 0)
#define ORANGE QColor(255, 102, 0)
#define PURPLE QColor(124, 7, 169)


//sorting class
class Sort{
public:
    Sort(int,QGraphicsScene *,QGraphicsView *,int);
    ~Sort();
    void render(int i,QColor);

    void Ascending();
    void Descending();
    void random();
    void visualize();
    void draw();
    void delay();
    void swap(int,int);


    void Stop(bool);
    void Bubble();
    void Insert();
    void Shell();
    void Quick();
    void Quick_middle(int,int);
    void Heap();
    void downHeap(int,int);
    void MergeSort();
    void Merge(int,int,int);
    void MergeSplit(int,int);

private:

    bool ok;
    QVector<int> vec;
    float width;
    int sort_num;
    std::vector<QGraphicsRectItem *> rects ;
    QGraphicsScene * m_scene ;
    QGraphicsView *m_view;
    bool drawn;
    bool running_now;
    int m_speed;
};




#endif // SORT_H
