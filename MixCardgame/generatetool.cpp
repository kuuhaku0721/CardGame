#include "generatetool.h"

GenerateTool::GenerateTool()
{
    GeneratrStatus();
    GeneratrServent();
    GenerateMaster();
}

GenerateTool::~GenerateTool() {}

QList<Status> GenerateTool::getStatus()
{
    QList<Status> result;
    QSet<int> randomNumbers;
    while (randomNumbers.size() < 5)
    {
        int randomNumber = QRandomGenerator::global()->bounded(0, m_listStatus.count());
        if (!randomNumbers.contains(randomNumber))
        {
            randomNumbers.insert(randomNumber);
        }
    }
    for (int i : randomNumbers) {
        result.append(m_listStatus[i]);
    }
    return result;
}

Status GenerateTool::getOneRandomStatus()
{
    int randomNumber = QRandomGenerator::global()->bounded(0, m_listStatus.count());
    return m_listStatus[randomNumber];
}

QList<Servent> GenerateTool::getServent()
{
    QList<Servent> result;
    QSet<int> randomNumbers;
    while (randomNumbers.size() < 3)
    {
        int randomNumber = QRandomGenerator::global()->bounded(0, m_listServent.count());
        if (!randomNumbers.contains(randomNumber))
        {
            randomNumbers.insert(randomNumber);
        }
    }
    for (int i : randomNumbers) {
        result.append(m_listServent[i]);
    }
    return result;
}

QList<Master> GenerateTool::getMaster()
{
    QList<Master> result;
    QSet<int> randomNumbers;
    while (randomNumbers.size() < 2)
    {
        int randomNumber = QRandomGenerator::global()->bounded(0, m_listMaster.count());
        if (!randomNumbers.contains(randomNumber))
        {
            randomNumbers.insert(randomNumber);
        }
    }
    for (int i : randomNumbers) {
        result.append(m_listMaster[i]);
    }
    return result;
}

// 如果想要添加新的牌，请在此添加
// TODO：如果后续数量多的话，可以换成本地json格式文件存储的形式，启动时从文件中读取出来
void GenerateTool::GeneratrStatus()
{
    // 基础牌 参数说明：描述文字、攻击值、生命值
    Status s1("[普通牌]攻击+1", 1, 0, NORMAL);
    Status s2("[普通牌]生命+1", 0, 1, NORMAL);
    Status s3("[普通牌]攻击+2 生命+1", 2, 1, NORMAL);
    Status s4("[普通牌]攻击-1 生命+3", -1, 3, NORMAL);
    Status s5("[置换牌]攻击-5 生命+5", -5, 5, NORMAL);
    Status s6("[置换牌]攻击+5 生命-5", 5, -5, NORMAL);
    Status s7("[隐藏牌]攻击+3 生命+3", 3, 3, NORMAL);
    Status s8("[隐藏牌]攻击-2 生命+4", -2, 4, NORMAL);
    Status s9("[隐藏牌]攻击+5", 5, 0, NORMAL);
    Status s10("[自杀牌]生命-20", 0, -20, NORMAL);
    Status s11("[普通牌]攻击-3 生命+1", -3, 1, NORMAL);
    Status s12("[普通牌]攻击+4 生命-1", 4, -1, NORMAL);
    Status s13("[厄运牌]攻击-5", -2, 0, NORMAL);
    Status s14("[厄运牌]攻击-2 生命-2", -2, -2, NORMAL);
    Status s15("[厄运牌]攻击-3 生命-1", -3, -1, NORMAL);
    Status s16("[幸运牌]生命+5", 0, 5, NORMAL);
    Status s17("[幸运牌]攻击+3 生命+3", 3, 3, NORMAL);
    Status s18("[编不出来牌]", 1, 1, NORMAL);
    Status s19("[编不出来牌]", 1, 1, NORMAL);
    Status s20("[编不出来牌]", 1, 1, NORMAL);
    // 效果牌                  TODO：等待设计实现

    m_listStatus << s1 << s2 << s3 << s4 << s5 << s6 << s7 << s8
                 << s9 << s10 << s11 << s12 << s13 << s14 << s15 << s16
                 << s17 << s18 << s19 << s20;
}

void GenerateTool::GeneratrServent()
{
    // 参数说明：从者名，攻击，生命
    Servent s1("Elysia", 6, 25);
    Servent s2("PhiliaGrey", 7, 15);
    Servent s3("Amane", 5, 18);
    Servent s4("Arte", 2, 30);
    Servent s5("noa", 5, 15);
    Servent s6("Kurumi", 7, 30);
    Servent s7("Kotose", 4, 18);
    Servent s8("Yae", 7, 15);
    Servent s9("Tsubaki", 6, 25);
    Servent s10("NishikiAsumi", 3, 18);
    Servent s11("Shio", 4, 20);
    m_listServent << s1 << s2 << s3 << s4 << s5 << s6
                  << s7 << s8 << s9 << s10 << s11;
}

void GenerateTool::GenerateMaster()
{
    // 参数说明: 角色名、攻击、生命、头像路径
    Master m1("futiya", 1, 20);
    Master m2("me", 2, 10);
    Master m3("lifu", 1, 15);
    Master m4("box", 1, 10);
    m_listMaster << m1 << m2 << m3 << m4;
}
