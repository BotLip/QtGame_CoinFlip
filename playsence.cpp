#include "playsence.h"
#include"mypushbutton.h"
#include"mycoin.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QPropertyAnimation>

//PlaySence::PlaySence(QWidget *parent) : QMainWindow(parent)
//{

//}

PlaySence::PlaySence(int levelNum){
    this->level = levelNum;

    // qDebug()<< level;
    this->setFixedSize(320, 588);
    this->setWindowTitle("嗨嗨嗨"+QString::number(level));

    QMenuBar* mb = menuBar();
    this->setMenuBar(mb);
    QMenu* startM = mb->addMenu("开始");
    QAction* quitAction = startM->addAction("退出");
    connect(quitAction, &QAction::triggered, this, [=](){
       this->close();
    });

    MyPushButton* backBtn = new MyPushButton(":/Image/gameIcon/quit.bmp", ":/Image/gameIcon/quitSelected.bmp");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(), this->height()-backBtn->height());
    connect(backBtn, &MyPushButton::clicked, [=](){
        // qDebug()<< "back";
        QTimer::singleShot(200, this, [=](){
            emit this->callBackLevelWindow();
        });

    });

    // Success
    QLabel* winLabel = new QLabel;
    QPixmap winPix;
    winPix.load(":/Image/gameIcon/win.bmp");
    winLabel->setGeometry(0, 0, winPix.width(), winPix.height());
    winLabel->setPixmap(winPix);
    winLabel->setParent(this);
    winLabel->move(this->width() - winPix.width(), -winPix.height());



    // 布置关卡
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            QString path;
            MyCoin* coin;
            if (this->dcf.myData[level][i][j] == 1){
                path = ":/Image/gameIcon/coin1.bmp";
                coin = new MyCoin(path);
                coin->flag = true;
            }else{
                path = ":/Image/gameIcon/coin4.bmp";
                coin = new MyCoin(path);
                coin->flag = false;
            }
            coin->poxX = i;
            coin->poxY = j;
            coin->setFixedSize(30, 30);
            coin->setParent(this);
            coin->move(57+i*50, 200+j*50);

            coins[i][j] = coin;

            connect(coin, &MyCoin::clicked, this, [=](){
                coin->changeFlag();
                MyCoin::AllWin = true;
                QTimer::singleShot(300, this, [=](){
                    this->dcf.myData[level][i][j] = dcf.myData[level][i][j] == 0? 1: 0;
                    int X = coin->poxX;
                    int Y = coin->poxY;
                    if (X + 1 <= 3){
                        coins[X+1][Y]->changeFlag();
                        dcf.myData[level][X+1][Y]= dcf.myData[level][X+1][Y] == 0? 1: 0;
                    }
                    if (X - 1 >= 0){
                        coins[X-1][Y]->changeFlag();
                        dcf.myData[level][X-1][Y]= dcf.myData[level][X-1][Y] == 0? 1: 0;
                    }
                    if (Y + 1 <= 3){
                        coins[X][Y+1]->changeFlag();
                        dcf.myData[level][X][Y+1]= dcf.myData[level][X][Y+1] == 0? 1: 0;
                    }
                    if (Y - 1 >= 0){
                        coins[X][Y-1]->changeFlag();
                        dcf.myData[level][X][Y-1]= dcf.myData[level][X][Y-1] == 0? 1: 0;
                    }
                    MyCoin::AllWin = false;
                    qDebug()<< "here";
                    this->isWin = true;
                    for (int m=0; m<4; m++){
                        for (int n=0; n<4; n++){
                            if (!coins[m][n]->flag){
                                isWin = false;
                                break;
                            }
                        }
                        if (!isWin)
                            break;
                    }
                    if (this->isWin){
                        qDebug()<< "u WIn";
                        MyCoin::AllWin = true;  // 禁止按钮
                        QPropertyAnimation* ani = new QPropertyAnimation(winLabel, "geometry");
                        ani->setDuration(1000);
                        ani->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        ani->setEndValue(QRect(winLabel->x(), winLabel->y()+114,winLabel->width(), winLabel->height()));
                        ani->setEasingCurve(QEasingCurve::OutBounce);
                        ani->start();
                    }

                });
            });

        }
    }

}

void PlaySence::paintEvent(QPaintEvent *){     // 开局触发此事件
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/bkg/bg.bmp");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
