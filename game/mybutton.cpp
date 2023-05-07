#include "mybutton.h"
#include <QPixmap>
#include <QPropertyAnimation>
myButton::myButton(QString firstimage,QSize s,QString secondimage)
{
    this->f_image=firstimage;
    this->s_image=secondimage;
    QPixmap pix;
    if(!pix.load(f_image))
    {
        qDebug()<<"图片打开失败"<<f_image<<Qt::endl;
        return;
    }
    pix=pix.scaled(s,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(s);
}
void myButton::movedown()
{
    QPropertyAnimation*down=new QPropertyAnimation(this,"geometry");
    down->setDuration(300);
    down->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    down->setEndValue(QRect(this->x(),this->y()+6,this->width(),this->height()));
    down->setEasingCurve(QEasingCurve::OutBounce);
    down->start();
}
void myButton::moveup()
{
    QPropertyAnimation*down=new QPropertyAnimation(this,"geometry");
    down->setDuration(300);
    down->setStartValue(QRect(this->x(),this->y()+6,this->width(),this->height()));
    down->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    down->setEasingCurve(QEasingCurve::OutBounce);
    down->start();
}
