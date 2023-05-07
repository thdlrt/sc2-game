#ifndef GAMESTART_H
#define GAMESTART_H
#include"gamedata.h"
#include <QDialog>
#include"creature.h"
#include"mybutton.h"
#include"model.h"
namespace Ui {
class gameStart;
}
struct attackmovie//弹幕
{
    pair<double,double>begin,end,place;
    double time=10;
    int type;//0近程 1远程
    double speedx,speedy;
};

struct game_datas
{
    QString picture;
    QString name;
    vector<vector<int>>map,play;//map中2为起点3为终点1为道路
    //play中-1不可放置，0为远程，1为近战，2（狂热者）,3(幽灵),4,5为占用，9为终点
    vector<defeat*>defeater;
    //防御信息
    list<creature*>enemy;
    vector<attackmovie> attack;//攻击，用于动画
    list<pair<int,int>>wait_enemy;

};
class gameStart : public QDialog
{
    Q_OBJECT

public:
    explicit gameStart(QString path,QWidget *parent = nullptr);
    ~gameStart();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void m1Btn_clicked();
    void m2Btn_clicked();
    void m3Btn_clicked();
    void m4Btn_clicked();
    void up();//数据&画面
    void up2();//出兵&攻击
    void upresouce2();//瓦斯
    void defeatdead(int x,int y,int range);//刷新地图和路径
private:
    bool nuclear=1;//送一枚核弹
    Ui::gameStart *ui;
    QString path;
    game_datas game_data;
    void readGame();
    bool show_near,show_far;
    int health;
    int resource1,resource2;
    void upcase();
    int b_x,b_y;//出兵点
    model*m1,*m2,*m3,*m4;
    int choose;//选择兵种2345
    pair<int,int>searchplace(int x,int y);//找所在格子
    QTimer*timer_up,*timer_up2,*timer_up3;
    int resouce2_factor=0;
    QTime t0;
    QPixmap pix_p,pix_map,
            pix_d_1,pix_d_2,
            pix_e_1,pix_e_2,
            pix_m_1,pix_m_2,
            pix_d_3,pix_m_3,
            pix_e_3,pix_m_4,
            pix_c_2, pix_c_3,
            pix_c_4,
            pix_f_1,
            pix_f_2,
            pix_f_3,
            pix_f_4,
            pix_f_5;
    QMediaPlayer*bgm,* soundeffect_scv_ready,*soundeffect_scv_help,*soundeffect_ghost_ready,*soundeffect_ghost_help,*soundeffect_build_complete
,*soundeffect_under_attack,*soundeffect_nuclear;
signals:

};
#endif // GAMESTART_H
