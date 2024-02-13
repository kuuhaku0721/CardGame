#ifndef STATUS_H
#define STATUS_H

#include <QString>
#include <QImage>

enum Effect
{
    NORMAL,
    SILENT,
    DURATION
};

class Status
{
public:
    Status();
    Status(QString desc, int atk, int hp, Effect eff);
    ~Status();

    // TODO
    // Status(QString description, int attack, int health, bool isSlience, int duration);  // 外加特殊能力

public:
    QImage getImg();
    QString getDescription();
    int getATK();
    int getHP();
    Effect getEffect();
    // TODO:其他效果等待添加

private:
    QImage m_img;           // buff图标
    QString m_description;  // 描述
    int m_attack;           // 攻击
    int m_health;           // 生命

    Effect m_effect;

    // TODO:未来打算添加的：烧伤、中毒、冻结、以及各种状态的相互影响
    // 沉默
    // bool isSlience;
    // // 持续回合数
    // int duration;
};

#endif // STATUS_H
