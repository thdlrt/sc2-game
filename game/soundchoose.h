#ifndef SOUNDCHOOSE_H
#define SOUNDCHOOSE_H

#include <QWidget>

namespace Ui {
class soundchoose;
}

class soundchoose : public QWidget
{
    Q_OBJECT

public:
    explicit soundchoose(QWidget *parent = nullptr);
    ~soundchoose();
    int getnum(){return num;}
    void setnum(int val);
private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_clicked();

private:
    Ui::soundchoose *ui;
    bool state=0;
    int num=99;
};

#endif // SOUNDCHOOSE_H
