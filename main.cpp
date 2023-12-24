#include "mainwindow.h"
#include<QVector>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include<QFile>
#include<QDialog>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include<QTextStream>
#include<QDebug>
#include <QString>
#include <QRandomGenerator>
#include <QTimer>
#include <QObject>
#include "start.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QGraphicsView view;
    Start s;
    s.show();



    return a.exec();
}

