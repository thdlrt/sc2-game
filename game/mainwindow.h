#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"mybutton.h"
#include <QMainWindow>
#include"mypushbutton.h"
#include"modechoose.h"
#include"mainedit.h"
#include"gamedata.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startBtn_clicked();
    void editBtn_clicked();
    void exitBtn_clicked();
private:
    Ui::MainWindow *ui;
    myButton* startBtn,*editBtn,*exitBtn;
};
#endif // MAINWINDOW_H
