#ifndef MASTER_H
#define MASTER_H

#include <QString>
#include <QImage>

class Master
{
public:
    Master();
    Master(QString name, int atk, int hp);
    ~Master();

public:
    QString getName();
    int getATK();
    int getHP();
    void setHP(int hp);

private:
    QString m_name;
    int m_atk;
    int m_hp;
};

#endif // MASTER_H
