#ifndef MAPIN_H
#define MAPIN_H

#include <QDialog>
#include"gamedata.h"
#include"mybutton.h"
namespace Ui {
class mapin;
}

class mapin : public QDialog
{
    Q_OBJECT

public:
    explicit mapin(QWidget *parent = nullptr);
    ~mapin();
private slots:
    void uploadBtn_clicked();
    void on_pushButton_clicked();

private:
    Ui::mapin *ui;
    QString filein,mapname,difficult,owner;
    myButton* uploadBtn;
    vector<mapList>map_data;
    void writedata();
};

#endif // MAPIN_H
