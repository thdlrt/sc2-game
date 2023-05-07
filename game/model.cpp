#include "model.h"
#include "ui_model.h"

model::model(QString picture,QString distribe,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::model)
{
    ui->setupUi(this);
    //界面初始化
    QPixmap pix(picture);
    ui->textEdit->setPlainText(distribe);
    pix=pix.scaled(ui->picture->width(),ui->picture->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->picture->setPixmap(pix);
    QPalette label_palette;
    label_palette.setColor(QPalette::WindowText,QColor(0,0,0));
    ui->backcolor->setFixedSize(this->width(),this->height());
    ui->backcolor->setAutoFillBackground(true);
    ui->backcolor->setPalette(label_palette);
    ui->textEdit->setReadOnly(1);
    //选择按钮
    Btn=new myButton(":/game/resource/chooseBtn.png",QSize(114,50));
    Btn->setParent(this);
    //connect(Btn,SIGNAL(clicked()),p,SLOT(Btn_clicked()));
    Btn->move((int)this->width()*0.88 - Btn->width() * 0.5 -2.5, (int)this->height() *0.6);
}

model::~model()
{
    delete ui;
}
