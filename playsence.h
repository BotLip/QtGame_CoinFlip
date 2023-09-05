#ifndef PLAYSENCE_H
#define PLAYSENCE_H

#include <QMainWindow>
#include<mycoin.h>
#include"dataconfig.h"

class PlaySence : public QMainWindow
{
    Q_OBJECT
public:
    // explicit PlaySence(QWidget *parent = nullptr);
    PlaySence(int );
    int level;
    void paintEvent(QPaintEvent*);
    DataConfig dcf;
    MyCoin* coins[4][4];
    bool isWin;
signals:
    void callBackLevelWindow();
};

#endif // PLAYSENCE_H
