#ifndef SERVENT_H
#define SERVENT_H

#include <QImage>
#include <QString>


class Servent
{
public:
    Servent();
    Servent(QString name, int atk, int hp);
    ~Servent();

public:
    QString getName();
    int getATK();
    int getHP();
    void setATK(int atk);
    void setHP(int hp);

private:
    QString m_name;
    int m_atk;
    int m_hp;
};

#endif // SERVENT_H
