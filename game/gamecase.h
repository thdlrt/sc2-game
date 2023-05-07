#ifndef GAMECASE_H
#define GAMECASE_H

#include <QDialog>

namespace Ui {
class gameCase;
}

class gameCase : public QDialog
{
    Q_OBJECT

public:
    explicit gameCase(QWidget *parent = nullptr);
    ~gameCase();

private:
    Ui::gameCase *ui;
};

#endif // GAMECASE_H
