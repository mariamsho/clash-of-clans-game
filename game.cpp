#include"game.h"
#include<QGraphicsScene>
#include<QTextStream>
#include"timer.h"
#include"castle.h"
#include"fence.h"
#include"enemytroops.h"
#include"bullet.h"
#include<QGraphicsView>
#include"gameover.h"
#include "powerups.h"
#include <QDebug>





game::game()
{
    view= new QGraphicsView();
    scene=new QGraphicsScene();
     view->setWindowTitle("The Game");
    bullet_damage=100;
    start();
}
void game::start()
{
    Timer* timer;
    timer=new Timer();
    QFont f;
    f.setPointSize(20);
    timer->setFont(f);
    timer->setPos(100,100);
    timer->setPlainText("5:00");
    this->timer=timer;
    QFile file2("C:/Users/maria/Downloads/PRJ.final2/PRJ/ClashOfClansDefensiveVersion/map (1).txt");
    file2.open(QIODevice::ReadOnly);
    QTextStream stream2(&file2);
    QString x;
    int y=0;
    while(!stream2.atEnd())
    {
        stream2 >> x;
        int z=x.toInt();
        if(z==2)
            y++;
    }
    int k=0;
    QVector <fence*> fences;
    fences.resize(y);
    for(int i=0;i<y;i++)
    {
        fences[i]=new fence();
    }
    QFile file3("C:/Users/maria/Downloads/PRJ.final2/PRJ/ClashOfClansDefensiveVersion/map (1).txt");
    file3.open(QIODevice::ReadOnly);
    QTextStream stream3(&file3);
    QString line;
    int rows(0);
    while(!stream3.atEnd())
    {
        line=stream3.readLine();
        rows++;
    }
    QFile file4("C:/Users/maria/Downloads/PRJ.final2/PRJ/ClashOfClansDefensiveVersion/map (1).txt");
    file4.open(QIODevice::ReadOnly);
    QTextStream stream4(&file4);
    QString line2;
    int columns(0);
    while(!stream4.atEnd())
    {
        line2=stream4.readLine();
        columns++;
    }

    row=rows;
    column=columns;
    QFile file("C:/Users/maria/Downloads/PRJ.final2/PRJ/ClashOfClansDefensiveVersion/map (1).txt");
    file.open(QIODevice::ReadOnly);
    QVector<QVector<int>> boarddata;
    boarddata.resize(row);

    for (int i = 0; i < row; i++)
    {
        boarddata[i].resize(column);
    }
    QTextStream stream(&file);
    QString temp;
    Castle* Mcastle= new Castle();
    cannon* MAcannon= new cannon();
    enemytroops troop;

    QPixmap grass(":/download (1).jpeg");
    grass=grass.scaledToHeight(50);
    grass=grass.scaledToWidth(50);
    QVector<std::pair<int,int>> v;
    QFile file6("map (1).txt");
    file6.open(QIODevice::ReadOnly);
    QTextStream stream6(&file6);

    QVector<QVector<QGraphicsPixmapItem*>> boardimages;
    boardimages.resize(rows);

    for (int i = 0; i < rows; i++)
    {
        boardimages[i].resize(columns);
        for (int j =0 ; j < columns; j++)
        {
            boardimages[i][j] = new QGraphicsPixmapItem(nullptr);
        }
    }

    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
        {
            boardimages[i][j]->setPixmap(grass);
            boardimages[i][j]->setPos(50+50*j,50+50*i);
            scene->addItem(boardimages[i][j]);

        }

    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
        {
            stream >> temp;
            boarddata[i][j]=temp.toInt();
        }
    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
        {
            stream6 >> temp;
            if(boarddata[i][j]==0)
            {
                v.push_back({i,j});
            }
        }

    for(int i=0;i<row;i++)
        for(int j=0;j<column;j++)
        {
            if(boarddata[i][j]==1)
            {
                Mcastle->set(i,j);

            }
            else if(boarddata[i][j]==2)
            {
                fences[k]->set(i,j);
                k++;

            }
            else if(boarddata[i][j]==3)
            {
                MAcannon->set(i,j,scene);
            }
            boardimages[i][j]->setPos(50+50*j,50+50*i);
            scene->addItem(boardimages[i][j]);
        }
    for(int i=0;i<rows;i++ )
    {
        for(int j=0;j<columns;j++)
        {
            if(boarddata[i][j]==0 || boarddata[i][j]==5)
            boardimages[i][j]->setPixmap(grass);

        }
    }


    troop_timer=new QTimer(this);
    connect(troop_timer,SIGNAL(timeout()),this,SLOT (create_troop()));
    troop_timer->start(2500);

    poweruptimer = new QTimer(this);
    connect(poweruptimer,SIGNAL(timeout()),this, SLOT(create_powerup()));
    poweruptimer->start(8000);

    bullet_timer = new QTimer(this);
    connect(bullet_timer, SIGNAL(timeout()), this, SLOT(create_bullet()));
    bullet_timer->start(500);

    C=MAcannon;
    castle=Mcastle;
    this->r = Mcastle->getr();
    this->c = Mcastle->getc();
    this->s = MAcannon->getr();
    this->m = MAcannon->getc();
    this->v = v;
    if(MAcannon->isDestroyed())
    {
        bullet_timer->stop();
    }


    for(int i=0;i<y;i++)
    {
        scene->addItem(fences[i]);
    }

    scene->addItem(timer);
    scene->addItem(Mcastle);
    scene->addItem(Mcastle->getrectangle());
    scene->addItem(Mcastle->getHealthBar());
    scene->addItem(MAcannon);
    scene->addItem(MAcannon->getrectangle());
    scene->addItem(MAcannon->getHealthBar());
    view->setScene(scene);
    view->setFixedSize(50*get_rows(),50*get_columns());
    view->setMouseTracking(true);
    view->show();
}


QGraphicsScene* game:: getscene()
{
    return scene;
}


void game:: create_powerup()
{
    QRandomGenerator* generator;
    generator = QRandomGenerator::global();
    int randomNumberInt = generator->bounded(0, v.size());

    powerups* powerup;
    powerup= new powerups(v[randomNumberInt].first, v[randomNumberInt].second );
    scene->addItem(powerup);

}


void game:: create_troop()
{
    int front = 0;
    int front2=0;
    QRandomGenerator* generator;
    generator = QRandomGenerator::global();
    int randomNumber = generator->generate();
    int randomNumberInt = generator->bounded(0, v.size());

    front=randomNumberInt;


    enemytroops* enemy;
    enemy= new enemytroops();
    enemy->set(v[front].first, v[front].second);
    enemy->set2(r, c);
    scene->addItem(enemy);
    if(enemy->isDestroyed())
    {
        num_troop_killed++;
        qDebug() << "troop killed";
    }
    if(num_troop_killed >= 20)
    {
        this->bullet_damage+=0.1*bullet_damage;
        num_troop_killed = 0;
    }
    if(Loss())
    {
        this->view->hide();
        gameOver *Over=new gameOver(NULL,1);
        //Over->show();
        troop_timer->stop();
    }
    if(Win())
    {
        this->view->hide();
        gameOver *Over=new gameOver(NULL,2);
        troop_timer->stop();

    }


}
void game::create_bullet()
{
    bullet* sbullet;
    sbullet = new bullet(bullet_damage,castle);
    sbullet->set(s, m);
    scene->addItem(sbullet);
    if(C->isDestroyed())
    {
        bullet_timer->stop();
    }
}
int game::get_columns()
{
    return column;
}
int game::get_rows()
{
    return row
        ;
}
int game::get_num_troop_killed()
{
    return num_troop_killed;
}
void game::set_num_troop_killed(int num_troop_killed)
{
    this->num_troop_killed=num_troop_killed;
}
bool game::Loss()
{
    if(castle->isDestroyed())
    {
        return true;
    }
}
bool game::Win()
{
    if(timer->get_time_remaining()<=0)
    {
        return true;
    }
    return false;
    }

