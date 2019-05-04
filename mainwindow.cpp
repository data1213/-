#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->p_timer = new QTimer();
    connect(this->p_timer, SIGNAL(timeout()), this, SLOT(update_my_timer())); //绑定定时器和槽函数

}

MainWindow::~MainWindow()
{
    delete ui;
}


//计时周期到响应的槽函数
void MainWindow::update_my_timer(){
    //1、更新当前计数
    this->count_time = this->count_time.addMSecs(1); //增加1ms
    //2、控件显式更新
    QString timev = this->count_time.toString("hh:mm:ss.zzz");
    qDebug()<<timev;
    this->ui->lcdNumber->display(timev);

}

//点击开始按钮之后触发计时器开始计时
void MainWindow::on_btn_begin_clicked()
{
    this->p_timer->start(1);  //启动1ms周期的定时器开始计时
    //0、清空计数
    this->count_time.setHMS(0,0,0,0);
}
