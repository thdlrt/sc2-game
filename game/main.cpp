#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<QCoreApplication::applicationDirPath(); //获取程序当前运行目录
    MainWindow w;
    w.show();
    return a.exec();
}
