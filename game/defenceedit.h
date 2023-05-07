#ifndef DEFENCEEDIT_H
#define DEFENCEEDIT_H
#include"gamedata.h"
#include"defeat.h"
#include <QDialog>

namespace Ui {
class defenceEdit;
}

class defenceEdit : public QDialog//血量等信息显示，升级前缀，删除回收
{
    Q_OBJECT

public:
    explicit defenceEdit(int resouce2,defeat*d,QWidget *parent = nullptr);
    ~defenceEdit();
private slots:
    void upcase();
    void on_pushButton_delete_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_delete_1_clicked();

    void on_delete_2_clicked();

    void on_delete_3_clicked();

    void on_delete_4_clicked();

    void on_delete_5_clicked();

public slots:
    void close();
private:
    int resouce2;
    QTimer*time_out;
    defeat*d;
    Ui::defenceEdit *ui;
    bool isclose=0;
    QPixmap pix,pix2,pix3,pix4,pix5,pix6,pix7;
signals:
    void spendresouce2(int n);//花费
    void addresouce1(int n);//回收
};

#endif // DEFENCEEDIT_H
