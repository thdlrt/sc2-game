#include "soundchoose.h"
#include "ui_soundchoose.h"

soundchoose::soundchoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::soundchoose)
{
    ui->setupUi(this);
    ui->horizontalSlider->setValue(99);
}

soundchoose::~soundchoose()
{
    delete ui;
}

void soundchoose::on_horizontalSlider_valueChanged(int value)
{
    if(value==0)
        ui->checkBox->setChecked(true);
    else
        ui->checkBox->setChecked(false);
    num=value;
}


void soundchoose::setnum(int val)
{
    ui->horizontalSlider->setValue(val);
}

void soundchoose::on_checkBox_clicked()
{
    if(!state)
    {
        ui->horizontalSlider->setValue(0);
    }
    else
    {
        ui->horizontalSlider->setValue(99);
    }
    state^=1;
}

