#ifndef SERVENTCARD_H
#define SERVENTCARD_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QStatusBar>
#include <QLabel>
#include <QMap>
#include <QVBoxLayout>
#include <QPair>
#include "servent.h"

namespace Ui {
class ServentCard;
}

class ServentCard : public QWidget
{
    Q_OBJECT

public:
    explicit ServentCard(QWidget *parent = nullptr);
    ~ServentCard();

public:
    void setIsSelected(bool selected);
    void setOwned(bool owner);
    void setId(int id);
    void setServent(Servent servent);
    void setATK(int atk);
    void setHP(int hp);
    void setAlive(bool alive);

    int getATK();
    int getHP();
    bool getAlive();
    QString getName();

    void drawCard();
    void paintBackground();

    void addBuff(/*TODO: 没想好参数*/);

signals:
    void isSelected(QPair<int, bool> pair, bool owner);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::ServentCard *ui;

    // 固有属性
    int m_id;
    bool m_isSelected;
    bool m_owned;
    QString m_stylesheet;

    Servent m_servent;
    bool m_isAlive;

    // 拥有控件
    QLabel* lab_attack;
    QLabel* lab_health;

    // TODO: // buff列表，理论成立，等待实践
    QVBoxLayout* layout_buff;
    QMap<QLabel*, bool> m_buffMap;
};

#endif // SERVENTCARD_H
