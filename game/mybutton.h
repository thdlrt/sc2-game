#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QWidget>
#include <QPushButton>
#include <QString>
class myButton:public QPushButton
{
public:
    myButton(QString firstimage,QSize s,QString secondimage="");
    void movedown();
    void moveup();
private:
    QString f_image,s_image;

};

#endif // MYBUTTON_H
