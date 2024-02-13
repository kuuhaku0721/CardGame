#include "servent.h"

Servent::Servent()
{
    this->m_name = "无名从者";
    this->m_atk = 5;
    this->m_hp = 20;
}

Servent::Servent(QString name, int atk, int hp)
{
    this->m_name = name;
    this->m_atk = atk;
    this->m_hp = hp;
}

Servent::~Servent()
{
}

QString Servent::getName()
{
    return m_name;
}

int Servent::getATK()
{
    return m_atk;
}

int Servent::getHP()
{
    return m_hp;
}

void Servent::setATK(int atk)
{
    this->m_atk = atk;
}

void Servent::setHP(int hp)
{
    this->m_hp = hp;
}
