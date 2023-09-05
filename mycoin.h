#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QString>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);
    void changeFlag();
    void mousePressEvent(QMouseEvent* );
    int poxX;
    int poxY;
    bool flag;
    QTimer* timer1;
    QTimer* timer2;
    static bool AllWin;
private:
    int min = 1;
    int max = 4;
    bool isAni;


signals:

};

#endif // MYCOIN_H
