#include "mainedit.h"
#include "ui_mainedit.h"

mainEdit::mainEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainEdit)
{
    this->setAttribute(Qt::WA_DeleteOnClose);//防止关闭后不销毁不保存数据
    ui->setupUi(this);
    ui->widget->setnum(bgmvalue);
    ui->widget_2->setnum(gamevalue);
}

mainEdit::~mainEdit()
{
    delete ui;
}

void mainEdit::on_pushButton_clicked()
{
    bgmvalue=ui->widget->getnum();
    gamevalue=ui->widget_2->getnum();
    this->close();
}


void mainEdit::on_pushButton_2_clicked()
{
    this->close();
}

