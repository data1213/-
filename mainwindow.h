#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void update_my_timer();

    void on_btn_begin_clicked();

    void on_btn_end_clicked();

    void on_btn_hold_clicked();

    void on_btn_flag_clicked();

private:
    QTime count_time;       //计数，用于更新定时器
    QTimer* p_timer;        //定时器
    QString show_time;        //用于打点记录
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
