#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //界面初始化
    QPixmap pix,pix2;
    QString icon=":/startcase/resource/mainIcon.png",icon2=":/startcase/resource/mainBack.png";
    if(!pix.load(icon))
        qDebug()<<"图片加载失败"<<icon<<Qt::endl;
    if(!pix2.load(icon2))
        qDebug()<<"图片加载失败"<<icon2<<Qt::endl;
    this->setFixedSize(1280,720);
    this->setWindowTitle("StartCraft Defence");
    this->setWindowIcon(pix);
    QLabel* back=new QLabel;
    back->setParent(this);
    pix2=pix2.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    back->setPixmap(pix2);
    back->setFixedSize(this->width(),this->height());
    //this->setWindowFlags(Qt::SplashScreen);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //开始按钮
    startBtn=new myButton(":/startcase/resource/startButton.png",QSize(250,128));
    startBtn->setParent(this);
    connect(startBtn,SIGNAL(clicked()),this,SLOT(startBtn_clicked()));
    startBtn->move((int)this->width() * 0.16 - startBtn->width() * 0.5 , (int)this->height() * 0.72);
    //设置按钮
    editBtn=new myButton(":/startcase/resource/edit.png",QSize(125,125));
    editBtn->setParent(this);
    connect(editBtn,SIGNAL(clicked()),this,SLOT(editBtn_clicked()));
    editBtn->move((int)this->width() * 0.82 - editBtn->width() * 0.5 , (int)this->height() * 0.72);
    //退出按钮
    exitBtn=new myButton(":/startcase/resource/exit.png",QSize(75,75));
    exitBtn->setParent(this);
    connect(exitBtn,SIGNAL(clicked()),this,SLOT(exitBtn_clicked()));
    exitBtn->move((int)this->width() * 0.95 - exitBtn->width() * 0.5 , (int)this->height() * 0.02);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::startBtn_clicked()
{
    startBtn->movedown();
    startBtn->moveup();
    Delay(280);
    modeChoose* m=new modeChoose;
    m->exec();

}
void MainWindow::editBtn_clicked()
{
    editBtn->movedown();
    editBtn->moveup();
    Delay(280);
    mainEdit* m=new mainEdit;
    m->exec();
}
void MainWindow::exitBtn_clicked()
{
    exitBtn->movedown();
    exitBtn->moveup();
    Delay(280);
    auto result=QMessageBox::question(this,"提醒","您即将退出游戏",QMessageBox::Yes|QMessageBox::No);
    if(result==QMessageBox::Yes)
        exit(0);
}
