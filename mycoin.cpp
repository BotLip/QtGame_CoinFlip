#include "mycoin.h"
#include<QPixmap>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}
bool MyCoin::AllWin = false;

MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if (!ret){}
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width()/3, pix.height()/3));

    timer1 = new QTimer();
    timer2 = new QTimer();

    connect(timer1, &QTimer::timeout, this, [=](){
        QPixmap pix;
        QString str = QString(":/Image/gameIcon/coin%1.bmp").arg(this->min++);
        pix.load(str);
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()/3, pix.height()/3));
        if (this->min > this->max){
            this->min = 1;
            timer1->stop();
            this->isAni = false;
        }
    });

    connect(timer2, &QTimer::timeout, this, [=](){
        QPixmap pix;
        QString str = QString(":/Image/gameIcon/coin%1.bmp").arg(this->max--);
        pix.load(str);
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()/3, pix.height()/3));
        if (this->min > this->max){
            this->max = 4;
            timer2->stop();
            this->isAni = false;
        }
    });

}


void MyCoin::changeFlag(){

    this->isAni = true;

    if (this->flag){
        timer1->start(50);
        flag = false;
    }else{
        flag = true;
        timer2->start(50);
    }

}

void MyCoin::mousePressEvent(QMouseEvent *e){
    if (this->isAni || AllWin){
        return ;
    }else{
        QPushButton::mousePressEvent(e);
    }
}
