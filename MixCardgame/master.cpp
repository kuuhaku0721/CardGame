#include "master.h"

Master::Master() {}

Master::~Master() {}

Master::Master(QString name, int atk, int hp)
{
    this->m_name = name;
    this->m_atk = atk;
    this->m_hp = hp;
}

QString Master::getName()
{
    return m_name;
}

int Master::getATK()
{
    return m_atk;
}

int Master::getHP()
{
    return m_hp;
}

void Master::setHP(int hp)
{
    this->m_hp = hp;
}
