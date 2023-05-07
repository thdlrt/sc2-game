#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//myPushButtons::myPushButtons(QWidget *parent) : QPushButton(parent)
//{

//}

MyPushButtons::MyPushButtons(QString normalImg,QString pressImg)
{
    this->m_pressImg = pressImg;
    this->m_normalImg = normalImg;

    QPixmap pix;
    bool ret = pix.load(m_normalImg);
    if(!ret)
    {
        qDebug() << "图片加载失败";
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

//弹跳特效
void MyPushButtons::zoomBottom()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y() + 20,this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButtons::zoomTop()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y() + 20,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

//
void MyPushButtons::mousePressEvent(QMouseEvent *ev)
{
    if(this->m_pressImg != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->m_pressImg);
        if(!ret)
        {
            qDebug() << "图片加载失败";
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式
        //this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    if(m_flag)
    {
        return;
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(ev);
}

void MyPushButtons::mouseReleaseEvent(QMouseEvent *ev)
{
    if(this->m_pressImg != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->m_normalImg);
        if(!ret)
        {
            qDebug() << "图片加载失败";
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片的样式
        //this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(ev);
}

