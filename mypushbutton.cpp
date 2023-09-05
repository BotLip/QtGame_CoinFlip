#include "mypushbutton.h"
#include<QPixmap>
#include<QPropertyAnimation>    // 动画属性



//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    this->normalPath = normalImg;
    this->pressPath = pressImg;

    QPixmap pixnor;
    QPixmap pixpre;
    bool retnor = pixnor.load(normalPath);
    bool retpre = pixpre.load(pressPath);
    this->setFixedSize(pixnor.width(), pixnor.height());

    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixnor);
    this->setIconSize(QSize(pixnor.width()/2, pixnor.height()/2));

}

void MyPushButton::zoomdown(){
    QPropertyAnimation* ani = new QPropertyAnimation(this, "geometry");
    ani->setDuration(200);
    ani->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    ani->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    ani->start();
}

void MyPushButton::zoomup(){
    QPropertyAnimation* ani = new QPropertyAnimation(this, "geometry");
    ani->setDuration(200);
    ani->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    ani->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    ani->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *ev){
    if (this->pressPath != ""){
        QPixmap pixpre;
        bool retpre = pixpre.load(pressPath);
        this->setFixedSize(pixpre.width(), pixpre.height());

        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixpre);
        this->setIconSize(QSize(pixpre.width(), pixpre.height()));
    }
    return QPushButton::mousePressEvent(ev);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *ev){
    if (this->pressPath != ""){
        QPixmap pixnor;
        bool retnor = pixnor.load(normalPath);
        this->setFixedSize(pixnor.width(), pixnor.height());

        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixnor);
        this->setIconSize(QSize(pixnor.width(), pixnor.height()));
    }
    return QPushButton::mouseReleaseEvent(ev);
}
