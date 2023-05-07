#ifndef MAINEDIT_H
#define MAINEDIT_H

#include <QDialog>
#include"gamedata.h"
namespace Ui {
class mainEdit;
}

class mainEdit : public QDialog
{
    Q_OBJECT

public:
    explicit mainEdit(QWidget *parent = nullptr);
    ~mainEdit();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::mainEdit *ui;
};

#endif // MAINEDIT_H
