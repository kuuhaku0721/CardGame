#include "status.h"

Status::Status()
{
    this->m_attack = 0;
    this->m_health = 0;

}

Status::Status(QString desc, int atk, int hp, Effect eff)
{
    this->m_description = desc;
    this->m_attack = atk;
    this->m_health = hp;
    this->m_effect = eff;
}

Status::~Status() {}

QImage Status::getImg()
{
    return m_img;
}

QString Status::getDescription()
{
    return m_description;
}

int Status::getATK()
{
    return m_attack;
}

int Status::getHP()
{
    return m_health;
}

Effect Status::getEffect()
{
    return m_effect;
}
