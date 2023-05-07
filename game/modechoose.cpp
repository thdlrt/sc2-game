#include "modechoose.h"
#include "ui_modechoose.h"
#include"gamestart.h"
#include"mapout.h"
#include"mapin.h"
modeChoose::modeChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modeChoose)
{
    ui->setupUi(this);
    //界面初始化
    QPixmap pix;
    QString icon=":/startcase/resource/modeChoose.png";
    if(!pix.load(icon))
        qDebug()<<"图片加载失败"<<icon<<Qt::endl;
    this->setFixedSize(853,480);
    this->setWindowTitle("StartCraft Defence");
    this->setWindowIcon(pix);
    pix=pix.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->back->setPixmap(pix);
    ui->back->setFixedSize(this->width(),this->height());
    //数据初始化
    map_data=readMapList();
    //表格初始化
    upcase();
}
void modeChoose::upcase()
{
    ui->tableWidget->setAlternatingRowColors(1);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(map_data.size());
    ui->tableWidget->setColumnWidth(4,45);
    ui->tableWidget->setColumnWidth(5,45);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->setMouseTracking(true);
     connect(ui->tableWidget, SIGNAL(cellEntered(int, int)), this, SLOT(slotCellEnter(int , int )));
    for(int i=0;i<map_data.size();i++)
    {
        QPushButton*button=new QPushButton(this);
        button->setText("选择");
        connect(button,SIGNAL(clicked()),this,SLOT(report()));
        ui->tableWidget->setCellWidget(i,4,button);
        QPushButton*button2=new QPushButton(this);
        button2->setText("导出");
        connect(button2,SIGNAL(clicked()),this,SLOT(report2()));
        ui->tableWidget->setCellWidget(i,5,button2);
        QTableWidgetItem*item;
        //qDebug()<<map_data[0].id;
        item=new QTableWidgetItem(map_data[i].id);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i,0,item);
        item=new QTableWidgetItem(map_data[i].name);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i,1,item);
        item=new QTableWidgetItem(map_data[i].dif);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i,2,item);
        item=new QTableWidgetItem(map_data[i].user);
        item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i,3,item);
    }
}
void modeChoose::report()
{
    QPushButton*a=qobject_cast<QPushButton*>(sender());
    if(a==NULL)
        return;
    QModelIndex q=ui->tableWidget->indexAt(QPoint(a->frameGeometry().x(),a->frameGeometry().y()));
    int i=q.row();
    //选择地图按钮
    gameStart *m=new gameStart(map_data[i].path);
    this->close();
    m->exec();
}
void modeChoose::report2()//导出地图
{
    QPushButton*a=qobject_cast<QPushButton*>(sender());
    if(a==NULL)
        return;
    QModelIndex q=ui->tableWidget->indexAt(QPoint(a->frameGeometry().x(),a->frameGeometry().y()));
    int i=q.row();
    mapout*m=new mapout(map_data[i].path);
    m->exec();
}
void modeChoose::slotCellEnter(int r, int c) {
    QTableWidgetItem *item = ui->tableWidget->item(r, c);
    if (item == nullptr) {
        return;
    }
    QToolTip::showText(QCursor::pos(), item->text());
}
 vector<mapList> modeChoose::readMapList()
{
    ifstream file((QCoreApplication::applicationDirPath()+"/mapdata.txt").toStdString(),ios::in);
    if(!file)
    {
        qDebug()<<"/mapdata.txt打开失败,重新创建"<<Qt::endl;
        ofstream file2;
        file2.open((QCoreApplication::applicationDirPath()+"/mapdata.txt").toStdString(),ios::out);
        file.open((QCoreApplication::applicationDirPath()+"/mapdata.txt").toStdString(),ios::in);
    }
    vector<mapList>temp;
    string s;
    while(getline(file,s))//按行读取
    {
        stringstream ss(s);//读取一行内每个数据
        string id,name,dif, user, path;
        ss>>id>>name>>dif>>user>>path;
       temp.push_back(mapList(QString::fromStdString(id),QString::fromStdString(name),QString::fromStdString(dif),QString::fromStdString(user),QString::fromStdString(path)));
    }
    file.close();
    return temp;
    //qDebug()<<map_data[0].id;
}
modeChoose::~modeChoose()
{
    delete ui;
}

void modeChoose::on_pushButton_clicked()//导入地图
{
    mapin*m=new mapin();
    m->exec();
    map_data=readMapList();
    this->upcase();//更新显示
}

