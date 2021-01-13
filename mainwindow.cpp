#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("A visualizer for sorting") ;
    this->setFixedSize(900,575);

    //newWindow
    animationScene=new QGraphicsScene();
    animationView= new QGraphicsView(animationScene);
    ui->gridLayout_4->addWidget(animationView);


    //array num
    ui->comboBox1->addItem("16");
    ui->comboBox1->addItem("32");
    ui->comboBox1->addItem("64");
    ui->comboBox1->addItem("128");
    ui->comboBox1->addItem("256");
    ui->comboBox1->addItem("512");


    //sort vatiation
    ui->comboBox2->addItem("Bubble");
    ui->comboBox2->addItem("Insert");
    ui->comboBox2->addItem("Shell");
    ui->comboBox2->addItem("Quick");
    ui->comboBox2->addItem("Heap");
    ui->comboBox2->addItem("Merge");

    //並び順
    ui->comboBox3->addItem("Ascending");
    ui->comboBox3->addItem("Descending");
    ui->comboBox3->addItem("Random");

    //stopはまだ使えない
    ui->stop->setText(NULL);
    ui->stop->setEnabled(false);

    //UI
    ui->generate->setStyleSheet("background-color: rgb(50, 50, 50) ;");
    ui->run->setStyleSheet("background-color: rgb(50, 50, 50) ;");
    ui->stop->setStyleSheet("background-color: rgb(50, 50, 50) ;");
    ui->comboBox1->setStyleSheet("background-color: rgb(50, 50, 50) ;");
    ui->comboBox2->setStyleSheet("background-color: rgb(50, 50, 50) ;");
    ui->comboBox3->setStyleSheet("background-color: rgb(50, 50, 50) ;");
    animationView->setStyleSheet("border:0px;background-color: rgb(50, 50, 50);");
    ui->frame->setObjectName("Qframe");
    ui->frame->setStyleSheet("#Qframe{border:1px solid rgb(50, 50, 50);}");
    ui->frame_2->setObjectName("Qframe2");
    ui->frame_2->setStyleSheet("#Qframe2{border:1px solid rgb(50, 50, 50);}");
    ui->frame_3->setObjectName("Qframe3");
    ui->frame_3->setStyleSheet("#Qframe3{border:1px solid rgb(50, 50, 50);}");
    ui->textBrowser_2->setStyleSheet("border:0px;background-color: rgb(50, 50, 50);");
    ui->textBrowser->setStyleSheet("border:0px;background-color: rgb(50, 50, 50);");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_generate_clicked()
{   //生成された
    ui->textBrowser->setText("generated");

    animationView->viewport()->update();

    //要素数を受け取る
    int num=ui->comboBox1->currentText().toInt();

    //どの並び順かを受け取る
    int initial_column = ui->comboBox3->currentIndex();

    //何倍速か値を受け取る
    int speed=ui->label_9->text().toInt();

    //Sortクラス
    m_sort=new Sort(num,animationScene,animationView,speed);

    //Ascending
    if(initial_column==0){
        m_sort->Ascending();
    }

    //Descending
    else if(initial_column==1){
        m_sort->Descending();
   }
    //random
    else if(initial_column==2){
        m_sort->random();
    }
    started=1;
}



void MainWindow::on_run_clicked()
{   //generateしていないとき
    if(started==0){
    ui->textBrowser->setText("you have to generate before running");
    }
    //generateしてあるとき
    if(started==1&&ui->run->text()=="Start"){
        //startした
        started=2;
        ui->textBrowser->setText("runnning...");

        //startは使えない
        ui->run->setText(NULL);
        ui->run->setEnabled(false);

        //stopが使えるようになる
        ui->stop->setText("Stop");
        ui->stop->setEnabled(true);

        //generateは使えない
        ui->generate->setText(NULL);
        ui->generate->setEnabled(false);

        //実行中
        running=true;

        int sort_type = ui->comboBox2->currentIndex();

        //時間を計測し始める
        time=0;
        timer.restart();


        //Bubble
        if(sort_type==0){
            m_sort->Bubble();
        }

        //Insert
        else if(sort_type==1){
            m_sort->Insert();
        }
        //shell
        else if(sort_type==2){
            m_sort->Shell();
        }
        //Quick
        else if(sort_type==3){
            m_sort->Quick();
        }
        //Heap
        else if(sort_type==4){
            m_sort->Heap();
        }
        //Merge
        else if(sort_type==5){
            m_sort->MergeSort();
        }
        //スタートを押せるようにする
        ui->run->setEnabled(true);
        ui->run->setText("Clear");


        time+=timer.elapsed();

        //計測した時間を表示
        ui->textBrowser_2->setText(QString::number(time/1000)+"second");
        ui->textBrowser->setText("finish!");

        //stopは使えなくなる
        ui->stop->setText(NULL);
        ui->stop->setEnabled(false);

    }
    //viewをclearする
    else if(ui->run->text()=="Clear"){
        //前回のを削除
        m_sort->~Sort();

        started=0;
        ui->run->setText("Start");
        ui->textBrowser->setText("Cleared");

        //generate使えるようになる
        ui->generate->setText("Generate");
        ui->generate->setEnabled(true);
    }
    else if(ui->run->text()=="Kill"&&ui->stop->text()=="Restart"){
        //今のプロセスをKill
        m_sort->~Sort();
        //初期状態にする
        //stopは使えない
        ui->stop->setText(NULL);
        ui->stop->setEnabled(false);
        //KillをStartに変える
        ui->run->setText("Start");
        started=0;
        ui->generate->setText("Generate");
        ui->generate->setEnabled(true);
    }
}

void MainWindow::on_stop_clicked()
{
    //停止する
    if(running==true && ui->stop->text()=="Stop"){
        time+=timer.elapsed();
        running=false;
        ui->stop->setText("Restart");

        //Killできるようにする
        ui->run->setText("Kill");
        ui->run->setEnabled(true);
        while(!running){
            m_sort->Stop(running);
        }
    }

    //再開する
    if(running==false && ui->stop->text()=="Restart"){
        timer.restart();
        running=true;
        ui->stop->setText("Stop");
        m_sort->Stop(running);
    }

}

//何倍速にするか
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->label_9->setText(QString::number(position));
}
