#ifndef FACTORCHOOSE_H
#define FACTORCHOOSE_H

#include <QWidget>

namespace Ui {
class factorChoose;
}

class factorChoose : public QWidget
{
    Q_OBJECT

public:
    explicit factorChoose(QWidget *parent = nullptr);
    ~factorChoose();

private:
    Ui::factorChoose *ui;
};

#endif // FACTORCHOOSE_H
