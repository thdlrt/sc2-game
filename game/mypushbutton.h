#ifndef MYPUSHBUTTONS_H
#define MYPUSHBUTTONS_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QMouseEvent>

class MyPushButtons : public QPushButton
{
    Q_OBJECT
public:
//    explicit myPushButtons(QWidget *parent = nullptr);

    MyPushButtons(QString normalImg,QString pressImg = "" );

    //弹跳特效
    void zoomBottom();
    void zoomTop();

    QString m_normalImg;//正常显示的图片
    QString m_pressImg;//按下显示的图片
    bool m_flag = false; //是否禁用按钮

    void mouseReleaseEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
signals:

public slots:
};

#endif // MYPUSHBUTTONS_H
