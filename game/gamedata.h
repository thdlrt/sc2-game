#ifndef GAMEDATA_H
#define GAMEDATA_H
#include<QTime>
#include<QEventLoop>
#include<QCoreApplication>
#include<QMessageBox>
#include<QPushButton>
#include <QLabel>
#include<QToolTip>
#include <QCoreApplication>
#include<QDebug>
#include<vector>
#include<QString>
#include<fstream>
#include<sstream>
#include<string>
#include<QPainter>
#include<QTimer>
#include<QMouseEvent>
#include<list>
#include<deque>
#include<QMovie>
#include<set>
#include<QTime>
#include<QtGlobal>
#include<QFileDialog>
#include<cmath>
#include<QMediaPlayer>
#include<QUrl>
#include<QAudioOutput>
#include<QSoundEffect>
using namespace std;
extern int bgmvalue,gamevalue;
extern QMediaPlayer*sound_effect_resource1,*sound_effect_resource2,*sound_effect_research;

struct mapList{//地图列表
    mapList(QString id,QString name,QString dif,QString user,QString path):id(id),name(name),dif(dif),user(user),path(path){}
    QString id;
    QString name;
    QString dif;
    QString user;
    QString path;
};
class gameData
{
public:
    gameData();

};
void Delay(int msec);//延时
#endif // GAMEDATA_H
