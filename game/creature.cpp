#include "creature.h"
#include<queue>
#include<set>
struct Node{
    Node(int x,int y,list<pair<int,int>>last=list<pair<int,int>>()):x(x),y(y)
    {
        ans=last;
        ans.push_back(make_pair(x,y));
    }
    int x,y;
    list<pair<int,int>>ans;
};

list<pair<int,int>> creature::searchpath(vector<vector<int>>mapstate,int x,int y)//bfs
{
    vector<vector<int>>move{{1,0},{0,1},{-1,0},{0,-1}};    //找不到可以直接通过的路径，执行attack模式
    queue<Node>q,q2;//q2为辅助，记录attack点,低优先级
    set<pair<int,int>>check;
    q.emplace(x,y);
    check.insert(make_pair(x,y));
    while(!q.empty()||!q2.empty())
    {
        if(!q.empty())
        {
            for(int i=0;i<4;i++)
            {
                int _x=q.front().x+move[i][0],_y=q.front().y+move[i][1];
                if(_x>=0&&_x<15&&_y>=0&&_y<17&&(mapstate[_x][_y]==2||mapstate[_x][_y]==1||mapstate[_x][_y]==9)&&check.find(make_pair(_x,_y))==check.end())
                {
                    if(mapstate[_x][_y]==9)//找到终点
                    {
                        q.front().ans.push_back(make_pair(_x,_y));
                        return q.front().ans;
                    }
                    else if(mapstate[_x][_y]==2)
                    {
                        q2.emplace(_x,_y,q.front().ans);
                        check.insert(make_pair(_x,_y));
                    }
                    else
                    {
                    q.emplace(_x,_y,q.front().ans);
                    check.insert(make_pair(_x,_y));
                    }
                }
            }
            q.pop();
        }
        else
        {
            while(!q2.empty())
            {
                q.push(q2.front());
                q2.pop();
            }
        }
    }
    //return list<pair<int,int>>();
}
void creature::move(int x,int y)
{
   real_x=x;
   real_y=y;
   this->x=real_x/48;
   this->y=real_y/48;
}
