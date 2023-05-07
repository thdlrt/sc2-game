#include "mapin.h"
#include "ui_mapin.h"
#include"modechoose.h"
mapin::mapin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mapin)
{
    ui->setupUi(this);//自定义按钮
    uploadBtn=new myButton(":/game/resource/upmap.png",QSize(100,100));
    uploadBtn->setParent(this);
    connect(uploadBtn,SIGNAL(clicked()),this,SLOT(uploadBtn_clicked()));
    uploadBtn->move((int)this->width() * 0.75 - uploadBtn->width() * 0.5 , (int)this->height() * 0.4);
    ui->lineEdit->setReadOnly(true);
    map_data=modeChoose::readMapList();
}

mapin::~mapin()
{
    delete ui;
}
void mapin::uploadBtn_clicked()
{
    uploadBtn->movedown();
    uploadBtn->moveup();
    Delay(280);
    mapname=ui->mapname->text();
    difficult=ui->difficult->text();
    owner=ui->owner->text();
    qDebug()<<filein.toStdString().find_first_not_of(" ");//检验是否为空或只有空格
    if(filein==""||mapname==""||difficult==""||owner==""||mapname.toStdString().find_first_not_of(" ")==string::npos||
            difficult.toStdString().find_first_not_of(" ")==string::npos||owner.toStdString().find_first_not_of(" ")==string::npos)
    {
        QMessageBox::information(this,"注意","请先完善信息");
        return;
    }
    if(!map_data.empty())
    map_data.push_back(mapList(QString::number(map_data[map_data.size()-1].id.toInt()+1),mapname,difficult,owner,filein));
    else
    map_data.push_back(mapList(QString::number(1),mapname,difficult,owner,filein));
    writedata();
    QMessageBox::information(this,"注意","地图导入完成");
    this->close();
}

void mapin::on_pushButton_clicked()//获取文件路径
{
    QString curpath=QCoreApplication::applicationDirPath();
    filein=QFileDialog::getOpenFileName(this,"选择一个文件",curpath,"文本文件(*.txt)");
    ui->lineEdit->setText(filein);
}

void mapin::writedata()
{
    ofstream file((QCoreApplication::applicationDirPath()+"/mapdata.txt").toStdString(),ios::out);
    if(!file)
    {
        qDebug()<<"mapdata open fail：";
        return;
    }
    for(auto a:map_data)
    {
        file<<a.id.toStdString()<<" "<<a.name.toStdString()<<" "<<a.dif.toStdString()<<" "<<a.user.toStdString()<<" "<<a.path.toStdString()<<endl;
    }
    file.close();
}
