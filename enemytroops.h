#ifndef ENEMYTROOPS_H
#define ENEMYTROOPS_H
#include<QGraphicsPixmapItem>
#include <QTimer>
#include<QObject>
typedef bool flag;
class enemytroops: public QObject ,public QGraphicsPixmapItem
{
Q_OBJECT
private:
    int HP;
    int damage;
    int r;
    int c;
    int z;
    int a;
    QTimer* timer;
    flag can_move = true;
    QTimer* timer2;
    int changer;

public:

    enemytroops();
    void setr(int row);
    void setc(int col);
    int getr();
    int getc();
    void set(int m,int h);
    void set2(int z,int a);
    void sethp(int Hp);
    int gethp();
    void create_troop();
    void attackFence();
    void attackCannon();
    void get_damage(int amount);
    void attackCastle();
    bool isDestroyed();


public slots:
    void move();
    void motion();
};

#endif // ENEMYTROOPS_H
