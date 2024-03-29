#ifndef ITEMCARD_H
#define ITEMCARD_H

#include "status.h"

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPen>
#include <QPair>
#include <QRandomGenerator>

namespace Ui {
class ItemCard;
}

class ItemCard : public QWidget
{
    Q_OBJECT

public:
    explicit ItemCard(QWidget *parent = nullptr);
    ~ItemCard();

public:
    void setId(int id);
    void setStatus(Status stas);
    void setIsSelected(bool selected);

    bool getIsSelected();
    Status getStatus();

    void drawCard();
    void paintBackground();

signals:
    void isSelected(QPair<int, bool> pair);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::ItemCard *ui;

    int m_id;                   // TODO：还得抽象一层，因为所有的牌都由这几项功能，得抽象出来一个牌的父类
    bool m_isSelected;
    QString m_stylesheet;

    Status m_status;
};

#endif // ITEMCARD_H
