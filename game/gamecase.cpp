#include "gamecase.h"
#include "ui_gamecase.h"
#include"QTableWidget"
gameCase::gameCase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameCase)
{
    ui->setupUi(this);
}

gameCase::~gameCase()
{
    delete ui;
}
