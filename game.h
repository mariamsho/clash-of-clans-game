#ifndef GAME_H
#define GAME_H
#include <QGraphicsRectItem>
#include <QColor>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QTimer>
#include <QVector>
#include "mainwindow.h"
#include"castle.h"
#include<QVector>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include<QFile>
#include<QDialog>
#include<QPixmap>
#include<QTextStream>
#include<QDebug>
#include <QString>
#include"cannon.h"
#include <QObject>
#include "castle.h"
#include "timer.h"
#include "powerups.h"
class game:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    game();
    int get_rows();
    int get_columns();
    void start();
    int get_num_troop_killed();
    void set_num_troop_killed(int num_troop_killed);
    QGraphicsScene* getscene();
    bool Loss();
    bool Win();
private:
    QTimer* troop_timer;
    QTimer* poweruptimer;
    QTimer* checkertimer;
    int r;
    int c;
    int s;
    int m;
    int column;
    int row;
    int num_troop_killed;
    cannon* C;
    QTimer* bullet_timer;
    QGraphicsScene* scene;
    Timer* timer;
    Castle *castle;
    int bullet_damage;
    QVector<std::pair<int,int>> v;
    QGraphicsView* view;
//    powerups* pwup = nullptr;
//    bool powerhit;

public slots:

    void create_troop();
    void create_bullet();
    void create_powerup();
//    void checkpowerup();

};

#endif // GAME_H
