#ifndef CANNON_H
#define CANNON_H
#include<QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QColor>
#include <QMouseEvent>
#include <QPixmap>
#include <QPointF>
#include <QtMath>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QtMath>
#include <QPainter>
#include <QWidget>


class cannon : public QGraphicsPixmapItem/*, public QWidget {
    Q_OBJECT*/
{
private:
    int HP;
    int r;
    int c;
    double hp_origin;
    QGraphicsRectItem* rect;
    QGraphicsRectItem* hbar;
 //   QPixmap* Cannon2;
public:
    cannon();
    void setr(int row);
    void setc(int col);
    int getr();
    QGraphicsScene* cannon_scene;
    int getc();
    void set(int m,int h,QGraphicsScene* scene);
    void sethp(int Hp);
    int gethp();
    void get_damage(int amount);
    bool isDestroyed();
    QPoint Point;
    QGraphicsRectItem* getrectangle();
    QGraphicsRectItem* getHealthBar();
    QGraphicsPixmapItem* cannonImage;
    void setHealthbar(int hp);
    void  mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;
//    void setRotatingPixmap(QPixmap* pixmap);

//    void setRotationAngle(qreal angle);
//    void updateRotation(const QPointF& cursorPos);


};


#endif // CANNON_H
