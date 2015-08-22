#ifndef LAPIWORKER_H
#define LAPIWORKER_H

#include "globals.h"
#include <QTimer.h>
#include "threadedqobject.h"
#include "NodeWorker.h"
#include "FantasyAgent.h"
#include "Processor.h"
#include "FantasyAgent.h"
#include "NameData.h"
#include "Data.h"
#include "NameData.pb.h"
#include "StaticData.pb.h"
#include "StatusData.pb.h"
#include "ProtoData.pb.h"
#include <vector>
#include "iresolvable.h"

class MainLAPIWorker : public QObject , public IResolvable
{
    Q_OBJECT

    int intervalmax = 60000;
    int intervalstart = 500;
    int bcount =0;
    int pcount =0;
    int count =0;
    int last_block=0;
    NodeWorker *myNodeWorker;
    int numto = std::numeric_limits<int>::max();
    bool amlive = false;
    QTimer * timer;
    fantasybit::FantasyAgent agent{};
    fantasybit::NFLStateData data;
    fantasybit::FantasyNameData namedata;
    fantasybit::BlockProcessor processor;

    fantasybit::DeltaData deltadata{};
    std::map<std::string,fantasybit::MyFantasyName> myfantasynames{};
    fantasybit::MyFantasyName myCurrentName{};
public:
    MainLAPIWorker(QObject * parent=0);
    ~MainLAPIWorker(){}
    ThreadedQObject<NodeWorker> node;

    fantasybit::NFLStateData &NFLState() { return data; }

    fantasybit::FantasyNameData &NameData() { return namedata; }

    /*
    std::vector<fantasybit::GameRoster> getWeekGameRosters(int week){
        std::vector<fantasybit::GameRoster> vector;
        vector.push_back(fantasybit::GameRoster());
        return vector;
    }
    */
    void GoLive();

signals:

    //void OnData(const fantasybit::DeltaData &);
    //void sendNotificationWithData(const QVariant & notificationData);
    //sync blocks
    void ProcessNext();
    void GetNext();

    //to data
    void SubscribeLive();


    //to GUI
    void NameStatus(const fantasybit::MyFantasyName &);
    void LiveProj(fantasybit::FantasyBitProj &);
    void MyNames(std::vector<fantasybit::MyFantasyName> &);
    void NameBalance(fantasybit::FantasyNameBal &);
    void PlayerStatusChange(std::pair<std::string,fantasybit::PlayerStatus> &in);
    void OnGlobalState(fantasybit::GlobalState);
    void Live(bool);

public slots:

    //void getLivePlayers(int );
    //void processGUIRequest(const QVariant & requestData);

    void startPoint();

    void OnInSync(int num);
    void ProcessBlock();
    void OnSeenBlock(int num);
    void Timer();

    //void OnPlayerChange(std::string);

    //from gui
    void OnGetMyNames();
    void OnUseName(QString);

    //tx
    void OnFoundName(std::string &);
    void OnProjLive(fantasybit::FantasyBitProj &);
    void OnClaimName(QString);
    void OnProjTX(fantasybit::FantasyBitProj);

    //data
    void OnGlobalStateChange(fantasybit::GlobalState);
    void OnNameBal(fantasybit::FantasyNameBal &);
    void OnPlayerStatusChange(std::pair<std::string,fantasybit::PlayerStatus>);
private:

    bool Process(fantasybit::Block &b);

    //void doNewDelta();

};


#endif // LAPIWORKER_H
