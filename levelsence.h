#ifndef LEVELSENCE_H
#define LEVELSENCE_H

#include <QMainWindow>
#include"playsence.h"
#include"dataconfig.h"

class LevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelSence(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    PlaySence* playSence = NULL;
    DataConfig dcf; // 不要这样写，因为Playscense也要用，最好存在堆上，传指针给playscense

signals:
    void callBackMainWindow();

};

#endif // LEVELSENCE_H
