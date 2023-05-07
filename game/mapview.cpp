#include "mapview.h"
#include "ui_mapviex.h"

mapViex::mapViex(QString path,QWidget *parent) :path(path),
    QDialog(parent),
    ui(new Ui::mapViex)
{
    ui->setupUi(this);
}

mapViex::~mapViex()
{
    delete ui;
}
