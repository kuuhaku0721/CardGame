#include "itemcard.h"
#include "ui_itemcard.h"

ItemCard::ItemCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ItemCard)
{
    ui->setupUi(this);

    // 取消边框，禁止缩放
    this->setWindowFlag(Qt::FramelessWindowHint);

    ui->gridLayoutWidget->move(5,5);

    m_isSelected = false;

    QFont font("Arial", 14);
    ui->lab_text->setFont(font);
    ui->lab_text->setAlignment(Qt::AlignCenter);

    // TODO:buff图标还没设计好，所以先不管
    // ui->lab_bufImg->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
}

ItemCard::~ItemCard()
{
    delete ui;
}

void ItemCard::setId(int id)
{
    m_id = id;
}

void ItemCard::setStatus(Status stas)
{
    this->m_status = stas;
    // 确定身份之后绘制背景
    paintBackground();
}

void ItemCard::setIsSelected(bool selected)
{
    m_isSelected = selected;
    QPair<int, bool> pair(m_id, m_isSelected);
    emit isSelected(pair);
    update();
}

bool ItemCard::getIsSelected()
{
    return m_isSelected;
}

Status ItemCard::getStatus()
{
    return m_status;
}

void ItemCard::drawCard()
{
    ui->lab_text->setText(m_status.getDescription());
}

void ItemCard::paintBackground()
{
    // TODO: 等道具牌的类型多了之后这里应该是根据不同类型选中不同的背景，这里就做个模拟
    m_stylesheet = "background-image: url(:/img/item";
    int r = 2;
    switch(m_status.getEffect())
    {
    case NORMAL:
        r = 3;
        break;
    case SILENT:
        r = 1;
        break;
    case DURATION:
        r = 4;
        break;
    }                                           // WARN: 给Widget窗口设置的样式表会应用到所有的子控件上，所以需要有一个排除项
    m_stylesheet += QString::number(r) + ".jpg); border-radius: 5px; color: rgb(85, 255, 0);";
    this->setStyleSheet(m_stylesheet);
    // 取消掉子控件的背景
    ui->lab_text->setStyleSheet("");
}

// 鼠标点击更换状态
void ItemCard::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_isSelected = !m_isSelected;
    QPair<int, bool> pair(m_id, m_isSelected);
    emit isSelected(pair);
    // 更新状态
    update();
}

void ItemCard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if(m_isSelected)
    {
        // 画线
        QPainter painter(this);
        QPen pen(Qt::red, 5, Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(0, 0, width() - 1, height() - 1);

        ui->gridLayoutWidget->resize(280, 60);
    }
    else
    {
        ui->gridLayoutWidget->resize(260, 45);
    }
}
