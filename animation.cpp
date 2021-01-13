#include "animate.h"
#include "mainwindow.h"


animation::animation(){

}

void animation::render(int i,QVector<int> vec,int sort_num){



    int height=(vec[i]);
    if(sort_num<=256){
        int left=10+i;
        int up=5-height;
        QPen pen=QPen(Qt::black);
        QBrush brush=QBrush(GREEN);

    }

}
