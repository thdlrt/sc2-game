#include "gamestart.h"
#include "ui_gamestart.h"
#include"defenceedit.h"
vector<vector<int>>enemyinformation{{2,220,5,1},{3,140,10,2},{4,100,8,1}};//敌人信息 int speed,int hp,int att,int range
//1雷兽234todo
gameStart::gameStart(QString path,QWidget *parent) :path(path),
    QDialog(parent),
    ui(new Ui::gameStart)
{
    t0=QTime::currentTime();
    //窗口关闭后自动释放
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    //文件读取
    readGame();
    //画面刷新
    timer_up=new QTimer(this);
    timer_up2=new QTimer(this);
    timer_up3=new QTimer(this);
    timer_up->start(50);
    timer_up2->start(1000);
    timer_up3->start(15000);
    connect(timer_up,SIGNAL(timeout()),this,SLOT(up()));
    //connect(timer_up,&QTimer::timeout,this,[=](){update();});
    //connect(timer_up,&QTimer::timeout,this,[=](){QTime t=QTime::currentTime();qDebug()<<"timeout"<<t0.msecsTo(t);});
    connect(timer_up2,SIGNAL(timeout()),this,SLOT(up2()));
    connect(timer_up3,SIGNAL(timeout()),this,SLOT(upresouce2()));
    //数据初始化
    resource1=100;
    resource2=0;
    health=5;
    choose=0;
    //界面初始化
    this->setFixedSize(1280,720);
    this->setWindowTitle("StartCraft Defence");
    ui->label->setFixedSize(464,720);
    QPixmap pix(":/game/resource/gamemenu.png");//右侧菜单图片
    pix=pix.scaled(464,720,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label->setPixmap(pix);
    upcase();
    //金币血量
    ui->label_money_p->setFixedSize(30,30);
    QPixmap pix2(":/game/resource/resource1.png");
    pix2=pix2.scaled(20,20,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label_money_p->setPixmap(pix2);
    ui->label_health_p->setFixedSize(20,20);
    QPixmap pix3(":/game/resource/heart.png");
    pix3=pix3.scaled(20,20,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label_health_p->setPixmap(pix3);
    QPixmap pix4(":/game/resource/resource2.png");
    pix4=pix4.scaled(20,20,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label_resource2_p->setPixmap(pix4);
    QPalette label_palette;
    label_palette.setColor(QPalette::WindowText,QColor(0,0,0));
    ui->backcolor->setFixedSize(170,82);
    ui->backcolor->setAutoFillBackground(true);
    ui->backcolor->setPalette(label_palette);
    //右侧选择栏
    m1=new model(":/game/resource/kuangrzview.png","名称：scv\n种类：近战\n攻击10\n攻击范围1\n生命值150\n晶体矿：30");
    m1->setParent(this);
    m1->move(822,10);
    connect(m1->Btn,SIGNAL(clicked()),this,SLOT(m1Btn_clicked()));
    m2=new model(":/game/resource/soullast.png","名称：幽灵\n种类：远程\n攻击20\n攻击范围3\n生命值50\n晶体矿：35");
    m2->setParent(this);
    m2->move(822,160);
    connect(m2->Btn,SIGNAL(clicked()),this,SLOT(m2Btn_clicked()));
    m3=new model(":/game/resource/resouce2view.png","名称：瓦斯矿井\n种类：建筑\n每15s生产一瓦斯气泉\n生命值220\n晶体矿：50\n不可回收&升级");
    m3->setParent(this);
    m3->move(822,310);
    connect(m3->Btn,SIGNAL(clicked()),this,SLOT(m3Btn_clicked()));
    m4=new model(":/game/resource/nuclear.png","核弹打击\n对全屏敌人造成致命伤害,并造成持续烧伤\n每局游戏有一次免费使用机会\n高能瓦斯：10");
    m4->setParent(this);
    m4->move(822,460);
    connect(m4->Btn,SIGNAL(clicked()),this,SLOT(m4Btn_clicked()));
    show_far=0;
    show_near=0;
    //加载画家图片
    pix_p.load(":/game/resource/center.png");
    pix_d_1.load(":/game/resource/kuangrz.png");
    pix_d_2.load(":/game/resource/soul.png");
    pix_e_1.load(":/game/resource/leishou.png");
    pix_e_2.load(":/game/resource/zhanglang.png");
    pix_m_1.load(":/game/resource/soulattack.png");
    pix_m_2.load(":/game/resource/nomalattack.png");
    pix_d_3.load(":/game/resource/resouce2.png");
    pix_m_3.load(":/game/resource/frozon.png");
    pix_e_3.load(":/game/resource/fly.png");
    pix_m_4.load(":/game/resource/fire.png");
    pix_c_2.load(":/game/resource/hhp.png");
    pix_c_3.load(":/game/resource/fs.png");
    pix_c_4.load(":/game/resource/sp.png");
    pix_f_1.load(":/game/resource/addatt.png");
    pix_f_2.load(":/game/resource/frozen.png");
    pix_f_3.load(":/game/resource/range.png");
    pix_f_4.load(":/game/resource/hp.png");
    pix_f_5.load(":/game/resource/fireup.png");
    pix_map.load(game_data.picture);
    //地图图片
    pix_map=pix_map.scaled(816,720,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //显示可放置位置
    pix_p=pix_p.scaled(40,40);
    //defence
    pix_d_1=pix_d_1.scaled(48,48,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_d_2=pix_d_2.scaled(64,64,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_d_3=pix_d_3.scaled(50,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //enemy
    pix_e_1=pix_e_1.scaled(48,48,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_e_2=pix_e_2.scaled(48,48,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_e_3=pix_e_3.scaled(48,48,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //movie
    pix_m_1=pix_m_1.scaled(24,24,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_m_2=pix_m_2.scaled(24,24,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_m_3=pix_m_3.scaled(32,32,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_m_4=pix_m_4.scaled(32,32,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //前缀
    pix_c_2=pix_c_2.scaled(16,16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_c_3=pix_c_3.scaled(16,16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_c_4=pix_c_4.scaled(16,16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_f_1=pix_f_1.scaled(16,16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_f_2=pix_f_2.scaled(16,16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_f_3=pix_f_3.scaled(16,16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_f_4=pix_f_4.scaled(16,16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    pix_f_5=pix_f_5.scaled(16,16,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //bgm
    //QMessageBox::information(this,"GG","test2！");
    //qDebug()<<QString::number(pow(10,bgmvalue/100.0)/10-0.1);
    bgm=new QMediaPlayer(this);
    //QMessageBox::information(this,"GG","test3！");
    QAudioOutput*au1=new QAudioOutput;
    bgm->setAudioOutput(au1);
    au1->setVolume(pow(10,bgmvalue/100.0)/10-0.1);
    bgm->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/bgm.mp3"));
    bgm->play();
    bgm->setLoops(99);
    //soundeffect
    QAudioOutput*au2=new QAudioOutput;
    au2->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    soundeffect_scv_ready=new QMediaPlayer(this);
    soundeffect_scv_ready->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/SCV_Ready.mp3"));
    soundeffect_scv_ready->setAudioOutput(au2);

    QAudioOutput*au3=new QAudioOutput;
    au3->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    soundeffect_scv_help=new QMediaPlayer(this);
    soundeffect_scv_help->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/SCV_Help.mp3"));
    soundeffect_scv_help->setAudioOutput(au3);

    QAudioOutput*au4=new QAudioOutput;
    au4->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    soundeffect_ghost_ready=new QMediaPlayer(this);
    soundeffect_ghost_ready->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/Ghost_Ready.mp3"));
    soundeffect_ghost_ready->setAudioOutput(au4);

    QAudioOutput*au5=new QAudioOutput;
    au5->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    soundeffect_ghost_help=new QMediaPlayer(this);
    soundeffect_ghost_help->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/Ghost_Death.mp3"));
    soundeffect_ghost_help->setAudioOutput(au5);

    QAudioOutput*au6=new QAudioOutput;
    au6->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    soundeffect_build_complete=new QMediaPlayer(this);
    soundeffect_build_complete->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/Alert_TerranAddOnComplete.mp3"));
    soundeffect_build_complete->setAudioOutput(au6);

    QAudioOutput*au7=new QAudioOutput;
    au7->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    sound_effect_resource1=new QMediaPlayer(this);
    sound_effect_resource1->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/Alert_TerranNeedMoreMinerals.mp3"));
    sound_effect_resource1->setAudioOutput(au7);

    QAudioOutput*au8=new QAudioOutput;
    au8->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    sound_effect_resource2=new QMediaPlayer(this);
    sound_effect_resource2->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/Alert_TerranNeedMoreGas.mp3"));
    sound_effect_resource2->setAudioOutput(au8);

    QAudioOutput*au9=new QAudioOutput;
    au9->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    sound_effect_research=new QMediaPlayer(this);
    sound_effect_research->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/Alert_TerranResearchComplete.mp3"));
    sound_effect_research->setAudioOutput(au9);

    QAudioOutput*au10=new QAudioOutput;
    au10->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    soundeffect_under_attack=new QMediaPlayer(this);
    soundeffect_under_attack->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/UnderAttack.mp3"));
    soundeffect_under_attack->setAudioOutput(au10);

    QAudioOutput*au11=new QAudioOutput;
    au11->setVolume(pow(10,gamevalue/100.0)/10-0.1);
    soundeffect_nuclear=new QMediaPlayer(this);
    soundeffect_nuclear->setSource(QUrl::fromLocalFile("qrc:/music/resource/music/Ghost_NuclearStrike.mp3"));
    soundeffect_nuclear->setAudioOutput(au11);
    //test
    //resource1=100;
    //resource2=5;
    //show_far=1;
    //show_near=1;
    //creature* c=new creature(game_data.play,4,b_x,b_y,1,1,1);
    //game_data.enemy.push_back(c);
    //(vector<vector<int>>mapstate,int speed,int x,int y,int hp,int att,int range,int state=0)
}
void gameStart::readGame()
{
    ifstream file(path.toStdString());
    if(!file)
    {
        qDebug()<<"文件打开失败"<<path;
        return;
    }
    game_data.map=vector<vector<int>>(15,vector<int>(17,0));
    game_data.play=vector<vector<int>>(15,vector<int>(17,-1));
    string s,t_name,t_picture;
    for(int i=0;i<15;i++)//读取地图
    {
        getline(file,s);
        for(int j=0;j<17;j++)
            game_data.map[i][j]=s[j]-'0';
    }
    file>>t_name>>t_picture;
    game_data.name=QString::fromStdString(t_name);
    game_data.picture=QString::fromStdString(t_picture);
    //敌人数据
    int type,time;//类型，时间
    while(file>>type>>time)
    {
        game_data.wait_enemy.push_back(make_pair(type,time));
    }
    file.close();
    //搜索可放置点
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<17;j++)
        {
            if(game_data.map[i][j]==0&&((i<14&&j>0&&game_data.map[i+1][j-1]==1)||(i>0&&j<16&&game_data.map[i-1][j+1]==1)||(i<14&&j<16&&game_data.map[i+1][j+1]==1)||(i>0&&game_data.map[i-1][j]==1)||(j>0&&game_data.map[i][j-1]==1)||(i<14&&game_data.map[i+1][j]==1)||(j<16&&game_data.map[i][j+1]==1)||(i>0&&j>0&&game_data.map[i-1][j-1]==1)))
                game_data.play[i][j]=0;//可放置远程
            else if(game_data.map[i][j]==1)
                game_data.play[i][j]=1;//可放置近程
            else if(game_data.map[i][j]==3)
                game_data.play[i][j]=9;
            else if(game_data.map[i][j]==2)//设置出兵点
            {
                b_x=i;
                b_y=j;
            }
        }
    }
}
void gameStart::paintEvent(QPaintEvent *event)//绘图
{
    //QTime t1=QTime::currentTime();
    QPainter painter(this);

    //QTime t2=QTime::currentTime();
    //qDebug()<<"all"<<t0.msecsTo(t1)<<"ms";
    //qDebug()<<"update"<<t1.msecsTo(t2)<<"ms";
     painter.drawPixmap(0,0,pix_map);//绘制地图
    if(show_far||show_near)
    {
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<17;j++)
            {
                if(game_data.play[i][j]==0&&show_far)
                     painter.drawPixmap(48*j+4,48*i+4,pix_p);
                if(game_data.play[i][j]==1&&show_near)
                     painter.drawPixmap(48*j+4,48*i+4,pix_p);
            }
        }
    }
    //defence绘制
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<17;j++)
        {
            if(game_data.play[i][j]==2)
            {
                painter.drawPixmap(48*j+4,48*i+4,pix_d_1);
            }
            else if(game_data.play[i][j]==3)
            {
                painter.drawPixmap(48*j+4,48*i-12,pix_d_2);
            }
            else if(game_data.play[i][j]==4)
            {
                painter.drawPixmap(48*j+4,48*i-12,pix_d_3);
            }
//            else if(game_data.play[i][j]==5)
//                 ;
            //前缀
            for(auto a:game_data.defeater)
            {
                if(a->getx()==i&&a->gety()==j)
                {
                    list<int>temp;
                    int place=0;
                    for(auto b:a->state)
                        temp.push_back(b);
                    while(!temp.empty())
                    {
                        switch(temp.front())
                        {
                        case 1:
                            painter.drawPixmap(48*j+place,48*i,pix_f_1);
                            break;
                        case 2:
                            painter.drawPixmap(48*j+place,48*i,pix_f_2);
                            break;
                        case 3:
                            painter.drawPixmap(48*j+place,48*i,pix_f_3);
                            break;
                        case 4:
                            painter.drawPixmap(48*j+place,48*i,pix_f_4);
                            break;
                        case 5:
                            painter.drawPixmap(48*j+place,48*i,pix_f_5);
                            break;
                        }
                        temp.pop_front();
                        place+=16;
                    }
                }
            }
        }
    }
    //enemy绘制
    for(auto a:game_data.enemy)
    {//对不同敌人绘制不同
        //todo
        int x=a->getreal_x(),y=a->getreal_y();
        //qDebug()<<QString::number(x)<<" "<<QString::number(y);
        switch(a->getatt())
        {
        case 5:
            painter.drawPixmap(y,x,pix_e_1);
            break;
        case 10:
            painter.drawPixmap(y,x,pix_e_2);
            break;
        case 8:
            painter.drawPixmap(y,x,pix_e_3);
            //todo
        default:
            break;
        }
        //前缀特效
        //冰冻
        if(a->frozen_time>0)
        {
            //qDebug()<<"???";
            painter.drawPixmap(y+12,x,pix_m_3);
            a->frozen_time--;
            if(a->frozen_time==0)//恢复速度
                a->speed*=2;
        }
        //燃烧
        if(a->fire_time>0)
        {
            //qDebug()<<"fire";
            painter.drawPixmap(y+6,x,pix_m_4);
            a->fire_time--;
            a->hp--;
        }
        //前缀
        if(a->state.find(2)!=a->state.end())
        {
            painter.drawPixmap(y,x,pix_c_2);
        }
        if(a->state.find(3)!=a->state.end())
        {
            painter.drawPixmap(y+16,x,pix_c_3);
        }
        if(a->state.find(4)!=a->state.end())
        {
            painter.drawPixmap(y+32,x,pix_c_4);
        }
    }
    //攻击绘制
    for(int i=0;i<game_data.attack.size();i++)
    {
        if(game_data.attack[i].type==1)//素材选择
        {
            painter.drawPixmap(game_data.attack[i].place.second,game_data.attack[i].place.first,pix_m_1);
        }
        else
        {
            painter.drawPixmap(game_data.attack[i].place.second,game_data.attack[i].place.first,pix_m_2);
        }
        game_data.attack[i].place.first+=game_data.attack[i].speedx;//移动
        game_data.attack[i].place.second+=game_data.attack[i].speedy;
        //qDebug()<<QString::number(game_data.attack[i].place.first-game_data.attack[i].end.first);
        if(abs(game_data.attack[i].place.first-game_data.attack[i].end.first)<=5||abs(game_data.attack[i].place.second-game_data.attack[i].end.second)<=5)
        {
            game_data.attack.erase(game_data.attack.begin()+i);
        }
    }
//    QTime t2=QTime::currentTime();
//    qDebug()<<"all"<<t0.msecsTo(t1)<<"ms";
//    qDebug()<<"update"<<t1.msecsTo(t2)<<"ms";
}
void gameStart::upcase()//数据更新
{
    //QTime t1=QTime::currentTime();
    //生命值金钱
    ui->label_health->setText(QString::number(health));
    ui->label_money->setText(QString::number(resource1));
    ui->label_resource2->setText(QString::number(resource2));
    ui->progressBar->setValue(health*20);
    //游戏失败
    if(health<=0)
    {
        timer_up->stop();
        timer_up2->stop();
        timer_up3->stop();
        QMessageBox::information(this,"GG","很遗憾，你输了！");
        this->close();
    }
    //游戏胜利
    if(game_data.enemy.empty()&&game_data.wait_enemy.empty()&&health>0)
    {
        timer_up->stop();
        timer_up2->stop();
        timer_up3->stop();
        QMessageBox::information(this,"GG","恭喜，你胜利了！");
        this->close();
    }
    //防御塔死亡
    for(int i=0;i<game_data.defeater.size();i++)
    {
        if(!game_data.defeater[i]->islive())
        {
            delete game_data.defeater[i];
        }
    }
    //敌人移动

    for(auto i=game_data.enemy.begin();i!=game_data.enemy.end();)//遍历敌人
    {
        if(game_data.play[(*i)->path.front().first][(*i)->path.front().second]==9)
        {
            //qDebug()<<"a";
            health-=max(1,(*i)->getatt()/5);
            game_data.enemy.erase(i++);
            //敌人走到了尽头
            soundeffect_under_attack->play();
            continue;
        }
        else if(!(*i)->islive())
        {

            resource1+=3;
            //敌人死了
            //含词缀的敌人掉落特殊资源(有概率)
            if((*i)->state.size()>0||(*i)->getatt()==8)
            {
                QTime randTime=QTime::currentTime();
                srand(randTime.msec()+randTime.second()*1000);
                int n=rand()%100;
                if(n%3==0)
                resource2++;
            }
            game_data.enemy.erase(i++);
            continue;
        }
        //qDebug()<<"A";
        int speed=(*i)->getspeed();
        auto p1=(*i)->path.begin();//确定前进方向
        auto p2=p1;
        ++p2;
        if((*p2).second>(*p1).second)//右
        {
           (*i)->move((*i)->getreal_x(),(*i)->getreal_y()+speed);
        }
        else if((*p2).second<(*p1).second)//左
        {
            (*i)->move((*i)->getreal_x(),(*i)->getreal_y()-speed);
        }
        else if((*p2).first>(*p1).first)//下
        {
            (*i)->move((*i)->getreal_x()+speed,(*i)->getreal_y());
        }
        else if((*p2).first<(*p1).first)//上
        {
            (*i)->move((*i)->getreal_x()-speed,(*i)->getreal_y());
        }
        //是否走到
        if(abs((*i)->getreal_x()-(*p2).first*48)<=(*i)->speed/2&&abs((*i)->getreal_y()-(*p2).second*48)<=(*i)->speed/2)//防止减速后不是48倍数，进行纠正
        {
            (*i)->getreal_x()==(*p2).first*48;
            (*i)->getreal_y()==(*p2).second*48;
           // qDebug()<<QString::number((*i)->getx())<<" "<<QString::number((*i)->gety());
            //遇到敌人停？
            p2++;
            p1++;
            if(p2==(*i)->path.end())
            {
                (*i)->path.pop_front();
                continue;
            }
            if(game_data.play[(*p2).first][(*p2).second]==1||game_data.play[(*p2).first][(*p2).second]==9||((*i)->canfly&&game_data.play[(*p2).first][(*p2).second]==2))//近战塔被摧毁了//闪现
            {
                if(game_data.play[(*p2).first][(*p2).second]==2)
                (*i)->canfly=false;//使技能
                (*i)->stop=0;//恢复行动//唯一解除静止的可能
                (*i)->path.pop_front();
            }
            else
            {
                //qDebug()<<QString::number(game_data.play[(*p2).first][(*p2).second])<<" "<<(*p2).first<<" "<<(*p2).second;
                (*i)->path.pop_front();
                pair<int,int>stop=make_pair((*p1).first,(*p1).second);
                (*i)->path.push_front(stop);
                (*i)->stop=1;
            }
        }
        i++;
    }
    //QTime t2=QTime::currentTime();
    //qDebug()<<"all"<<t0.msecsTo(t2)<<"ms"<<Qt::endl;
    //qDebug()<<"upcase"<<t1.msecsTo(t2)<<"ms"<<Qt::endl;
}
void gameStart::up()//刷新
{
    //QTime t1=QTime::currentTime();
    update();
    //QTime t2=QTime::currentTime();
    //qDebug()<<"all"<<t0.msecsTo(t1)<<"ms";
    //qDebug()<<"update"<<t1.msecsTo(t2)<<"ms";
    upcase();
    //QTime t3=QTime::currentTime();
    //qDebug()<<"upcase"<<t2.msecsTo(t3)<<"ms"<<Qt::endl;
}
void gameStart::m1Btn_clicked()//狂热者
{
    m1->Btn->movedown();
    m1->Btn->moveup();
    Delay(300);
    show_near=1;
    show_far=0;
    choose=2;
}
void gameStart::m2Btn_clicked()//幽灵
{
    m2->Btn->movedown();
    m2->Btn->moveup();
    Delay(300);
    show_far=1;
    show_near=0;
    choose=3;
}
void gameStart::m3Btn_clicked()//瓦斯
{
    m3->Btn->movedown();
    m3->Btn->moveup();
    Delay(300);
    show_far=1;
    show_near=0;
    choose=4;
}
void gameStart::m4Btn_clicked()//核弹
{
    m4->Btn->movedown();
    m4->Btn->moveup();
    Delay(300);
    if(nuclear||resource2>=10)
    {
        if(nuclear)//使用赠送的
            nuclear=false;
        else
            resource2-=10;
        for(auto a:game_data.enemy)
        {
            a->hp-=60;
            a->fire_time=999;
        }
        soundeffect_nuclear->play();
    }
    else
    {
        sound_effect_resource2->play();
    }
}
void gameStart::mousePressEvent(QMouseEvent *event)
{
    int x=event->x(),y=event->y();
    pair<int,int>p=searchplace(y,x);
    if(event->button()==Qt::LeftButton&&choose)
    {
    //qDebug()<<QString::number(p.first)<<" "<<QString::number(p.second);
    if(p.first<15&&p.second<17)
    {
        //余额检查
        if(choose==2)
        {
            if(resource1<30)
            {
                sound_effect_resource1->play();
                show_near=0;
                return;
            }
        }
        else if(choose==3)
        {
            if(resource1<35)
            {
                sound_effect_resource1->play();
                show_far=0;
                return;
            }
        }
        else if(choose==4)
        {
            if(resource1<50)
            {
                sound_effect_resource1->play();
                show_far=0;
                return;
            }
        }
        if(show_near&&game_data.play[p.first][p.second]==1)
        {
           //路经检查，是否会堵住
            game_data.play[p.first][p.second]=choose;
           for(auto a:game_data.enemy)
           {
               if(a->stop)
                   continue;
               auto i=a->path.begin();
               pair<int,int>temp=make_pair(i->first,i->second);//保存第一个点
               ++i;//从下一个点开始搜索，放置中途环路出bug
               a->path=a->searchpath(game_data.play,i->first,i->second);
               a->path.push_front(temp);//加回第一个
           }
           if(choose==2)//scv
           {
               //音频
               soundeffect_scv_ready->play();

               defeat* t=new defeat(p.first,p.second,150,10,1,30);
               game_data.defeater.push_back(t);
               resource1-=t->getprice();
               connect(t,SIGNAL(dead(int,int,int)),this,SLOT(defeatdead(int,int,int)));
           }
        }
        else if(show_far&&game_data.play[p.first][p.second]==0)//其它单位加入
        {
           game_data.play[p.first][p.second]=choose;
           if(choose==3)//幽灵
           {
               //音频
               soundeffect_ghost_ready->play();

               defeat* t=new defeat(p.first,p.second,50,20,3,35);
               game_data.defeater.push_back(t);
               resource1-=t->getprice();
               connect(t,SIGNAL(dead(int,int,int)),this,SLOT(defeatdead(int,int,int)));
           }
           else if(choose==4)//瓦斯
           {
               //音频
               soundeffect_build_complete->play();

               resouce2_factor++;
               defeat* t=new defeat(p.first,p.second,220,0,-1,50);
               game_data.defeater.push_back(t);
               resource1-=t->getprice();
               connect(t,SIGNAL(dead(int,int,int)),this,SLOT(defeatdead(int,int,int)));
           }
           //todo
        }
    }
    choose=0;
    show_near=0;
    show_far=0;
    }
    else if(event->button()==Qt::LeftButton)//选中单位进行操作升级前缀/删除todo
    {
        if(p.first<15&&p.second<17&&(game_data.play[p.first][p.second]==2||game_data.play[p.first][p.second]==3||game_data.play[p.first][p.second]==4||game_data.play[p.first][p.second]==5))
        {
            defeat*target;
            for(auto a:game_data.defeater)
            {
                if(p.first==a->getx()&&p.second==a->gety())
                    target=a;
            }
            if(target->getatt()==0)
                return;
            defenceEdit*d=new defenceEdit(resource2,target);
            connect(target,SIGNAL(closeedit()),d,SLOT(close()));
            connect(d,&defenceEdit::addresouce1,this,[&](int n){resource1+=n;});
            connect(d,&defenceEdit::spendresouce2,this,[&](int n){resource2-=n;});
            d->exec();
        }
    }
}
pair<int,int>gameStart::searchplace(int x,int y)
{
    return make_pair(x/48,y/48);
}
void gameStart::up2()
{
    //QTime t1=QTime::currentTime();
    //资源
    resource1+=2;
    //(vector<vector<int>>mapstate,int speed,int x,int y,int hp,int att,int range,int state=0)
    //随机前缀 1为内置飞龙闪现，2厚血 3神速 4 免疫,随机数生成
    QTime randTime;
    for(auto i=game_data.wait_enemy.begin();i!=game_data.wait_enemy.end();)//出兵
    {
        i->second--;
        if(i->second<=0)
        {
            //随机数
            randTime=QTime::currentTime();
            srand(randTime.msec()+randTime.second()*1000);
            int n=rand()%100;
            //特性set设置
            set<int>temp;
            if(i->first==3)//特殊，飞龙
                temp.insert(1);
            if(n%7==0&&temp.size()<=2)//厚血
            {
                temp.insert(2);
            }
            if(n%8==0&&temp.size()<=2)//免疫
            {
                temp.insert(4);
            }
            if(n%10==0&&temp.size()<=2)//神速
            {
                temp.insert(3);
            }
            creature*c=new creature(game_data.play,enemyinformation[i->first-1][0],b_x,b_y,enemyinformation[i->first-1][1],enemyinformation[i->first-1][2],enemyinformation[i->first-1][3],temp);//敌人信息 int speed,int hp,int att,int range
            game_data.enemy.push_back(c);
            game_data.wait_enemy.erase(i++);
        }
        else
            i++;
    }
    //攻击
    for(auto a:game_data.defeater)
    {
        int attacktime=0;//范围攻击攻击次数限制3
        for(auto b:game_data.enemy)
        {
            if(a->attack(b))
            {
                attackmovie temp;//动画
                temp.begin.first=a->getreal_x();
                temp.begin.second=a->getreal_y();
                temp.end.first=b->getreal_x();
                temp.end.second=b->getreal_y();
                temp.place.first=temp.begin.first;
                temp.place.second=temp.begin.second;
                temp.time=sqrt(abs(pow(temp.end.first,2)-pow(temp.begin.first,2))+abs(pow(temp.end.second,2)-pow(temp.begin.second,2)))/48;
                //qDebug()<<QString::number(sqrt(abs(pow(temp.end.first,2)-pow(temp.begin.first,2))+abs(pow(temp.end.second,2)-pow(temp.begin.second,2)))/48);
                temp.speedx=(temp.end.first-temp.begin.first)/temp.time;
                temp.speedy=(temp.end.second-temp.begin.second)/temp.time;
                temp.type=1;
                game_data.attack.push_back(temp);
                if(a->state.find(2)!=a->state.end()&&!b->dontdif)
                {
                    if(b->frozen_time==0)
                        b->speed/=2;
                    b->frozen_time=25;//冰冻
                }
                else if(a->state.find(5)!=a->state.end()&&!b->dontdif)
                {
                    b->fire_time=25;//燃烧
                }
                if(a->state.find(3)==a->state.end())//范围伤害
               break;
                else
                {
                    attacktime++;
                    if(attacktime>=3)
                        break;
                }
            }
        }
    }
    for(auto a:game_data.enemy)
    {
        for(auto b:game_data.defeater)
        {
            if(a->attack(b))
            {
                attackmovie temp;
                temp.begin.first=a->getreal_x();
                temp.begin.second=a->getreal_y();
                temp.end.first=b->getreal_x();
                temp.end.second=b->getreal_y();
                temp.place.first=temp.begin.first;
                temp.place.second=temp.begin.second;
                temp.time=sqrt(abs(pow(temp.end.first,2)-pow(temp.begin.first,2))+abs(pow(temp.end.second,2)-pow(temp.begin.second,2)))/48;
                temp.speedx=(temp.end.first-temp.begin.first)/temp.time;
                temp.speedy=(temp.end.second-temp.begin.second)/temp.time;
                temp.type=0;
                game_data.attack.push_back(temp);
               break;
            }
        }
    }
    //QTime t2=QTime::currentTime();
    //qDebug()<<"all"<<t0.msecsTo(t1)<<"ms";
    //qDebug()<<"up2"<<t1.msecsTo(t2)<<"ms";
}
void gameStart::defeatdead(int x,int y,int range)
{
    //死亡音频
    if(range==1)
    {
        soundeffect_scv_help->play();
    }
    else if(range==3)
    {
        soundeffect_ghost_help->play();
    }

    if(range==-1)
        resouce2_factor--;
    if(range==1||range==-1)
        game_data.play[x][y]=1;
    else
        game_data.play[x][y]=0;
    for(int i=0;i<game_data.defeater.size();i++)
    {
        if(x==game_data.defeater[i]->getx()&&y==game_data.defeater[i]->gety())
        {
            game_data.defeater.erase(game_data.defeater.begin()+i);
            break;
        }
    }
    for(auto a:game_data.enemy)
    {
        if(a->stop)
            continue;
        auto i=a->path.begin();
        pair<int,int>temp=make_pair(i->first,i->second);//保存第一个点
        ++i;//从下一个点开始搜索，放置中途环路出bug
        a->path=a->searchpath(game_data.play,i->first,i->second);
        a->path.push_front(temp);//加回第一个
    }
}
void gameStart::upresouce2()//瓦斯
{
    //qDebug()<<QString::number(resouce2_factor);
    resource2+=resouce2_factor;
}
gameStart::~gameStart()
{
    //qDebug()<<"close";
    delete ui;
}
