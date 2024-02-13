#include "mastercard.h"
#include "ui_mastercard.h"

MasterCard::MasterCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterCard)
{
    ui->setupUi(this);

    m_isSelected = false;
    m_isTarget = false;

    QFont font("Arial", 15);
    ui->lab_health->setFont(font);
    ui->lab_health->setAlignment(Qt::AlignCenter);
}

MasterCard::~MasterCard()
{
    delete ui;
}

void MasterCard::setIsSelected(bool selected)
{
    m_isSelected = selected;
    emit isSelected(m_isSelected);
    update();
}

void MasterCard::setMaster(Master master)
{
    this->m_master = master;
    // 设置完身份之后绘制背景
    paintBackground();
}

void MasterCard::setHP(int hp)
{
    m_master.setHP(hp);
}

void MasterCard::setTarget(bool target)
{
    this->m_isTarget = target;
}

bool MasterCard::getIsSelected()
{
    return m_isSelected;
}

bool MasterCard::getTarget()
{
    return m_isTarget;
}

int MasterCard::getHP()
{
    return m_master.getHP();
}

int MasterCard::getATK()
{
    return m_master.getATK();
}

void MasterCard::drawCard()
{
    ui->lab_health->setText(QString::number(m_master.getHP()));
}

void MasterCard::paintBackground()
{
    QString styleSheet = "background-image: url(:/img/" + m_master.getName() + ".png);";
    this->setStyleSheet(styleSheet);
}

Master MasterCard::getMaster()
{
    return m_master;
}

void MasterCard::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_isSelected = !m_isSelected;
    emit isSelected(m_isSelected);
    update();
}

void MasterCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    // 选中后画个边框，粗一点，标识当前选中此项
    if(m_isSelected)
    {
        // 画线
        QPainter painter(this);
        QPen pen(Qt::red, 3, Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(10, 10, width() - 20, height() - 20);

        ui->lab_master->resize(85, 76);
    }
    else
    {
        ui->lab_master->resize(80, 76);
    }
}
