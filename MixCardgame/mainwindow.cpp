#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("修改项目结构分支，能运行就是修改成功了");
    this->setWindowIcon(QIcon(":/img/sikari.ico"));

    // 固定大小、禁止缩放
    this->setFixedSize(1250, 800);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 初始化背景及样式表
    Init();

    // 初始化属性值、标志位
    m_turn = false; // 先手默认player
    m_itemId = -1;
    m_serventId = -1;
    m_isCardSelected = false;
    m_isServentSelected = false;
    m_isMasterSelected = false;
    m_gameset = false;
    m_isNoEnd = false;

    m_attackPair.first = -1;
    m_attackPair.second = -1;

    m_totalTurns = 10;
    ui->lcd_countDown->display(m_totalTurns);

    // 初始化工具
    m_tool = new GenerateTool();

    // 绑定信号槽
    connect(this, &MainWindow::ImplBuff, this, &MainWindow::ImplementBuff);
    connect(this, &MainWindow::ImplAttack, this, &MainWindow::ImplementAttack);
    connect(this, &MainWindow::ImplTurn, this, &MainWindow::ImplementTurn);
    connect(this, &MainWindow::GameSet, this, &MainWindow::ImplementGameSet);
    connect(this, &MainWindow::AddInfo, this, &MainWindow::ImplementAddInfo);
    connect(this, &MainWindow::ImplUpdateCard, this, &MainWindow::ImplementUpdateItemCard);


    /// 测试代码 ///

    // TODO:加一个ScrollArea，程序启动，给个按钮，选择自选角色启动，然后显示这个ScrollArea，里面以水平方式
    //      将所有的卡牌的图片显示出来，并且需要支持左右滑动选择
    //      选择卡牌仍然要有选中特效，也就是说，这几个卡牌还是要生成出来
    //      一共需要选择三个，选不够三个不准点下一步
    //      需要有个信号，选完把选中的...id或者名字传出去，交给槽函数或者生成函数
    //      然后继续生成过程

    /// 测试代码 ///
}

void MainWindow::Init()
{
    // 先隐藏掉三个控件
    ui->dial->setVisible(false);
    ui->lcd_countDown->setVisible(false);
    ui->textEdit->setVisible(false);

    // 禁用重开按钮
    ui->btn_restart->setEnabled(false);

    // 隐藏说明按钮
    ui->btn_character->setVisible(false);

    // 设置窗口背景
    QString bkpath = ":/img/bk";
    int r = QRandomGenerator::global()->bounded(1, 6);
    bkpath += QString::number(r) + ".png";
    QPixmap pixmap(bkpath);
    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    ui->textEdit->setStyleSheet("QTextEdit {"
                                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 255, 255, 30), stop:1 #7FFFD4);"
                                "color: #333333;"
                                "border-radius: 5px;"
                                "font-size: 12px;"
                                "padding: 10px;"
                                "}"
                                "QTextEdit::focus {"
                                "border: 2px solid #333333;"
                                "}");
    ui->lcd_countDown->setStyleSheet("QLCDNumber {"
                                     "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 rgba(255, 255, 255, 30), stop:1 #7FFFD4);"
                                     "color: #333333;"
                                     "border-radius: 5px;"
                                     "font-size: 24px;"
                                     "padding: 10px;"
                                     "}"
                                     "QLCDNumber::segment {"
                                     "background-color: #7FFFD4;"
                                     "}"
                                     "QLCDNumber::focus {"
                                     "border: 2px solid #333333;"
                                     "}");
    // TODO: 支持后序更新修改
}

void MainWindow::GameStart()
{
    // 隐藏原本的四个控件
    ui->lineEdit->setVisible(false);
    ui->btn_cnt->setVisible(false);
    ui->btn_noend->setVisible(false);
    ui->lab_info->setVisible(false);

    // 显示三个状态控件
    ui->dial->setVisible(true);
    // ui->dial->setEnabled(false);
    ui->lcd_countDown->setVisible(true);
    ui->textEdit->setVisible(true);

    // 显示说明按钮
    ui->btn_character->setVisible(true);

    // 生成所有道具牌
    GenerateItemCards();

    // 生成所有侍从牌
    GenerateServentCards();

    // 生成所有角色牌
    GenerateMasterCards();

    // 发射信号，正式开始
    emit ImplTurn(); // 发射开始信号，正式开始

    ui->textEdit->append("游戏开始");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 生成道具牌在窗口上
void MainWindow::GenerateItemCards()
{
    // 玩家道具牌
    QList<Status> statuses = m_tool->getStatus();
    // 创建
    player_card1 = new ItemCard(this); player_card1->setId(1);
    player_card2 = new ItemCard(this); player_card2->setId(2);
    player_card3 = new ItemCard(this); player_card3->setId(3);
    player_card4 = new ItemCard(this); player_card4->setId(4);
    player_card5 = new ItemCard(this); player_card5->setId(5);

    player_card1->setStatus(statuses[0]);
    player_card2->setStatus(statuses[1]);
    player_card3->setStatus(statuses[2]);
    player_card4->setStatus(statuses[3]);
    player_card5->setStatus(statuses[4]);

    m_playerItemCardList << player_card1 << player_card2 << player_card3 << player_card4 << player_card5;
    // 移动
    player_card1->move(30,390 + 30);
    player_card2->move(30,460 + 30);
    player_card3->move(30,530 + 30);
    player_card4->move(30,600 + 30);
    player_card5->move(30,670 + 30);
    // 绘制
    player_card1->drawCard();
    player_card2->drawCard();
    player_card3->drawCard();
    player_card4->drawCard();
    player_card5->drawCard();
    // 展示
    player_card1->show();
    player_card2->show();
    player_card3->show();
    player_card4->show();
    player_card5->show();
    // 绑定
    connect(player_card1, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);
    connect(player_card2, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);
    connect(player_card3, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);
    connect(player_card4, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);
    connect(player_card5, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);

    // 敌方道具牌
    statuses = m_tool->getStatus();
    // 创建
    enemy_card1 = new ItemCard(this); enemy_card1->setId(1);
    enemy_card2 = new ItemCard(this); enemy_card2->setId(2);
    enemy_card3 = new ItemCard(this); enemy_card3->setId(3);
    enemy_card4 = new ItemCard(this); enemy_card4->setId(4);
    enemy_card5 = new ItemCard(this); enemy_card5->setId(5);

    enemy_card1->setStatus(statuses[0]);
    enemy_card2->setStatus(statuses[1]);
    enemy_card3->setStatus(statuses[2]);
    enemy_card4->setStatus(statuses[3]);
    enemy_card5->setStatus(statuses[4]);

    m_enemyItemCardList << enemy_card1 << enemy_card2 << enemy_card3 << enemy_card4 << enemy_card5;
    // 移动
    enemy_card1->move(30,290);
    enemy_card2->move(30,220);
    enemy_card3->move(30,150);
    enemy_card4->move(30,80);
    enemy_card5->move(30,10);
    // 绘制
    enemy_card1->drawCard();
    enemy_card2->drawCard();
    enemy_card3->drawCard();
    enemy_card4->drawCard();
    enemy_card5->drawCard();
    // 展示
    enemy_card1->show();
    enemy_card2->show();
    enemy_card3->show();
    enemy_card4->show();
    enemy_card5->show();
    // 绑定
    connect(enemy_card1, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);
    connect(enemy_card2, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);
    connect(enemy_card3, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);
    connect(enemy_card4, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);
    connect(enemy_card5, &ItemCard::isSelected, this, &MainWindow::ChangeItemCardState);

    // 保存所有player牌
    m_playerList.append(QVariant::fromValue(player_card1));
    m_playerList.append(QVariant::fromValue(player_card2));
    m_playerList.append(QVariant::fromValue(player_card3));
    m_playerList.append(QVariant::fromValue(player_card4));
    m_playerList.append(QVariant::fromValue(player_card5));
    // 保存所有enemy牌
    m_enemyList.append(QVariant::fromValue(enemy_card1));
    m_enemyList.append(QVariant::fromValue(enemy_card2));
    m_enemyList.append(QVariant::fromValue(enemy_card3));
    m_enemyList.append(QVariant::fromValue(enemy_card4));
    m_enemyList.append(QVariant::fromValue(enemy_card5));
}

void MainWindow::GenerateServentCards()
{
    QList<Servent> servents = m_tool->getServent();
    // 生成player的Servent
    player_servent1 = new ServentCard(this);
    player_servent2 = new ServentCard(this);
    player_servent3 = new ServentCard(this);

    player_servent1->setId(1);
    player_servent2->setId(2);
    player_servent3->setId(3);

    player_servent1->setOwned(true);
    player_servent2->setOwned(true);
    player_servent3->setOwned(true);

    player_servent1->setServent(servents[0]);
    player_servent2->setServent(servents[1]);
    player_servent3->setServent(servents[2]);

    m_playerServentCardList << player_servent1 << player_servent2 << player_servent3;
    player_servent1->move(340, 420);
    player_servent2->move(550, 420);
    player_servent3->move(760, 420);

    connect(player_servent1, &ServentCard::isSelected, this, &MainWindow::ChangeServentCardState);
    connect(player_servent2, &ServentCard::isSelected, this, &MainWindow::ChangeServentCardState);
    connect(player_servent3, &ServentCard::isSelected, this, &MainWindow::ChangeServentCardState);

    player_servent1->drawCard();
    player_servent2->drawCard();
    player_servent3->drawCard();

    emit AddInfo("[player]已召唤Servent: " + player_servent1->getName());
    emit AddInfo("[player]已召唤Servent: " + player_servent2->getName());
    emit AddInfo("[player]已召唤Servent: " + player_servent3->getName());

    player_servent1->show();
    player_servent2->show();
    player_servent3->show();

    // 生成enemy的Servent
    servents = m_tool->getServent();
    enemy_servent1 = new ServentCard(this);
    enemy_servent2 = new ServentCard(this);
    enemy_servent3 = new ServentCard(this);

    enemy_servent1->setId(1);
    enemy_servent2->setId(2);
    enemy_servent3->setId(3);

    enemy_servent1->setOwned(false);
    enemy_servent2->setOwned(false);
    enemy_servent3->setOwned(false);

    enemy_servent1->setServent(servents[0]);
    enemy_servent2->setServent(servents[1]);
    enemy_servent3->setServent(servents[2]);

    m_enemyServentCardList << enemy_servent1 << enemy_servent2 << enemy_servent3;
    enemy_servent1->move(340, 100);
    enemy_servent2->move(550, 100);
    enemy_servent3->move(760, 100);

    connect(enemy_servent1, &ServentCard::isSelected, this, &MainWindow::ChangeServentCardState);
    connect(enemy_servent2, &ServentCard::isSelected, this, &MainWindow::ChangeServentCardState);
    connect(enemy_servent3, &ServentCard::isSelected, this, &MainWindow::ChangeServentCardState);

    enemy_servent1->drawCard();
    enemy_servent2->drawCard();
    enemy_servent3->drawCard();

    emit AddInfo("[enemy]已召唤Servent: " + enemy_servent1->getName());
    emit AddInfo("[enemy]已召唤Servent: " + enemy_servent2->getName());
    emit AddInfo("[enemy]已召唤Servent: " + enemy_servent3->getName());

    enemy_servent1->show();
    enemy_servent2->show();
    enemy_servent3->show();

    m_playerList.append(QVariant::fromValue(player_servent1));
    m_playerList.append(QVariant::fromValue(player_servent2));
    m_playerList.append(QVariant::fromValue(player_servent3));
    m_enemyList.append(QVariant::fromValue(enemy_servent1));
    m_enemyList.append(QVariant::fromValue(enemy_servent2));
    m_enemyList.append(QVariant::fromValue(enemy_servent3));
}

void MainWindow::GenerateMasterCards()
{
    // 玩家牌
    QList<Master> masters = m_tool->getMaster();

    player = new MasterCard(this);
    player->setMaster(masters[0]);
    player->move(600,690);
    player->drawCard();
    player->show();
    connect(player, &MasterCard::isSelected, this, &MainWindow::ChangeMasterCardState);

    enemy = new MasterCard(this);
    enemy->setMaster(masters[1]);
    enemy->move(600,0);
    enemy->drawCard();
    enemy->show();
    connect(enemy, &MasterCard::isSelected, this, &MainWindow::ChangeMasterCardState);

    emit AddInfo("[player]:" + player->getMaster().getName());
    emit AddInfo("[enemy]:" + enemy->getMaster().getName());

    m_playerList.append(QVariant::fromValue(player));
    m_enemyList.append(QVariant::fromValue(enemy));
}

void MainWindow::ChangeItemCardState(QPair<int, bool> pair)
{
    m_itemId = pair.first;
    m_isCardSelected = pair.second;
    qDebug() << "现在是第: " << m_itemId << "个道具牌被点击了";

    // 根据回合改变状态
    if(m_turn)
    {   // [player]回合，改变player状态
        if(m_isCardSelected)
        {
            // 改变其他道具牌的状态
            for (int i = 0; i < m_playerItemCardList.count(); ++i) {
                if(i + 1 == m_itemId) continue;
                m_playerItemCardList[i]->setEnabled(false);
            }
        }
        else
        {
            for (int i = 0; i < m_playerItemCardList.count(); ++i) {
                m_playerItemCardList[i]->setEnabled(true);
            }
        }
    }
    else
    {   // 当前是[enemy]回合，更改enemy状态
        if(m_isCardSelected)
        {
            for (int i = 0; i < m_enemyItemCardList.count(); ++i) {
                if(i + 1 == m_itemId) continue;
                m_enemyItemCardList[i]->setEnabled(false);
            }
        }
        else
        {
            for (int i = 0; i < m_enemyItemCardList.count(); ++i) {
                m_enemyItemCardList[i]->setEnabled(true);
            }
        }
    }
}

void MainWindow::ChangeServentCardState(QPair<int, bool> pair, bool owner) // owner:true为player false为enemy
{
    if(m_gameset)
        return;

    m_serventId = pair.first;
    m_isServentSelected = pair.second;
    qDebug() << "当前选中的Servent是: " << m_serventId << "号.";

    if(m_turn)
    {   // 当前是[player]回合
        // 使用道具牌
        if(m_isCardSelected)
        {
            qDebug() << "已选择了道具牌，道具牌id为: " << m_itemId;
            m_playerItemCardList[m_itemId - 1]->setIsSelected(false);
            m_playerServentCardList[m_serventId - 1]->setIsSelected(false);
            emit ImplBuff(m_itemId, m_serventId);
            return;
        }

        // master 攻击 servent
        if(m_isMasterSelected)
        {
            ServentCard* servent = m_enemyServentCardList[m_serventId - 1];
            servent->setHP(servent->getHP() - player->getATK());
            if(servent->getHP() <= 0)
            {
                servent->setHP(0);
                servent->setAlive(false);
                servent->setEnabled(false);
            }
            // 取消选中状态
            player->setIsSelected(false);       // WARN:这里做个记录：取消选中状态的时候，顺序必须是先master然后servent
            servent->setIsSelected(false);      // 因为这个函数的判断条件是masterSelected，如果先servent会再执行一遍这些函数，然后无穷无尽的循环下去直到崩溃
            emit AddInfo("[player]攻击了enemy的servent：" + servent->getName()
                         + ", 造成了" + QString::number(player->getATK()) + "点伤害");
            emit ImplTurn();
            return;
        }

        // servent 攻击 servent
        bool isAllDie = true;
        if(m_isServentSelected)
        {
            // enemy的master状态，在三个servent都阵亡的时候变为true
            for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
                if(m_enemyServentCardList[i]->getAlive())
                {
                    isAllDie = false;
                    break;
                }
            }
            if(isAllDie)
            {
                enemy->setEnabled(true);
            }

            // player的手牌状态，选中的为true，未选的为false
            for (int i = 0; i < m_playerServentCardList.count(); ++i) {
                if(i + 1 == m_serventId) continue;
                m_playerServentCardList[i]->setEnabled(false);
            }
            // enemy的手牌状态，三个都是true，并且等待响应点击
            for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
                if(m_enemyServentCardList[i]->getAlive() == false) continue;
                m_enemyServentCardList[i]->setEnabled(true);
            }
            // 道具牌状态，全都为false
            for (int i = 0; i < m_playerItemCardList.count(); ++i) {
                m_playerItemCardList[i]->setEnabled(false);
            }

            if(owner == true)
            {   // 选择的是player的servent
                m_attackPair.first = m_serventId;
            }
            else
            {   // 选择的是enemy的servent
                m_attackPair.second = m_serventId;
            }
        }
        else
        {
            if(isAllDie)
            {
                enemy->setEnabled(false);
            }
            for (int i = 0; i < m_playerServentCardList.count(); ++i) {
                if(m_playerServentCardList[i]->getAlive() == false) continue;
                m_playerServentCardList[i]->setEnabled(true);
            }
            for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
                m_enemyServentCardList[i]->setEnabled(false);
            }
            for (int i = 0; i < m_playerItemCardList.count(); ++i) {
                m_playerItemCardList[i]->setEnabled(true);
            }
            m_attackPair.first = -1;
            m_attackPair.second = -1;
        }
    }
    else
    {   // 当前是[enemy]回合
        // 使用道具牌
        if(m_isCardSelected)
        {
            qDebug() << "当前已经选择了道具牌，道具牌id为: " << m_itemId;  // TODO:更改为AddInfo
            m_enemyItemCardList[m_itemId - 1]->setIsSelected(false);
            m_enemyServentCardList[m_serventId - 1]->setIsSelected(false);
            emit ImplBuff(m_itemId, m_serventId);
            return;
        }

        // master 攻击 servent
        if(m_isMasterSelected)
        {
            ServentCard* servent = m_playerServentCardList[m_serventId - 1];
            servent->setHP(servent->getHP() - enemy->getATK());
            if(servent->getHP() <= 0)
            {
                servent->setHP(0);
                servent->setAlive(false);
                servent->setEnabled(false);
            }
            // 取消选中状态
            enemy->setIsSelected(false);
            servent->setIsSelected(false);
            emit AddInfo("[enemy]攻击了player的servent：" + servent->getName()
                         + ", 造成了" + QString::number(enemy->getATK()) + "点伤害");
            emit ImplTurn();
            return;
        }

        // servent 攻击 servent
        bool isAllDie = true;
        if(m_isServentSelected)
        {
            // player的master状态，在三个servent都阵亡的时候变为true
            for (int i = 0; i < m_playerServentCardList.count(); ++i) {
                if(m_playerServentCardList[i]->getAlive())
                {
                    isAllDie = false;
                    break;
                }
            }
            if(isAllDie)
            {
                player->setEnabled(true);
            }
            // enemy的servent状态,已经阵亡的不能选择
            for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
                if(i + 1 == m_serventId) continue;
                m_enemyServentCardList[i]->setEnabled(false);
            }
            // player的手牌状态，三个都是true，并且等待响应点击
            for (int i = 0; i < m_playerServentCardList.count(); ++i) {
                if(m_playerServentCardList[i]->getAlive() == false) continue;
                m_playerServentCardList[i]->setEnabled(true);
            }
            // 道具牌状态，全都为false
            for (int i = 0; i < m_enemyItemCardList.count(); ++i) {
                m_enemyItemCardList[i]->setEnabled(false);
            }

            if(owner == true)
            {   // 选择的是player的servent
                m_attackPair.first = m_serventId;
            }
            else
            {   // 选择的是enemy的servent
                m_attackPair.second = m_serventId;
            }
        }
        else
        {
            if(isAllDie)
            {
                player->setEnabled(true);
            }
            for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
                if(m_enemyServentCardList[i]->getAlive() == false) continue;
                m_enemyServentCardList[i]->setEnabled(true);
            }
            for (int i = 0; i < m_playerServentCardList.count(); ++i) {
                m_playerServentCardList[i]->setEnabled(false);
            }
            for (int i = 0; i < m_enemyItemCardList.count(); ++i) {
                m_enemyItemCardList[i]->setEnabled(true);
            }
            m_attackPair.first = -1;
            m_attackPair.second = -1;
        }
    }

    // 默认first是player，second是enemy，攻击方和被攻击方由回合决定
    if(m_attackPair.first != -1 && m_attackPair.second != -1)
    {
        qDebug() << "在发射Attack信号之前：pair.first = " << m_attackPair.first << ", second = " << m_attackPair.second;
        emit ImplAttack(m_attackPair);
        int playerServerID = m_attackPair.first - 1;
        int enemyServentID = m_attackPair.second - 1;
        // 发射完信号之后改变选中状态                 -1是因为pair存储的是ID不是下标
        m_playerServentCardList[playerServerID]->setIsSelected(false);
        m_enemyServentCardList[enemyServentID]->setIsSelected(false);
        // 重置
        m_attackPair.first = -1;
        m_attackPair.second = -1;
    }
}

void MainWindow::ChangeMasterCardState(bool selected)
{
    qDebug() << "选择了master牌";
    m_isMasterSelected = selected;

    if(m_turn)
    {   // player回合，选择master牌
        bool isAllDie = true;
        if(m_isMasterSelected)
        {
            for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
                if(m_enemyServentCardList[i]->getAlive())
                {
                    isAllDie = false;
                    break;
                }
            }
            if(isAllDie)
            {   // servent已经全部阵亡
                enemy->setEnabled(true);
            }
            else
            {   // 没有全部阵亡
                for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
                    if(m_enemyServentCardList[i]->getAlive())
                        m_enemyServentCardList[i]->setEnabled(true);
                }
            }

            // master 攻击 master
            if(player->getIsSelected() && enemy->getIsSelected())
            {
                enemy->setHP(enemy->getHP() - player->getATK());
                enemy->drawCard();
                player->setIsSelected(false);
                enemy->setIsSelected(false);
                if(enemy->getHP() <= 0)
                {
                    enemy->setHP(0);
                    emit GameSet(GameOver);
                    return;
                }
                emit AddInfo("[player]攻击了enemy的master，造成" + QString::number(player->getATK()) + "点伤害");
                emit ImplTurn();
                return;
            }

            // servent 攻击 master
            if(m_isServentSelected)
            {
                qDebug() << "player回合，servent攻击enemy的master";
                enemy->setHP(enemy->getHP() - m_playerServentCardList[m_serventId - 1]->getATK());
                enemy->drawCard();
                qDebug() << "攻击逻辑完成，设置状态";
                enemy->setIsSelected(false); // WARN:做记录，这里也要先让enemy设置selected状态然后再设servent，理由和上面哪个一样
                m_playerServentCardList[m_serventId - 1]->setIsSelected(false);
                qDebug() << "设置状态完成，打印信息，转换回合方";
                if(enemy->getHP() <= 0)
                {
                    enemy->setHP(0);
                    emit GameSet(GameOver);
                    return;
                }
                emit AddInfo("[player]使用" + m_playerServentCardList[m_serventId - 1]->getName() + "攻击了enemy的master");
                emit ImplTurn();
                qDebug() << "更换回合方完成，return掉";
                return;
            }
        }
        else
        {
            enemy->setEnabled(false);
            for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
                m_enemyServentCardList[i]->setEnabled(false);
            }
        }
    }
    else
    {   // enemy回合，选择master牌
        bool isAllDie = true;
        if(m_isMasterSelected)
        {
            for (int i = 0; i < m_playerServentCardList.count(); ++i) {
                if(m_playerServentCardList[i]->getAlive())
                {
                    isAllDie = false;
                    break;
                }
            }
            if(isAllDie)
            {   // servent已经全部阵亡
                player->setEnabled(true);
            }
            else
            {   // 没有全部阵亡
                for (int i = 0; i < m_playerServentCardList.count(); ++i) {
                    if(m_playerServentCardList[i]->getAlive())
                        m_playerServentCardList[i]->setEnabled(true);
                }
            }

            // master 攻击 master
            if(player->getIsSelected() && enemy->getIsSelected())
            {
                player->setHP(player->getHP() - enemy->getATK());
                player->drawCard();
                player->setIsSelected(false);
                enemy->setIsSelected(false);
                if(player->getHP() <= 0)
                {
                    player->setHP(0);
                    emit GameSet(GameOver);
                    return;
                }
                emit AddInfo("[enemy]攻击了player的master，造成" + QString::number(enemy->getATK()) + "点伤害");
                emit ImplTurn();
                return;
            }

            // servent 攻击 master
            if(m_isServentSelected)
            {
                player->setHP(player->getHP() - m_enemyServentCardList[m_serventId - 1]->getATK());
                player->drawCard();
                player->setIsSelected(false);
                m_enemyServentCardList[m_serventId - 1]->setIsSelected(false);
                if(player->getHP() <= 0)
                {
                    player->setHP(0);
                    emit GameSet(GameOver);
                    return;
                }
                emit AddInfo("[enemy]使用" + m_enemyServentCardList[m_serventId - 1]->getName() + "攻击了player的master");
                emit ImplTurn();
                return;
            }
        }
        else
        {
            player->setEnabled(false);
            for (int i = 0; i < m_playerServentCardList.count(); ++i) {
                m_playerServentCardList[i]->setEnabled(false);
            }
        }
    }
}

void MainWindow::ImplementBuff(int itemId, int serventId)
{
    // TODO:这个函数有待完善，因为不止有普通牌，还有其他带效果的牌也需要设置，也就是说，得能够支持更新
    Status buff;
    ServentCard* acceptCard;   // 接受的卡
    QString msg;
    if(m_turn)
    {
        msg = "[player]的";
        buff = m_playerItemCardList[itemId - 1]->getStatus();
        acceptCard = m_playerServentCardList[serventId - 1];
    }
    else
    {
        msg = "[enemy]的";
        buff = m_enemyItemCardList[itemId - 1]->getStatus();
        acceptCard = m_enemyServentCardList[serventId - 1];
    }
    // 根据牌类型的不同做出不同的应对措施
    switch(buff.getEffect())
    {
    case NORMAL:
        acceptCard->setATK(acceptCard->getATK() + buff.getATK());
        if(acceptCard->getATK() <= 0)
            acceptCard->setATK(0);
        acceptCard->setHP(acceptCard->getHP() + buff.getHP());
        if(acceptCard->getHP() <= 0)
        {
            msg += acceptCard->getName() + "自尽了";
            emit AddInfo(msg);
            acceptCard->setHP(0);
            acceptCard->setAlive(false);
            acceptCard->setEnabled(false);
        }
        break;
    case SILENT:
        break;
    case DURATION:
        break;
    }


    emit ImplUpdateCard(itemId); // 换牌
    emit ImplTurn(); // 更改回合方
}

void MainWindow::ImplementAttack(QPair<int, int> pair)
{
    qDebug() << "此为执行attack的槽函数：当前攻击方为：" << pair.first << ", 被攻击方为: " << pair.second;
    if(m_turn)
    {
        qDebug() << "现在是[player]回合，将执行player: " << pair.first << "对enemy: " << pair.second << "的攻击行动";
        emit AddInfo("[player]驱使" + m_playerServentCardList[pair.first - 1]->getName() + "对enemy的" + m_enemyServentCardList[pair.second - 1]->getName() + "发动了攻击");

        m_enemyServentCardList[pair.second - 1]->setHP(m_enemyServentCardList[pair.second - 1]->getHP() - m_playerServentCardList[pair.first - 1]->getATK());
        if(m_enemyServentCardList[pair.second - 1]->getHP() <= 0)
        {
            qDebug() << "enemy的第: " << pair.second << "号从者阵亡了";
            emit AddInfo("enemy的" + m_enemyServentCardList[pair.second - 1]->getName() + "阵亡了");

            m_enemyServentCardList[pair.second - 1]->setHP(0);
            m_enemyServentCardList[pair.second - 1]->setAlive(false);
            m_enemyServentCardList[pair.second - 1]->setEnabled(false);
        }
    }
    else
    {
        qDebug() << "现在是[enemy]回合，将执行enemy: " << pair.first << "对player: " << pair.second << "的攻击行动";
        emit AddInfo("[enemy]驱使" + m_enemyServentCardList[pair.second - 1]->getName() + "对player的" + m_playerServentCardList[pair.first - 1]->getName() + "发动了攻击");

        m_playerServentCardList[pair.first - 1]->setHP(m_playerServentCardList[pair.first - 1]->getHP() - m_enemyServentCardList[pair.second - 1]->getATK());
        if(m_playerServentCardList[pair.first - 1]->getHP() <= 0)
        {
            qDebug() << "player的第: " << pair.first << "号从者阵亡了";
            emit AddInfo("player的" + m_playerServentCardList[pair.first - 1]->getName() + "阵亡了");

            m_playerServentCardList[pair.first - 1]->setHP(0);
            m_playerServentCardList[pair.first - 1]->setAlive(false);
            m_playerServentCardList[pair.first - 1]->setEnabled(false);
            qDebug() << "设置完false";
        }
    }
    emit ImplTurn();
}

void MainWindow::ImplementTurn()
{
    if(m_gameset)
        return;

    m_turn = !m_turn;
    if(m_turn)
    {   // player回合: 启用player、禁用enemy
        ui->dial->setValue(100);
        ui->dial->setStyleSheet("background-color: rgb(255, 255, 0);");

        foreach (const QVariant& variant, m_playerList) {
            QWidget* widget = qvariant_cast<QWidget*>(variant);
            if (widget) {
                widget->setEnabled(true);
            }
        }
        foreach (const QVariant& variant, m_enemyList) {
            QWidget* widget = qvariant_cast<QWidget*>(variant);
            if (widget) {
                widget->setEnabled(false);
            }
        }
        bool isAllDie = true;
        for (int i = 0; i < m_playerServentCardList.count(); ++i) {
            if(m_playerServentCardList[i]->getAlive() == false)
            {   // 找到一张已阵亡的servent，重新设置回false
                m_playerServentCardList[i]->setEnabled(false);
            }
            else
                isAllDie = false;
        }
        if(isAllDie)
        {   // servent全部阵亡，master设为true，否则false
            player->setEnabled(true);
        }
        else
        {
            player->setEnabled(false);
        }
    }
    else
    {   // enemy回合: 启用enemy、禁用player
        ui->dial->setValue(50);
        ui->dial->setStyleSheet("background-color: rgb(255, 170, 255);");
        foreach (const QVariant& variant, m_enemyList) {
            QWidget* widget = qvariant_cast<QWidget*>(variant);
            if (widget) {
                widget->setEnabled(true);
            }
        }
        foreach (const QVariant& variant, m_playerList) {
            QWidget* widget = qvariant_cast<QWidget*>(variant);
            if (widget) {
                widget->setEnabled(false);
            }
        }
        bool isAllDie = true;
        for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
            if(m_enemyServentCardList[i]->getAlive() == false)
                m_enemyServentCardList[i]->setEnabled(false);
            else
                isAllDie = false;
        }
        if(isAllDie)
            enemy->setEnabled(true);
        else
            enemy->setEnabled(false);
    }
    // 更新回合数
    m_totalTurns--;
    ui->lcd_countDown->display(m_totalTurns);
    if(m_totalTurns == 0)
    {
        // 回合数结束，无尽模式，重置回合数状态
        if(m_isNoEnd)
            m_totalTurns = 9999;
        // 否则，游戏结束
        emit GameSet(TimeOut);
    }
}

void MainWindow::ImplementGameSet(GameOverStat stat)
{
    qDebug() << "游戏结束";
    m_gameset = true;
    ui->btn_restart->setEnabled(true);

    QString victor = "";
    int playerRemainHP = 0, enemyRemainHP = 0;
    switch(stat)
    {
    case TimeOut:
        emit AddInfo("回合数结束，游戏结束");
        // 回合结束统计血量，只统计servent，master不包括在内
        for (int i = 0; i < m_playerServentCardList.count(); ++i) {
            if(m_playerServentCardList[i]->getAlive())
                playerRemainHP += m_playerServentCardList[i]->getHP();
        }
        for (int i = 0; i < m_enemyServentCardList.count(); ++i) {
            if(m_enemyServentCardList[i]->getAlive())
                enemyRemainHP += m_enemyServentCardList[i]->getHP();
        }
        if(playerRemainHP > enemyRemainHP)
        {
            victor = "player";
        }
        else if(playerRemainHP < enemyRemainHP)
        {
            victor = "enemy";
        }
        else
        {
            victor = "平局";
        }
        break;
    case GameOver:
        if(m_turn)
        {   // player回合，master被打败：player获胜
            victor = "player";
            emit AddInfo("[enemy]的master已被击败，游戏结束");
        }
        else
        {   // enemy回合，master被打败：enemy获胜
            victor = "enemy";
            emit AddInfo("[player]的master已被击败，游戏结束");
        }
        break;
    }

    lab_gameset = new QLabel(this);
    lab_gameset->setGeometry(280, 200, 700, 250);
    lab_gameset->setAlignment(Qt::AlignHCenter);
    lab_gameset->setStyleSheet("QLabel {"
                               "background-color: rgba(238, 130, 238, 127);"
                               "color: red;"
                               "border-radius: 5px;"
                               "border: 2px solid red;"
                               "font-size: 60px;"
                               "}");
    lab_gameset->setText("游戏结束\n胜者:" + victor);
    lab_gameset->show();

    // 禁用后面所有的控件
    foreach (const QVariant& variant, m_playerList) {
        QWidget* widget = qvariant_cast<QWidget*>(variant);
        if (widget) {
            widget->setEnabled(false);
        }
    }
    foreach (const QVariant& variant, m_enemyList) {
        QWidget* widget = qvariant_cast<QWidget*>(variant);
        if (widget) {
            widget->setEnabled(false);
        }
    }
}

void MainWindow::ImplementAddInfo(QString message)
{
    qDebug() << message;
    ui->textEdit->append(message);
}

void MainWindow::ImplementUpdateItemCard(int itemId)
{
    ItemCard* card;
    if(m_turn)
    {
        card = m_playerItemCardList[itemId - 1];
        emit AddInfo("[player]对" + m_playerServentCardList[m_serventId - 1]->getName() +
                     "使用道具牌-" + card->getStatus().getDescription());
    }
    else
    {
        card = m_enemyItemCardList[itemId - 1];
        emit AddInfo("[enemy]对" + m_enemyServentCardList[m_serventId - 1]->getName() +
                     "使用道具牌-" + card->getStatus().getDescription());
    }
    Status s = m_tool->getOneRandomStatus();
    qDebug() << "更新道具牌: 新生成的道具牌为：" << s.getDescription();

    card->setStatus(s);
    card->drawCard();
}

void MainWindow::on_btn_cnt_clicked()
{
    bool ok = false;
    int inputCnt = ui->lineEdit->text().toInt(&ok);
    if(!ok)
    {
        QMessageBox::warning(this, "警告", "请输入正确的不小于20的数字");
        return;
    }
    else if(inputCnt < 20)
    {
        QMessageBox::warning(this, "警告", "输入的数字过小，请输入不小于20的数字");
        return;
    }
    m_totalTurns = inputCnt + 1;
    m_backupTurns = m_totalTurns;
    GameStart();
}


void MainWindow::on_btn_noend_clicked()
{
    m_isNoEnd = true;
    m_totalTurns = 9999;
    m_backupTurns = m_totalTurns;
    GameStart();
}


void MainWindow::on_btn_restart_clicked()
{
    // 已存在的控件都删除重建
    lab_gameset->setVisible(false);
    lab_gameset = NULL;
    foreach(const QVariant& variant, m_playerList)
    {
        QWidget* widget = qvariant_cast<QWidget*>(variant);
        if (widget) {
            widget = NULL;
        }
    }
    foreach(const QVariant& variant, m_enemyList)
    {
        QWidget* widget = qvariant_cast<QWidget*>(variant);
        if (widget) {
            widget = NULL;
        }
    }
    m_playerList.clear();
    m_playerItemCardList.clear();
    m_playerServentCardList.clear();

    m_enemyList.clear();
    m_enemyItemCardList.clear();
    m_enemyServentCardList.clear();

    ui->textEdit->clear();

    m_totalTurns = m_backupTurns;

    m_gameset = false;

    ui->btn_restart->setEnabled(false);

    GameStart();
}

void MainWindow::on_btn_about_clicked()
{
    QMessageBox::information(this, "关于", "关于游戏的说明："
                                           "\n1、一共三种类型的牌: 道具牌、Servent、Master"
                                           "\n2、Servent牌左上角是攻击值，右上角是血量"
                                           "\n3、Master牌左上角是血量，攻击值默认锁死要么1要么2"
                                           "\n4、当Servent全部阵亡后才可选择Master"
                                           "\n5、点击选中后会有红色边框显示"
                                           "\n6、中间的标志指明了回合方"
                                           "\n7、下面的是[player]上面的是[enemy]"
                                           "\n8、默认先手是[player]"
                                           "\n9、道具牌只可作用与己方的Servent身上"
                                           "\n10、游戏结束有两种方式：回合数到或Master阵亡"
                                           "\n11、回合数到时Servent总和血量多的一方获胜"
                                           "\n");
}


void MainWindow::on_btn_character_clicked()
{
    QMessageBox::information(this, "角色名对照", "卡牌名\t对应角色名\t作品"
                                                 "\nElysia\t爱莉希雅\t《崩坏三》"
                                                 "\nPhiliaGrey\t菲莉亚·格雷\t《星之终途》"
                                                 "\nAmane\t谷风天音\t《天使☆嚣嚣 RE-BOOT!》"
                                                 "\nArte\t怪盗阿尔蒂\t《Ambitious mission》"
                                                 "\nNoa\t白雪乃爱\t《天使☆嚣嚣 RE-BOOT!》"
                                                 "\nKurumi\t小云雀来海\t《天使☆嚣嚣 RE-BOOT!》"
                                                 "\nKotose\t琴濑\t《不败世界与终焉之花》"
                                                 "\nYae\t石川弥荣\t《Ambitious mission》"
                                                 "\nTsubaki\t朱雀院椿\t《牵绊闪耀的恋之伊吕波》"
                                                 "\nNishikiAsumi\t锦 亚澄\t《灵感满溢的甜蜜创想》"
                                                 "\nShio\t镰仓诗樱\t《灵感满溢的甜蜜创想》"
                                                 "\n");
}

