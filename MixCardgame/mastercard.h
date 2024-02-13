#ifndef MASTERCARD_H
#define MASTERCARD_H

#include "master.h"

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPen>

namespace Ui {
class MasterCard;
}

class MasterCard : public QWidget
{
    Q_OBJECT

public:
    explicit MasterCard(QWidget *parent = nullptr);
    ~MasterCard();

public:
    void setIsSelected(bool selected);
    void setMaster(Master master);
    void setHP(int hp);
    void setTarget(bool target);
    bool getIsSelected();
    bool getTarget();
    int getHP();
    int getATK();
    void drawCard();
    void paintBackground();
    Master getMaster();

signals:
    void isSelected(bool isSelected);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MasterCard *ui;

    bool m_isTarget;
    bool m_isSelected;
    Master m_master;
};

#endif // MASTERCARD_H
