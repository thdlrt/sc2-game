#include "gamedata.h"
//全局变量
int bgmvalue=99,gamevalue=99;
QMediaPlayer*sound_effect_resource1,*sound_effect_resource2,*sound_effect_research;
gameData::gameData()
{

}
void Delay(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

