#ifndef CREATURE_H
#define CREATURE_H
#include"defeat.h"
#include"gamedata.h"
class creature:public defeat
{
public:
    creature(vector<vector<int>>mapstate,int speed,int x,int y,int hp,int att,int range,set<int>state):stop(0),speed(speed),defeat(x,y,hp,att,range)
    {        this->real_x=48*x;
             this->state=state;
             this->real_y=48*y;
             path=searchpath(mapstate,x,y);
             if(state.find(1)!=state.end())//闪现冷却恢复
             {
                 time=new QTimer;
                 time->start(10000);
                 connect(time,&QTimer::timeout,this,[&](){canfly=1;});
                 canfly=1;
             }
             if(state.find(2)!=state.end())//厚血
             {
                this->hp*=2;
             }
             if(state.find(3)!=state.end())//神速
             {
                this->speed*=2;
             }
             if(state.find(4)!=state.end())//免疫
             {
                dontdif=1;
             }
    }
    list<pair<int,int>>searchpath(vector<vector<int>>mapstate,int x,int y);//传入play,xy为起始点
    list<pair<int,int>>path;//移动路径
    void move(int x,int y);
    int getspeed(){return speed;}
    int getreal_x(){return real_x;}
    int getreal_y(){return real_y;}
    bool stop;//被阻挡，静止状态
    //set state;//1可以闪现,2暴走，3厚血
    int frozen_time=0;//特殊状态时间
    int fire_time=0;
    int speed;//移动速度,每次移动像素
    bool canfly=0;//闪现
    bool dontdif=0;//异常免疫
    QTimer*time;
protected:
    int real_x,real_y;//像素坐标
};
#endif // CREATURE_H
