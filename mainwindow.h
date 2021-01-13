#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGlobal>
#include <QElapsedTimer>
#include "sort.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent= nullptr);
    ~MainWindow();


private slots:
    void on_generate_clicked();
    void on_run_clicked();
    void on_stop_clicked();
    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QElapsedTimer timer;
    QGraphicsScene *animationScene;
    QGraphicsView *animationView;
    Sort *m_sort;

    bool running=0;
    float time=0;

    //before generatedのとき0 after generatedのとき1 startedのとき2
    int started=0;

    QPen pen = QPen (ORANGE);
    QBrush brush = QBrush (ORANGE) ;
};



#endif // MAINWINDOW_H
