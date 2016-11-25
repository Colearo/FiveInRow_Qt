#include "view.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)//MainWindow的初始化构造函数
{
    resize(540, 440);
    setWindowTitle("五子棋-Five in a row");
    center = new QWidget();
    setCentralWidget(center);
    //计时器设置
    timeI=0;
    time=new QTime(0,0,0);
    timer=new QTimer;
    lcd=new QLCDNumber(center);
    center->resize(540,440);//设置窗口大小
    this->setStyleSheet("QMainWindow{background-color:#6B8A74;}");//设置背景颜色
    //设置下面这6个按钮
    btnstart=new QPushButton("开始游戏",center);
    btnpause=new QPushButton("暂停游戏",center);
    btnrestart=new QPushButton("重新开始",center);
    btnexit=new QPushButton("退出游戏",center);
    btnback=new QPushButton("悔棋",center);
    btnabout=new QPushButton("关于",center);
    Run=false;
    createMenu();
    //memset(a, 0, 20 * 20 * sizeof(int));
    //total = 0;
}

MainWindow::~MainWindow()
{

}
void MainWindow::createMenu()//设置菜单样式和信号槽功能
{
    lcd->setDigitCount(8);//设置lcd显示计数器控件
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setMode(QLCDNumber::Dec);
    lcd->display("00:00:00");
    QString button_style="QPushButton{color:#D79691;background-color:#6385A7;border-radius:6px;border: 1px groove gray;}""QPushButton:pressed{background-color:#F3F0CD;}";
    btnexit->setGeometry(460,100,60,20);
    btnexit->setStyleSheet("QPushButton{color:#093D5A;background-color:#F35A4A;border-radius:6px;border: 1px groove gray;}""QPushButton:pressed{background-color:#F3F0CD;}");
    btnback->setGeometry(460,140,60,20);//设置按钮大小和位置
    btnstart->setGeometry(460,180,60,20);
    btnpause->setGeometry(460,220,60,20);
    btnabout->setGeometry(460,260,60,20);
    btnrestart->setGeometry(460,300,60,20);
    lcd->setGeometry(460,350,60,20);
    btnback->setStyleSheet(button_style);//设置按钮样式
    btnstart->setStyleSheet(button_style);
    btnpause->setStyleSheet(button_style);
    btnpause->setStyleSheet(button_style);
    btnabout->setStyleSheet(button_style);
    btnrestart->setStyleSheet("QPushButton{color:#F2F2F2;background-color:#212A3E;border-radius:6px;border: 1px groove gray;}""QPushButton:pressed{background-color:#F3F0CD;}");
    //设置按钮和与之相关的动作，即Qt里的信号－槽关联
    connect(btnexit,SIGNAL(clicked()),this,SLOT(close()));
    connect(btnstart,SIGNAL(clicked()),this,SLOT(startGame()));
    connect(btnpause,SIGNAL(clicked()),this,SLOT(pauseGame()));
    connect(btnback,SIGNAL(clicked()),this,SLOT(backto()));
    connect(btnabout,SIGNAL(clicked()),this,SLOT(showAbout()));
    connect(btnrestart,SIGNAL(clicked()),this,SLOT(restartGame()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpate()));
}

void MainWindow::paintEvent(QPaintEvent *) //设置窗口的重绘事件
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    int i, j;
    //画出20*20的棋盘
    for (i = 0; i < 21; i++)
    {
        p.drawLine(20, 20 + i * 20, 420, 20 + i * 20);
        p.drawLine(20 + i * 20, 20, 20 + i * 20, 420);
    }
    //画五子棋的棋子
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
        {
            if (GAME.data[i][j] == 1)
            {
                brush.setColor(Qt::black);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i + 1) * 20, (j + 1) * 20), 8, 8);
            }
            else if (GAME.data[i][j] == 2)
            {
                brush.setColor(Qt::white);
                p.setBrush(brush);
                p.drawEllipse(QPoint((i + 1) * 20, (j + 1) * 20), 8, 8);
            }
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)  //设置鼠标的点击事件
{
    if(Run==false){
        setEnabled(false);
        QMessageBox::information(this, "注意",
                "请先点击开始游戏按钮");
        sleep(1);
        setEnabled(true);
        return;
    }
    int who=0;
    if(GAME.Process(e->x(),e->y(),who))//如果在棋盘区域范围内则有效执行下面函数
    {
        update();
        GAME.Judge(who);//鼠标每次点击之后要判断一下正负
        if(who==1)
        {
            update();
            setEnabled(false);
            //黑棋赢了则弹出下面对话框
            QMessageBox::information(this, "游戏结束", "黑棋赢了！", QMessageBox::Ok);
            sleep(1);
            setEnabled(true);
        }
        else if(who==2)
        {
            update();
            setEnabled(false);
            //白棋赢了则弹出下面对话框
            QMessageBox::information(this, "游戏结束", "白棋赢了！", QMessageBox::Ok);
            sleep(1);
            setEnabled(true);
        }
    }
}

void MainWindow::startGame(void)//开始游戏按钮对应的槽函数
{
    if (Run == false)
    {
        Run = true;
        timer->start(1000);
        update();
    }
}
void MainWindow::pauseGame(void)//暂停游戏按钮所对应的槽函数
{
    if (Run == true)
    {
        Run = false;
        timer->stop();
        update();
    }

}
void MainWindow::backto(void)//悔棋按钮所对应的槽函数
{
    //执行悔棋函数
    if(GAME.Backto()==false){
        setEnabled(false);
        QMessageBox::information(this, "注意",
                "已经没有棋子！！！");
        sleep(1);
        setEnabled(true);
    }
    update();
}
void MainWindow::showAbout(void)//关于按钮所对应的槽函数
{
    QMessageBox::information(this, "关于五子棋游戏",
            "五子棋游戏__人机对战\t\n\n制作 by 鲁科辰 Colearo Lu");
}
void MainWindow::restartGame(void)//重新开始游戏按钮所对应的槽函数
{
    GAME.Clear();//执行棋盘数据清零
    Run=true;//清零后开始标志置为true
    timeI=0;//计数器清零
    time->setHMS(0,0,0,0);
    update();
}
void MainWindow::timeUpate()
{
    timeI++;
    QTime t=time->addSecs(timeI);
    lcd->display(t.toString("hh:mm:ss"));
}
