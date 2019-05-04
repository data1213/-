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

    //为了实现打点记录，这里先获取下当前时间
    this->show_time = str;

}

//点击开始按钮之后触发计时器开始计时
void MainWindow::on_btn_begin_clicked()
{
    this->p_timer->start(1);  //启动1ms周期的定时器开始计时
    //0、记录当前时间
    this->count_time = QTime::currentTime();
}

void MainWindow::on_btn_end_clicked()
{

}

void MainWindow::on_btn_hold_clicked()
{

}

//打点功能：
void MainWindow::on_btn_flag_clicked()
{
    //获取当前计数，并显式在text brower控件中显式
    //this->ui->lcdNumber->value();是一个double值，不是时间值
    //this->ui->textBrowser->setText()方法会覆盖之前的文本内容
    this->ui->textBrowser->append(this->show_time);
}
