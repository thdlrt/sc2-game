#include "mapout.h"
#include "ui_mapout.h"

mapout::mapout(QString s,QWidget *parent) :path(s),
    QDialog(parent),
    ui(new Ui::mapout)
{
    ui->setupUi(this);
    ui->lineEdit->setReadOnly(true);
    readdata();//读入文件
    QPixmap pix(QString::fromStdString(text[16]));
    pix=pix.scaled(250,220,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->pixview->setFixedSize(250,220);
    ui->pixview->setPixmap(pix);
}

mapout::~mapout()
{
    delete ui;
}

void mapout::on_pushButton_clicked()//地址选择
{
    QString curpath=QCoreApplication::applicationDirPath();
    pathout=QFileDialog::getExistingDirectory(this,"选择一个目录",curpath,QFileDialog::ShowDirsOnly);
    ui->lineEdit->setText(pathout);
}


void mapout::on_pushButton_2_clicked()//导出
{
    QString name=ui->lineEdit_2->text();//获取设置的文件名
    if(pathout==""||name=="")
    {
        QMessageBox::information(this,"注意","请先设置导出路径和文件名称");
        return;
    }
    ofstream file;
    file.open((pathout+"/"+name+".txt").toStdString(),ios::out);//创建新文件
    if(!file)
    {
        qDebug()<<"file"<<pathout+"/"+name+".txt"<<"open faile！";
        return;
    }
    for(auto a:text)
    {
        file<<a<<endl;
    }
    file.close();
    QMessageBox::information(this,"注意","导出成功！");
    this->close();
}
void mapout::readdata()//数据读取
{
    ifstream file(path.toStdString(),ios::in);
    if(!file)
        qDebug()<<"文件"<<path<<"打开失败！";
    string temp;
    getline(file,temp);
    while(!file.fail())
    {
        text.push_back(temp);
        getline(file,temp);
    }
}
