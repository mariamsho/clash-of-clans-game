#include "cannon.h"
#include "qbrush.h"
#include "qgraphicssceneevent.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPixmap>
#include <QPointF>
#include <QtMath>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QWidget>


cannon::cannon()
{
    HP=10000;
    hp_origin=HP;
    setAcceptHoverEvents(true);


}
void cannon :: setr(int row)
{
    r=row;
}
void cannon :: setc(int col)
{
    c=col;
}
int cannon ::getr()
{
    return r;
}
int cannon::getc()
{
    return c;
}


void cannon:: set(int m,int h,QGraphicsScene* scene)
{
    r=m;
    c=h;

    cannonImage = new QGraphicsPixmapItem(QPixmap(":/result (1).png").scaledToHeight(50).scaledToWidth(50));
    //cannonImage->setPixmap(QPixmap(":/result (1).png").scaledToHeight(50).scaledToWidth(50));
    cannonImage->setTransformOriginPoint(cannonImage->boundingRect().center()); // Set transformation origin

    cannonImage->setPos(50 + 50 * c, 50 + 50 * r);
    scene->addItem(cannonImage);
    //QPixmap Cannon(":/result (1).png");
    //Cannon=Cannon.scaledToHeight(50);
    //Cannon=Cannon.scaledToWidth(50);
    //setPixmap(cannonImage);
    //setPos(50+50*c,50+50*r);
    // setRotationAngle(0);
    //updateRotation()
    cannon_scene=scene;


    QGraphicsRectItem *rectangle = new QGraphicsRectItem(50+r*50, 50+(c-0.5)*50, 50, 8); // (x, y, width, height)
    QGraphicsRectItem *healthbar = new QGraphicsRectItem(50+r*50, 50+(c-0.5)*50, 50, 8); // (x, y, width, height)
    rect = rectangle;
    hbar = healthbar;

    hbar->setBrush(QBrush(Qt::green));
    rect->setBrush(QBrush(Qt::white));

}
void cannon::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event)
    {
        QPointF cursorPos = mapToScene(event->pos());
        qDebug() << "Mouse Move Event - Cursor Pos:" << cursorPos;

        qreal angle = qAtan2(cursorPos.y() - cannonImage->pos().y(), cursorPos.x() - cannonImage->pos().x());
        setRotation(qRadiansToDegrees(angle));

        // Set the transformation origin point to the center of the item
        cannonImage->setTransformOriginPoint(cannonImage->boundingRect().center());
        if(cannon_scene)
        {
            cannon_scene->update();

        }
    }
    QGraphicsPixmapItem::mouseMoveEvent(event);
}




void cannon::sethp(int Hp)
{
    HP=Hp;
}
int cannon::gethp()
{
    return HP;
}
void cannon::get_damage(int amount)
{
    HP -= amount;
    if (HP <= 0)
    {
    }

    setHealthbar(HP);


}
bool cannon::isDestroyed()
{
    if (HP <= 0)
      return true;
    else
      return false;


}
QGraphicsRectItem* cannon:: getrectangle(){
    return rect;
}
QGraphicsRectItem* cannon::getHealthBar(){
    return hbar;
}
void cannon::setHealthbar(int hp){

    double w = hp/1000.0;
    hbar->setRect(50+r*50, 50+(c-0.5)*50, w*5, 8 );
    if (hp == 0){
      rect->setRect(50+r*50, 50+(c-0.5)*50, 0, 8);
    }


    bool red = false;
    if(hp <= hp_origin*0.40)
    {
      hbar->setBrush(QBrush(Qt::red));
      red = true;
    }

    if((hp <= hp_origin*0.75) && (!red))
    {
         hbar->setBrush(QBrush(Qt::yellow));
    }

}
