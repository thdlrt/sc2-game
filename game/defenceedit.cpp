#include "defenceedit.h"
#include "ui_defenceedit.h"
defenceEdit::defenceEdit(int resouce2,defeat*d,QWidget *parent) :
    QDialog(parent),resouce2(resouce2),
    ui(new Ui::defenceEdit)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    //页面初始化
    this->d=d;
    ui->labelpix->setFixedSize(160,160);
    pix.load(":/game/resource/resource2.png");
    pix3.load(":/game/resource/addatt.png");
    pix4.load(":/game/resource/frozen.png");
    pix5.load(":/game/resource/range.png");
    pix6.load(":/game/resource/hp.png");
    pix7.load(":/game/resource/fireup.png");
    pix=pix.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix2=pix2.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix3=pix3.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix4=pix4.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix5=pix5.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix6=pix6.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix7=pix7.scaled(30,30,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->icon1->setFixedSize(30,30);
    ui->icon2->setFixedSize(30,30);
    ui->icon3->setFixedSize(30,30);
    ui->icon1->setPixmap(pix3);
    ui->icon2->setPixmap(pix4);
    ui->icon3->setPixmap(pix5);
    ui->icon4->setPixmap(pix6);
    ui->icon5->setPixmap(pix7);
    ui->label_icon->setFixedSize(30,30);
    ui->label_icon->setPixmap(pix);
    if(d->getrange()==1)
    {
        pix2.load(":/game/resource/kuangrz.png");
        ui->progressBar->setValue(d->gethp()/150.0*100);
    }
    else if(d->getrange()==3)
    {
        pix2.load(":/game/resource/soul.png");
        ui->progressBar->setValue(d->gethp()/50.0*100);
    }
    pix2=pix2.scaled(160,160,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->labelpix->setPixmap(pix2);
    //定时器
    time_out=new QTimer;
    time_out->start(500);
    connect(time_out,SIGNAL(timeout()),this,SLOT(upcase()));
}
void defenceEdit::upcase()
{
    if(!isclose)
    {
        ui->progressBar->setValue(100.0*d->gethp()/d->gethp_max());//血量
        if(d->state.find(1)!=d->state.end())//已有技能
        {
            ui->get1->setFixedSize(30,30);
            ui->get1->setPixmap(pix3);
        }
        if(d->state.find(2)!=d->state.end())
        {
            ui->get2->setFixedSize(30,30);
            ui->get2->setPixmap(pix4);
        }
        if(d->state.find(3)!=d->state.end())
        {
            ui->get3->setFixedSize(30,30);
            ui->get3->setPixmap(pix5);
        }
        if(d->state.find(4)!=d->state.end())
        {
            ui->get4->setFixedSize(30,30);
            ui->get4->setPixmap(pix6);
        }
        if(d->state.find(5)!=d->state.end())
        {
            ui->get5->setFixedSize(30,30);
            ui->get5->setPixmap(pix7);
        }
    }
}
void defenceEdit::close()//关闭
{
    isclose=1;
    delete this;
}
defenceEdit::~defenceEdit()
{
    delete ui;
}

void defenceEdit::on_pushButton_delete_clicked()
{
    auto result=QMessageBox::question(this,"注意","删除后只会退还一半的晶体矿",QMessageBox::Yes,QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        emit addresouce1(d->getprice()/2);
        d->hp=0;
       this->close();
    }
}


void defenceEdit::on_pushButton_1_clicked()//攻击*2
{
    if(d->state.size()>=2)
    {
        QMessageBox::information(this,"注意","一个单位最多只能获得两种升级");
        return;
    }
    if(d->state.find(1)!=d->state.end())
    {
        QMessageBox::information(this,"注意","请不要重复升级");
        return;
    }
    if(resouce2<1)
    {
        sound_effect_resource2->play();
        return;
    }
    emit spendresouce2(1);
    sound_effect_research->play();
    d->setstate(1);
}

void defenceEdit::on_pushButton_2_clicked()//冰冻
{
    if(d->state.size()>=2)
    {
        QMessageBox::information(this,"注意","一个单位最多只能获得两种升级");
        return;
    }
    if(d->state.find(2)!=d->state.end())
    {
        QMessageBox::information(this,"注意","请不要重复升级");
        return;
    }
    if(d->state.find(5)!=d->state.end())
    {
        QMessageBox::information(this,"注意","不能同时具有冰冻和燃烧属性");
        return;
    }
    if(resouce2<2)
    {
        sound_effect_resource2->play();
        return;
    }
    emit spendresouce2(2);
    sound_effect_research->play();
    d->setstate(2);
}


void defenceEdit::on_pushButton_3_clicked()//范围
{
    if(d->state.size()>=2)
    {
        QMessageBox::information(this,"注意","一个单位最多只能获得两种升级");
        return;
    }
    if(d->state.find(3)!=d->state.end())
    {
        QMessageBox::information(this,"注意","请不要重复升级");
        return;
    }
    if(resouce2<3)
    {
        sound_effect_resource2->play();
        return;
    }
    emit spendresouce2(3);
    sound_effect_research->play();
    d->setstate(3);
}


void defenceEdit::on_pushButton_4_clicked()//血
{
    if(d->state.size()>=2)
    {
        QMessageBox::information(this,"注意","一个单位最多只能获得两种升级");
        return;
    }
    if(d->state.find(4)!=d->state.end())
    {
        QMessageBox::information(this,"注意","请不要重复升级");
        return;
    }
    if(resouce2<1)
    {
        sound_effect_resource2->play();
        return;
    }
    emit spendresouce2(1);
    sound_effect_research->play();
    d->setstate(4);
}


void defenceEdit::on_pushButton_clicked()
{
    if(d->state.size()>=2)
    {
        QMessageBox::information(this,"注意","一个单位最多只能获得两种升级");
        return;
    }
    if(d->state.find(2)!=d->state.end())
    {
        QMessageBox::information(this,"注意","不能同时具有冰冻和燃烧属性");
        return;
    }
    if(d->state.find(5)!=d->state.end())
    {
        QMessageBox::information(this,"注意","请不要重复升级");
        return;
    }
    if(resouce2<2)
    {
       sound_effect_resource2->play();
        return;
    }
    emit spendresouce2(2);
    sound_effect_research->play();
    d->setstate(5);
}


void defenceEdit::on_delete_1_clicked()
{
    if(d->state.find(1)==d->state.end())
        return;
    auto result=QMessageBox::question(this,"注意","删除后不会返回任何费用",QMessageBox::Yes,QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        d->state.erase(1);
    }
    ui->get1->clear();
}


void defenceEdit::on_delete_2_clicked()
{
    if(d->state.find(2)==d->state.end())
        return;
    auto result=QMessageBox::question(this,"注意","删除后不会返回任何费用",QMessageBox::Yes,QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        d->state.erase(2);
    }
    ui->get2->clear();
}


void defenceEdit::on_delete_3_clicked()
{
    if(d->state.find(3)==d->state.end())
        return;
    auto result=QMessageBox::question(this,"注意","删除后不会返回任何费用",QMessageBox::Yes,QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        d->state.erase(3);
    }
    ui->get3->clear();
}


void defenceEdit::on_delete_4_clicked()
{
    if(d->state.find(4)==d->state.end())
        return;
    auto result=QMessageBox::question(this,"注意","删除后不会返回任何费用",QMessageBox::Yes,QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        d->state.erase(4);
    }
    ui->get4->clear();
}


void defenceEdit::on_delete_5_clicked()
{
    if(d->state.find(5)==d->state.end())
        return;
    auto result=QMessageBox::question(this,"注意","删除后不会返回任何费用",QMessageBox::Yes,QMessageBox::No);
    if(result==QMessageBox::Yes)
    {
        d->state.erase(5);
    }
    ui->get5->clear();
}

