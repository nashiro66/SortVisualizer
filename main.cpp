#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    w.setStyleSheet("background-color: rgb(80, 80, 80) ; color: rgb(255, 255, 255);");


    return a.exec();
}
