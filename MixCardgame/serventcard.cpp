#include "serventcard.h"
#include "ui_serventcard.h"

ServentCard::ServentCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServentCard)
{
    ui->setupUi(this);

    lab_attack = ui->label_attack;
    lab_health= ui->label_health;
    // TODO:Buff图标这个功能还没做好，做好了再把它加进来
    // layout_buff = ui->verticalLayout_Buff;

    m_isSelected = false;
    m_isAlive = true;

    ui->gridLayoutWidget->move(5, 5);


    // 背景在UI界面直接设置
    QFont font("Arial", 20);
    lab_attack->setFont(font);
    lab_attack->setAlignment(Qt::AlignCenter);

    lab_health->setFont(font);
    lab_health->setAlignment(Qt::AlignCenter);
}

ServentCard::~ServentCard()
{
    delete ui;
}

void ServentCard::setIsSelected(bool selected)
{
    m_isSelected = selected;
    QPair<int, bool> pair(m_id, m_isSelected);
    emit isSelected(pair, m_owned);
    update();
}

void ServentCard::setOwned(bool owner)
{
    this->m_owned = owner;
}

void ServentCard::setId(int id)
{
    this->m_id = id;
}

void ServentCard::setServent(Servent servent)
{
    this->m_servent = servent;
    // 设置完身份之后绘制背景图片
    paintBackground();
}

void ServentCard::setATK(int atk)
{
    m_servent.setATK(atk);
    lab_attack->setText(QString::number(atk));
}

void ServentCard::setHP(int hp)
{
    m_servent.setHP(hp);
    lab_health->setText(QString::number(hp));
}

void ServentCard::setAlive(bool alive)
{
    this->m_isAlive = alive;
}

int ServentCard::getATK()
{
    return m_servent.getATK();
}

int ServentCard::getHP()
{
    return m_servent.getHP();
}

bool ServentCard::getAlive()
{
    return m_isAlive;
}

QString ServentCard::getName()
{
    return m_servent.getName();
}

void ServentCard::drawCard()
{
    ui->label_attack->setText(QString::number(m_servent.getATK()));
    ui->label_health->setText(QString::number(m_servent.getHP()));
}

void ServentCard::paintBackground()
{
    m_stylesheet = "background-image: url(:/img/" + m_servent.getName() + ".png); border-radius: 10px;";
    this->setStyleSheet(m_stylesheet);
}

void ServentCard::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_isSelected = !m_isSelected;
    QPair<int, bool> pair(m_id, m_isSelected);
    emit isSelected(pair, m_owned);
    // 更新状态
    update();
}

void ServentCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    // 选中后画个边框，粗一点，标识当前选中此项
    if(m_isSelected)
    {
        // 画线
        QPainter painter(this);
        QPen pen(Qt::red, 5, Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0, 0, width() - 1, height() - 1);

        ui->gridLayoutWidget->resize(190, 270);
    }
    else
    {
        ui->gridLayoutWidget->resize(180, 250);
    }
}
