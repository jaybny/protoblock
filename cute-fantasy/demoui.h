#ifndef DEMOUI_H
#define DEMOUI_H

#include <QWidget>
#include <QThread>
#include <QString>

#include <ProtoData.pb.h>


#include "teamsloader.h"
#include "playerloader.h"
#include "spinboxdelegate.h"
#include "models.h"
#include "scheduleloader.h"

namespace Ui {
class DemoUI;
}

class DemoUI : public QWidget
{
    Q_OBJECT
    enum State { CONNECTING, LIVE };
    InData indata{};
    bool first = true;
public:
    explicit DemoUI(QWidget *parent = 0);
    ~DemoUI();
public slots:
    void fromServer(const DeltaData &in);
    void refreshViews(const DeltaData &in);
signals:
    void onClose();
    void fromGUI(const InData &);

protected:
    virtual void closeEvent(QCloseEvent *){ emit onClose();}

private slots:
    void on_mySendProjectionsButton_clicked();

    void on_myDeleteAllRowsButton_clicked();

    void on_generate_clicked();

private:
    Ui::DemoUI *ui;
    void updatesnap();
    void updatedelta();
    /**
     * @brief myCurrentSnapShot : contains last snapshot data
     */
    SnapShotViewModel myCurrentSnapShot;
    //the following models will hold data shown by the table views.
    TeamStateTableModel myTeamsStateTableModel;
    PlayerDataTableModel myPlayerDataTableModel;
    TeamDataTableModel myTeamDataTableModel;
    FantasyPlayerTableModel myFantasyPlayerTableModel;
    QList<GameProjectionTableModel *> myGameProjectionTableModels;
    QList<TeamLoader::JsonTeam> myPreloadedTeams;
    QList<PlayerLoader::JsonPlayer> myPreloadedPlayers;
    QList<ScheduleLoader::JsonSchedule> myPreloadedSchedule;
    QList<QString> myTeamTransitions;
    SpinBoxDelegate myDelegate;
};

#endif // DEMOUI_H
