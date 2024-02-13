#include "turndial.h"

TurnDial::TurnDial(QWidget *parent)
    : QDial(parent)
{
    m_color = Qt::blue;
    setRange(0, 100);

}

void TurnDial::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRectF rect(0, 0, 70, 50);  // 设置控件宽度为70，高度为50

    int radius = qMin(rect.width(), rect.height()) / 2;

    // 绘制Dial背景
    painter.save();
    painter.setBrush(m_color);
    painter.drawEllipse(rect.adjusted(2, 2, -2, -2));
    painter.restore();

    // 绘制Dial指针
    painter.save();
    painter.translate(rect.center());
    painter.rotate(-45.0 + (270.0 * value() / maximum()));

    QPainterPath path;
    path.moveTo(-3, -3);
    path.lineTo(3, -3);
    path.lineTo(0, -radius + 10);
    path.closeSubpath();

    // 根据value值设置渐变色
    QLinearGradient gradient(rect.topLeft(), rect.bottomRight());
    if (value() >= 0 && value() <= 50) {
        gradient.setColorAt(0, Qt::blue);
        gradient.setColorAt(1, Qt::darkBlue);
    } else if (value() > 50 && value() <= 100) {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    painter.drawPath(path);
    painter.restore();
}
