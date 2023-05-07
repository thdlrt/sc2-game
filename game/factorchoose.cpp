#include "factorchoose.h"
#include "ui_factorchoose.h"

factorChoose::factorChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::factorChoose)
{
    ui->setupUi(this);
}

factorChoose::~factorChoose()
{
    delete ui;
}
