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
    if(this->ui->btn_end->text() == "停止"){
        this->p_timer->stop();
        this->ui->btn_end->text() = "清零";
    }else {  //清零
        this->ui->lcdNumber->display("00:00:00:000");
        this->ui->textBrowser->clear();
        this->ui->btn_end->text() = "停止";
    }
}

//暂停功能
void MainWindow::on_btn_hold_clicked()
{
    //old_time需要时静态的，记录点击暂停时的时间，保留到下次调用该函数——点击继续时调用
    static QTime old_time;

    if(this->ui->btn_hold->text() == "暂停"){
        old_time = QTime::currentTime();
        this->p_timer->stop();//暂停计数,当系统时间一直在走，而count_timer没有变化了
        this->ui->btn_hold->setText("继续");
    }else {
        QTime new_time = QTime::currentTime();
        int mdiff = old_time.msecsTo(new_time);
        //更新从上一次点击暂停到这次点击继续之间系统经过的时间，然后补偿给count_timer
        this->count_time = this->count_time.addMSecs(mdiff);
        //开启计时器
        this->p_timer->start(1);
        this->ui->btn_hold->setText("暂停");
    }
}

//打点功能：
void MainWindow::on_btn_flag_clicked()
{
    //获取当前计数，并显式在text brower控件中显式
    //this->ui->lcdNumber->value();是一个double值，不是时间值
    //this->ui->textBrowser->setText()方法会覆盖之前的文本内容
    this->ui->textBrowser->append(this->show_time);
}
