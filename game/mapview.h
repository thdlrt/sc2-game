#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QDialog>
#include"gamedata.h"
namespace Ui {
class mapViex;
}

class mapViex : public QDialog
{
    Q_OBJECT

public:
    explicit mapViex(QString path,QWidget *parent = nullptr);
    ~mapViex();

private:
    Ui::mapViex *ui;
    QString path;
};

#endif // MAPVIEW_H
