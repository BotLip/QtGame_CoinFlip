#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"mypushbutton.h"
#include"levelsence.h"
#include<QPixmap>
#include<QPainter>
#include<QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap(":/Image/gameIcon/coin4.bmp"));\
    this->setFixedSize(320, 588);
    this->setWindowTitle("嗨嗨嗨");

    connect(ui->actionQuitGame, &QAction::triggered, this, [=](){
        this->close();
    });

    MyPushButton* startbtn = new MyPushButton(":/Image/gameIcon/start.bmp");
    startbtn->setParent(this);
    startbtn->move(this->width()/2 - startbtn->width()/2, this->height()*0.7);

    this->ls = new LevelSence(this);

    // 这是场景切换的监听
    connect(ls, &LevelSence::callBackMainWindow, this, [=](){
        this->setGeometry(ls->geometry());
        QTimer::singleShot(200, this, [=](){
            this->show();
            ls->hide();
        });
    });
    // 这是开始场景的切换
    connect(startbtn, &MyPushButton::clicked, this, [=](){
        startbtn->zoomdown();
        startbtn->zoomup();
        // 点完stat就levelSence  这是一个QTimer的延时函数
        QTimer::singleShot(200, this, [=](){
            ls->setGeometry(this->geometry());
            this->hide();
            ls->show();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent *){     // 开局触发此事件
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/bkg/bg.bmp");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
