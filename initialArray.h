#ifndef INITIALARRAY_H
#define INITIALARRAY_H
#include "mainwindow.h"
#include <QtGlobal>
#include <QTime>
#include <QRandomGenerator>

//初期配列を定義する
//色0～255を並べる

//昇順
void MainWindow::Ascending(){
    for(int i=0;i<sort_num;i++){
        vec.append((i)*255/(sort_num-1));
    }
}

//降順
void MainWindow::Descending(){
    for(int i=sort_num-1;i>=0;i--){
        vec.append((i)*255/(sort_num-1));
    }

}

//ランダム
void MainWindow::random(){
    // initialize random generator
    qsrand( QTime::currentTime().msec() );
    for(int i=0;i<sort_num;i++){
        int random = qrand() % (256);
        //add random number
        vec.append(random);
    }
}
#endif // INITIALARRAY_H
