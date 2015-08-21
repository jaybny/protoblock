#include "LAPIWorker.h"


#include <QWaitCondition>
#include "RestFullCall.h"
#include "globals.h"
#include <algorithm>
#include "ProtoData.pb.h"
#include "core.h"
#include <vector>
#include "Commissioner.h"

using namespace std;
using namespace fantasybit;

MainLAPIWorker::MainLAPIWorker(QObject * parent):  QObject(parent),
    data{}, namedata{}, processor(data,namedata)
{
    timer = new QTimer(this);
    node.thread()->connect(node.thread(),
                           SIGNAL(started()),
                           node.object(),
                           SLOT(init()));
    myNodeWorker = node.object();
    node.thread()->start();
    QObject::connect(myNodeWorker,SIGNAL(InSync(int)),this,SLOT(OnInSync(int)));
    QObject::connect(myNodeWorker,SIGNAL(SeenBlock(int)),this,SLOT(OnSeenBlock(int)));
    //QObject::connect(this,SIGNAL(Timer()),myNodeWorker,SLOT(TryNext()));
    QObject::connect(this,SIGNAL(ProcessNext()),this,SLOT(ProcessBlock()));
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(Timer()));
    QObject::connect(this,SIGNAL(GetNext()),myNodeWorker,SLOT(TryNext()));
    //QObject::connect(this,SIGNAL(GetNext()),qApp,SLOT(aboutQt()));
    //QObject::connect(timer,SIGNAL(timeout()),myNodeWorker,SLOT(Timer()));
    QObject::connect(this,SIGNAL(Live(bool)),&data,SLOT(OnLive(bool)));
    QObject::connect(this,SIGNAL(Live(bool)),&namedata,SLOT(OnLive(bool)));
    QObject::connect(this,SIGNAL(Live(bool)),&processor,SLOT(OnLive(bool)));
    QObject::connect(&processor,SIGNAL(WeekOver(int)),&data,SLOT(OnWeekOver(int)));
    QObject::connect(&processor,SIGNAL(WeekStart(int)),&namedata,SLOT(OnWeekStart(int)));
    QObject::connect(this,SIGNAL(WeekStart(int)),&data,SLOT(OnWeekStart(int)));

    QObject::connect(&data,SIGNAL(PlayerChange(std::string)),
                     this,SLOT(OnPlayerChange(std::string)));

    QObject::connect(&data,SIGNAL(TeamPlus(std::string ntid,std::string)),
                     this,SLOT(OnTeamPlus(std::string ntid,std::string )));

    QObject::connect(&data,SIGNAL(TeamMinus(std::string ntid,std::string )),
                     this,SLOT(OnTeamMinus(std::string ntid,std::string )));

    QObject::connect(&data,SIGNAL(GameStart(std::string)),
                     this,SLOT(OnGameStart(std::string)));

    QObject::connect(&data,SIGNAL(GlobalStateChange(GlobalState)),
                     this,SLOT(OnGlobalStateChange(GlobalState)));

    QObject::connect(&namedata,SIGNAL(FantasyNameFound(std::string)),
                     this,SLOT(OnFoundName(std::string)));

    QObject::connect(&data,SIGNAL(ProjectionLive(FantasyBitProj)),
                     this,SLOT(OnProjLive(FantasyBitProj)));

    QObject::connect(&data,SIGNAL(FantasyNameBalance(FantasyNameBal)),
                     this,SLOT(OnNameBal(FantasyNameBal)));

}

void MainLAPIWorker::GoLive() {
    numto = 0;
    intervalstart = 500;
    timer->start(intervalstart);

    OnGetMyNames();
    /*
    //ToDo: convert names with a status OnLive()
    myfantasynames = agent.getMyNamesStatus();
    for(auto p : myfantasynames) {
        if ( p.second.status() < MyNameStatus::confirmed )
            namedata.Subscribe(p.first);

        deltadata.add_myfantasyname()->CopyFrom(p.second);
    }
    deltadata.mutable_globalstate()->CopyFrom(data.GetGlobalState());
    */
    emit OnLive();
    emit SubscribeLive();

}

void MainLAPIWorker::processGUIRequest(const QVariant & requestData){
    //GUI sent us a request process it
    //  processing requestData
    //and then reply back a kind of result
    /*
        if (requestData.type()== QVariant::String){
            if (requestData.toString()=="PING")
                emit sendNotificationWithData(QString("PONG"));
        }
        */
}

void MainLAPIWorker::getLivePlayers(int week){
    if ( amlive ) {
        auto allgames = data.GetLiveWeekGameRosters();
        //emit sendNotificationWithData(allgames);
    }
    /*
    QUrl url("http://api.nfldata.apiphany.com/nfl/v2/JSON/AreAnyGamesInProgress");
    RestfullCall rest;
    rest.moveToThread(QThread::currentThread());
    rest.restFullSynchrounousCallGet(url,"","");
    */
}

void MainLAPIWorker::startPoint(){
    qDebug("Main Core Thread started");   
    last_block = processor.init();
    if ( last_block < 0 ) {
        //emit OnError();
        last_block = 0;
    }   

    intervalstart = 5000;
    timer->start(intervalstart);
}

void MainLAPIWorker::OnInSync(int num) {
    numto = num;
    intervalstart = 2000;
    emit ProcessNext();
}

void MainLAPIWorker::ProcessBlock() {
    auto b = fantasybit::Node::getLocalBlock(last_block+1);
    if (!b) {
        //emit OnError();
        return;
    }
    if ( !Process(*b) ) return;

    count = pcount = 0;
    if ( !amlive && last_block < numto )
        emit ProcessNext(); //catching up
    else {
        doNewDelta();
        if ( !amlive ) {
            amlive = true;
            GoLive();
        }
    }
}

void MainLAPIWorker::OnSeenBlock(int num) {
    if (amlive)
        numto = num;
    timer->start(intervalstart);
    count = bcount = 0;
}

void MainLAPIWorker::Timer() {
    bcount++;
    pcount++;
    if ( !amlive ) {
        emit ProcessNext();
        if ( bcount > 10 && pcount < 2)
            emit GetNext();
        else if ( bcount < 3 && numto < std::numeric_limits<int>::max())
            emit GetNext();
    }
    else if ( numto > last_block ) {
        emit ProcessNext();
        if ( bcount < 3)
            emit GetNext();
    }
    else {
        count++;
        emit GetNext();
        emit ProcessNext();
        int interval = std::min(intervalmax,count*intervalstart);
        timer->start(interval);
    }

}

bool MainLAPIWorker::Process(fantasybit::Block &b) {
    int last = processor.process(b);
    if ( last == -1 ) {
        //emit OnError();
        timer->start(5000);
        return false;
    }
    if ( last != last_block+1) {
        //emit OnError
        //should never be here
        return false;
    }

    last_block = last;
    return true;
}

void MainLAPIWorker::doNewDelta() {
    //auto deltasnap = processor.GetandClear();
    //qDebug(deltasnap.DebugString().c_str());
    //emit OnData(deltasnap);
}

void MainLAPIWorker::OnPlayerChange(std::string) {}

void MainLAPIWorker::OnFoundName(std::string &name) {
    auto it = myfantasynames.find(name);
    if ( it != end(myfantasynames)) {
        it->second.set_status(MyNameStatus::confirmed);
        emit NameStatus(it->second);
    }
}

void MainLAPIWorker::OnProjLive(fantasybit::FantasyBitProj &proj) {
    emit LiveProj(proj);
}

void MainLAPIWorker::OnNameBal(fantasybit::FantasyNameBal &) {}

void MainLAPIWorker::OnGetMyNames() {
    vector<MyFantasyName> my;
    myfantasynames = agent.getMyNamesStatus();
    for(auto p : myfantasynames) {
        if ( !amlive )
        if ( p.second.status() < MyNameStatus::confirmed )
            namedata.Subscribe(p.first);

        my.push_back(p.second);
    }

    emit OnMyNames(my);
}

void MainLAPIWorker::OnUseName(QString name) {
    myCurrentName.set_name(name.toStdString());
    myCurrentName.set_status(MyNameStatus::none);


    auto it = myfantasynames.find(name.toStdString());
    if ( it == end(myfantasynames)) {
        myfantasynames = agent.getMyNamesStatus();
        it = myfantasynames.find(name.toStdString());
    }

    if ( it != end(myfantasynames)) {
        if ( agent.UseName(myCurrentName.name()) ) {
            myCurrentName = it->second;
        }
    }

    if ( myCurrentName.status() < MyNameStatus::confirmed)
        namedata.Subscribe(myCurrentName.name());

    emit NameStatus(myCurrentName);
}

void MainLAPIWorker::OnClaimName(QString name) {
    if ( !amlive ) return;

    myCurrentName.set_name(name.toStdString());
    myCurrentName.set_status(MyNameStatus::none);

    auto ret = agent.signPlayer(name.toStdString());

    switch ( ret ) {
        case FantasyAgent::AVAIL:
            myCurrentName.set_status(MyNameStatus::requested);
        break;
        case FantasyAgent::NOTAVAILABLE:
            myCurrentName.set_status(MyNameStatus::notavil);
        break;
        case FantasyAgent::OWNED:
            myCurrentName.set_status(MyNameStatus::confirmed);
        break;
    }

    if ( myCurrentName.status() == MyNameStatus::requested)
        namedata.Subscribe(myCurrentName.name());

    emit NameStatus(myCurrentName);
}

void MainLAPIWorker::OnProjTX(FantasyBitProj inp) {
    if ( !amlive ) return;

    if ( !agent.HaveClient() ) return;

    ProjectionTrans pj{};
    pj.set_playerid(inp.playerid());
    pj.set_points(inp.proj());

    auto gs = data.GetGlobalState();
    pj.set_week(gs.week());
    pj.set_season(gs.season());

    Transaction trans{};
    trans.set_version(Commissioner::TRANS_VERSION);
    trans.set_type(TransType::PROJECTION);
    trans.MutableExtension(ProjectionTrans::proj_trans)->CopyFrom(pj);
    SignedTransaction sn = agent.makeSigned(trans);
    agent.onSignedTransaction(sn);

    namedata.Subscribe(myCurrentName.name());

}

