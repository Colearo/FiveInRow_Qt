#ifndef VIEW_H
#define VIEW_H

#include <QtGui>
#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
#include <QAction>
#include <QPushButton>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <iostream>
#include <vector>
#include "fir.h"
class MainWindow : public QMainWindow//Qt库的图形主窗口继承自QMainWindow类
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);//构造函数
    ~MainWindow();//析构函数
    void paintEvent(QPaintEvent *);//设置窗口的重绘事件
    void mouseReleaseEvent(QMouseEvent *);//设置鼠标的点击事件
    void createMenu();  //设置菜单按钮

protected slots:
    void startGame(void); //开始游戏
    void pauseGame(void); //暂停游戏
    void backto(void);//悔棋
    void showAbout(void); //显示关于对话框
    void restartGame(void); //重新开始游戏
    void timeUpate();  //设置计时器
private:
    bool Run;//游戏开始标志
    QWidget *center;//中心窗口控件
    QPushButton *btnstart;//开始按钮
    QPushButton *btnrestart;//重新开始按钮
    QPushButton *btnexit;//退出按钮
    QPushButton *btnback;//返回按钮
    QPushButton *btnpause;//暂停按钮
    QPushButton *btnabout;//关于按钮
    QLCDNumber *lcd;//计时器控件
    QTimer *timer;
    int timeI;
    QTime *time;
    FIR GAME;//声明一个五子棋游戏对象
};


#endif // VIEW_H
