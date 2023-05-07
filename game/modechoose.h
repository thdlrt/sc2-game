#ifndef MODECHOOSE_H
#define MODECHOOSE_H

#include <QDialog>
#include"gamedata.h"
namespace Ui {
class modeChoose;
}

class modeChoose : public QDialog
{
    Q_OBJECT

public:
    explicit modeChoose(QWidget *parent = nullptr);
    ~modeChoose();
    void upcase();
    static vector<mapList> readMapList();
private slots:
        void report();
        void report2();
        void slotCellEnter(int r, int c);
        void on_pushButton_clicked();

private:
    Ui::modeChoose *ui;
    vector<mapList>map_data;
};

#endif // MODECHOOSE_H
