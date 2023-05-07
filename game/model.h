#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include"gamedata.h"
#include"mybutton.h"
namespace Ui {
class model;
}

class model : public QWidget
{
    Q_OBJECT

public:
    explicit model(QString picture,QString distribe,QWidget *parent = nullptr);
    myButton*Btn;
    ~model();
private slots:

private:
    Ui::model *ui;
};

#endif // MODEL_H
