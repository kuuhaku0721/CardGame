#ifndef GENERATETOOL_H
#define GENERATETOOL_H

#include "master.h"
#include "servent.h"
#include "status.h"
#include <QSet>
#include <QRandomGenerator>

class GenerateTool
{
public:
    GenerateTool();
    ~GenerateTool();

public:
    QList<Status> getStatus();
    Status getOneRandomStatus();
    QList<Servent> getServent();
    QList<Master> getMaster();
    void AddStatus();
    void AddServent();
    void AddMaster();

protected:
    void GeneratrStatus();
    void GeneratrServent();
    void GenerateMaster();

private:
    int m_itemCnt = 5;
    int m_serventCnt = 3;
    QList<Status> m_listStatus;
    QList<Servent> m_listServent;
    QList<Master> m_listMaster;
};

#endif // GENERATETOOL_H
