#include "defeat.h"

bool defeat::inRange(defeat*d)
{
    if ((abs(x - d->getx()) <= range && abs(y - d->gety()) <= range))
        return true;
    return false;
}

bool defeat::attack(defeat*target)
{
    if (islive() && target->islive() && inRange(target))
    {
        target->hurt(this);
        return true;
    }
    return false;
}

bool defeat::hurt(defeat*attacker)
{
    hp -= attacker->getatt();
    //qDebug()<<QString::number(att)<<" "<<QString::number(hp);
    return islive();
}
void defeat::setstate(int n)
{
    state.insert(n);
    if(n==1)
    {
        att*=2;
    }
    else if(n==4)
    {
        hp+=120;
        hp_max+=120;
    }

}
defeat::~defeat()
{
    emit this->dead(x,y,range);
    emit this->closeedit();
}
