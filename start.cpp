#include "start.h"
#include "ui_start.h"
#include "game.h"

Start::Start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
}

Start::~Start()
{
}


void Start::on_pushButton_2_clicked()
{
    this->hide();
    game *g=new game();
    g->show();
}

