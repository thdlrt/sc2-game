#ifndef DEFEAT_H
#define DEFEAT_H
#include"gamedata.h"
#include<QObject>
class defeat:public QObject
{
        Q_OBJECT
public:
    defeat(int x,int y,int hp,int att,int range):x(x),y(y),hp(hp),att(att),range(range),QObject(nullptr),hp_max(hp){}
    defeat(int x,int y,int hp,int att,int range,int price):x(x),y(y),hp(hp),att(att),range(range),price(price),QObject(nullptr),hp_max(hp){}
    bool islive(){return hp>0;}
    bool inRange(defeat*d);
    bool attack(defeat*d);
    bool hurt(defeat*d);
    //数据获取
    int getx(){return x;}
    int gety(){return y;}
    int getatt(){return att;}
    int gethp(){return hp;}
    int getprice(){return price;}
    int getrange(){return range;}
    int getreal_x(){return x*48;}
    int getreal_y(){return y*48;}
    int gethp_max(){return hp_max;}
    void setstate(int n);
    ~defeat();
    set<int> state;//词缀
    int hp;
protected:
    int x,y;
    int hp_max;//生命
    int att;//攻击
    int range;//攻击范围
private:
    int price;
signals:
    void dead(int x,int y,int range);//死亡信号
    void closeedit();
};

#endif // DEFEAT_H
