#include "levelsence.h"
#include<QMenuBar>
#include<QPainter>
#include<QLabel>
#include<QTimer>
#include<QDebug>
#include "mypushbutton.h"
#include"mycoin.h"

LevelSence::LevelSence(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/Image/gameIcon/coin1.bmp"));
    this->setWindowTitle("select A level");

    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    QMenu* startM = bar->addMenu("开始");
    QAction* actionQuit = startM->addAction("退出");
    connect(actionQuit, &QAction::triggered, [=](){
        this->close();
    });

    // 返回
    MyPushButton* backBtn = new MyPushButton(":/Image/gameIcon/quit.bmp", ":/Image/gameIcon/quitSelected.bmp");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());
    connect(backBtn, &MyPushButton::clicked, [=](){

        // this->setGeometry(playSence->geometry());

        emit this->callBackMainWindow();
    });


    // play场景切换

    for (int i=0; i<20; i++){
        MyPushButton* menubtn = new MyPushButton(":/Image/Icon/levelIcon");
        menubtn->setParent(this);
        menubtn->setFixedSize(40, 40);
        menubtn->move(30+i%4 * 80, 100+i/4 * 80);

        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width()/5, menubtn->height()/5);
        label->setText(QString::number(i+1));
        label->move(30+i%4 * 80, 100+i/4 * 80);
        // label的对齐方式
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        // label设置穿透 让btn接受鼠标事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(menubtn, &MyPushButton::clicked, this, [=](){
            menubtn->zoomdown();
            menubtn->zoomup();
            if (this->dcf.myData.count(i+1) != 0){
                this->playSence = new PlaySence(i+1);

                playSence->setGeometry(this->geometry());

                playSence->setAttribute(Qt::WA_DeleteOnClose);
                QTimer::singleShot(200, this, [=](){
                    this->hide();
                    playSence->show();
                });
                connect(playSence, &PlaySence::callBackLevelWindow, this, [=](){
                    QTimer::singleShot(200, this, [=](){
                        qDebug()<< "back from play";
                        // 顺序颠倒失败
    //                    delete playSence;
    //                    playSence = nullptr;
                        this->setGeometry(playSence->geometry());
                        playSence->close();
                        this->show();
                        MyCoin::AllWin = false;


                    });
                });
            }

        });
    }

}

void LevelSence::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/bkg/bg.bmp");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

}
