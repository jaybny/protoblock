#ifndef TESTINGWINDOW_H
#define TESTINGWINDOW_H

#include <QMainWindow>
#include "ProtoData.pb.h"
#include <unordered_map>
#include "Data.h"

namespace Ui {
class TestingWindow;
}
using fantasybit::GlobalState;
using namespace fantasybit;
using namespace std;

class MainLAPIWorker;
class TestingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestingWindow(QWidget *parent = 0);
    ~TestingWindow();

    void initialize();


signals:
    void UseMyFantasyName(QString);
    void BeOracle();
    void ClaimFantasyName(QString);

public slots:
    void GoLive(GlobalState);
    void OnNameStatus(MyFantasyName);
    void OnMyFantasyNames(vector<MyFantasyName> &);
    void OnNewWeek(int);

private slots:
    void on_beoracle_clicked();

    void on_weeks_activated(int index);

    void on_SendBlock_clicked();

    void on_claimname_clicked();

    void on_GetTx_clicked();

    //void on_game_currentIndexChanged(int index);

    void on_game_activated(const QString &arg1);

    //void on_game_activated(const QString &arg1);

    void on_player_activated(const QString &arg1);

    void on_team_activated(const QString &arg1);

    void on_GetGameResult_clicked();

private:
    MainLAPIWorker *  myCoreInstance;
    std::unordered_map<string,GameInfo> mGames;
    std::unordered_map<string,GameResult> mGameResult;
    std::unordered_map<string,GameRoster> mGameRoster;
    std::unordered_map<string,PlayerDetail> mPlayerDetail;

    std::unordered_map<string,GameResult> mStagedGameResult;


    std::unordered_map<string,::google::protobuf::RepeatedPtrField< ::fantasybit::FantasyBitAward>>
    mRewards;

    std::unordered_map<string,PlayerResult>
    mResult;

    int realweek() ;

    Ui::TestingWindow *ui;
};

#endif // TESTINGWINDOW_H
