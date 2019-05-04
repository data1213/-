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
    //记录当前时间
    QTime c_time = QTime::currentTime();
    int diff = this->count_time.msecsTo(c_time);

    QTime temp;
    temp.setHMS(0,0,0,0);

    temp = temp.addMSecs(diff);
    QString str = temp.toString("hh:mm:ss.zzz");
    this->ui->lcdNumber->display(str);

}

//点击开始按钮之后触发计时器开始计时
void MainWindow::on_btn_begin_clicked()
{
    this->p_timer->start(1);  //启动1ms周期的定时器开始计时
    //0、记录当前时间
    this->count_time = QTime::currentTime();
}
