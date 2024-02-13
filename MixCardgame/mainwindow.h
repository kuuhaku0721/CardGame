#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QList>
#include <QVariantList>
#include <QLabel>
#include <QPalette>
#include <QMessageBox>

#include "itemcard.h"
#include "serventcard.h"
#include "generatetool.h"
#include "mastercard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum GameOverStat
    {
        TimeOut,
        GameOver
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void GenerateItemCards();
    void GenerateServentCards();
    void GenerateMasterCards();

signals:
    void ImplBuff(int itemId, int serventId);
    void ImplAttack(QPair<int, int> pair);
    void ImplTurn();
    void ImplUpdateCard(int itemId);
    void GameSet(GameOverStat stat);
    void AddInfo(QString message);

private slots:

    void ChangeItemCardState(QPair<int, bool> pair);

    void ChangeServentCardState(QPair<int, bool> pair, bool owner);

    void ChangeMasterCardState(bool selected);

    void ImplementBuff(int itemId, int serventId);

    void ImplementAttack(QPair<int, int> pair);

    void ImplementTurn();

    void ImplementGameSet(GameOverStat stat);

    void ImplementAddInfo(QString message);

    void ImplementUpdateItemCard(int itemId);

    void on_btn_cnt_clicked();

    void on_btn_noend_clicked();

    void on_btn_restart_clicked();

    void on_btn_about_clicked();

    void on_btn_character_clicked();

private:
    void Init();
    void GameStart();

private:
    Ui::MainWindow *ui;

    bool m_turn;                    // 回合方，true代表player(下)，false代表enemy(上)
    int m_totalTurns;               // 总的回合数
    int m_backupTurns;              // 备份回合数，重开用
    bool m_gameset;                 // 游戏结束的标志
    bool m_isNoEnd;                 // 是否以无尽模式启动游戏

    bool m_isCardSelected;          // 道具牌是否被选中
    int m_itemId;                   // 选中的是哪一个
    bool m_isServentSelected;       // servent是否被选中
    int m_serventId;                // 选中的哪个
    bool m_isMasterSelected;        // master是否被选中
    QPair<int, int> m_attackPair;   // 执行攻击行为的双方，first为player，second为enemy

    GenerateTool* m_tool;
    QList<Status*> m_totalStatus;

    QLabel* lab_gameset;            // 结束时显示的标签

    QVariantList m_playerList;      // 存储所有player方对象的集合
    QVariantList m_enemyList;       // 存储所有enemy方对象的集合
    QList<ItemCard*> m_playerItemCardList;
    QList<ItemCard*> m_enemyItemCardList;
    QList<ServentCard*> m_playerServentCardList;
    QList<ServentCard*> m_enemyServentCardList;
    QList<MasterCard*> m_MasterCardList;

    // 道具牌
    ItemCard* player_card1;
    ItemCard* player_card2;
    ItemCard* player_card3;
    ItemCard* player_card4;
    ItemCard* player_card5;
    ItemCard* enemy_card1;
    ItemCard* enemy_card2;
    ItemCard* enemy_card3;
    ItemCard* enemy_card4;
    ItemCard* enemy_card5;

    // 侍从牌
    ServentCard* player_servent1;
    ServentCard* player_servent2;
    ServentCard* player_servent3;
    ServentCard* enemy_servent1;
    ServentCard* enemy_servent2;
    ServentCard* enemy_servent3;

    // 角色牌
    MasterCard* player;
    MasterCard* enemy;

};
#endif // MAINWINDOW_H
