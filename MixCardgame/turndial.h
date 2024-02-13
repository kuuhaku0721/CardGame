#ifndef TURNDIAL_H
#define TURNDIAL_H

#include <QDial>
#include <QObject>
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>

class TurnDial : public QDial
{
    Q_OBJECT
public:
    TurnDial(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QColor m_color;
};

#endif // TURNDIAL_H
