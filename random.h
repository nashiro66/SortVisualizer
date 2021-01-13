#ifndef RANDOM_H
#define RANDOM_H
#include "mainwindow.h"
#include <QtGlobal>
#include <QTime>
#include <QRandomGenerator>

void MainWindow::generate_random(){
    // initialize random generator
    qsrand( QTime::currentTime().msec() );
    for(int i=0;i<sort_num;i++){
        int random = qrand() % (256);
        //add random number
        vec.append(random);
    }
}

#endif // RANDOM_H
