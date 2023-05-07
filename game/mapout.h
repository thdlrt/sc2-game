#ifndef MAPOUT_H
#define MAPOUT_H

#include <QDialog>
#include"gamedata.h"
namespace Ui {
class mapout;
}

class mapout : public QDialog
{
    Q_OBJECT

public:
    explicit mapout(QString s,QWidget *parent = nullptr);
    ~mapout();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mapout *ui;
    QString path,pathout;
    vector<string>text;
    void readdata();
};

#endif // MAPOUT_H
