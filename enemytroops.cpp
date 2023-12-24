#include "enemytroops.h"
#include <QApplication>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QtCore>
#include "cannon.h"
#include "castle.h"
#include "fence.h"
/*enemytroops::enemytroops(QObject *parent): QObject(parent)
{
    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT (move()));
    timer->start(30);

}*/
enemytroops::enemytroops()
{
    timer = new QTimer(this);
    damage=100;
    HP=1000;
    timer2=new QTimer(this);
    changer = 1;

}
void enemytroops :: setr(int row)
{
    r=row;
}
void enemytroops :: setc(int col)
{
    c=col;
}
int enemytroops ::getr()
{
    return r;
}
int enemytroops::getc()
{
    return c;
}

void enemytroops::sethp(int Hp)
{
    HP=Hp;
}
int enemytroops::gethp()
{
    return HP;
}
void enemytroops:: set(int m,int h)
{
    r=m;
    c=h;
    QPixmap Enemytroop(":/result (4) (1).png");
    Enemytroop=Enemytroop.scaledToHeight(50);
    Enemytroop=Enemytroop.scaledToWidth(50);
    setPixmap(Enemytroop);
    setPos(50+50*c,50+50*r);
    connect(timer,SIGNAL(timeout()),this,SLOT (move()));
    timer->start(16);
    connect(timer2,SIGNAL(timeout()),this,SLOT (motion()));
    timer2->start(220);

}
void enemytroops::set2(int z,int a)
{
    this->z=z;
    this->a=a;
}
void enemytroops ::move()
{
    attackFence();
    attackCannon();
    attackCastle();
 }

void enemytroops::motion()
{
    if(can_move)
    {
      if(changer==1)
      {
          QPixmap Enemytroop2(":/troopmotion_1 (1).png");
          Enemytroop2=Enemytroop2.scaledToHeight(52);
          Enemytroop2=Enemytroop2.scaledToWidth(52);
          setPixmap(Enemytroop2);
          changer=2;

      }
      else if(changer==2)
      {
          QPixmap Enemytroop3(":/troopmotion_2 (1).png");
          Enemytroop3=Enemytroop3.scaledToHeight(45);
          Enemytroop3=Enemytroop3.scaledToWidth(45);
          setPixmap(Enemytroop3);
          changer=1;
      }
    }
//    else
//    {
//      QPixmap Enemytroop(":/result (4) (1).png");
//      Enemytroop=Enemytroop.scaledToHeight(50);
//      Enemytroop=Enemytroop.scaledToWidth(50);
//      setPixmap(Enemytroop);
//    }

}

void enemytroops::attackFence()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_items) {
      if (typeid(*item) == typeid(fence)) {
	can_move = false;
	fence *Fence = static_cast<fence *>(item);
	Fence->damage(damage);
	if (Fence->isDestroyed()) {
	  can_move = true;
	  scene()->removeItem(Fence);
	}
    }
    }
}
void enemytroops::get_damage(int amount)
{
    HP -= amount;
    if (HP <= 0) {
      this->deleteLater();
    }
}
void enemytroops::attackCannon()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_items) {
      if (typeid(*item) == typeid(cannon)) {
	can_move = false;
	cannon *c = static_cast<cannon *>(item);
	c->get_damage(damage);
	if (c->isDestroyed()) {
	  can_move = true;
	  scene()->removeItem(c);
	}
      }
    }
}
void enemytroops::attackCastle()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    foreach (QGraphicsItem *item, colliding_items)
    {
    if (typeid(*item) == typeid(Castle))
    {
        Castle *c = static_cast<Castle *>(item);
        c->get_damage(damage);
        if (c->isDestroyed())
    {
	  can_move = true;
	  scene()->removeItem(c);
	}
      }
    }
}
bool enemytroops::isDestroyed()
{
    if (HP <= 0)
      return true;

    else
      return false;
}


