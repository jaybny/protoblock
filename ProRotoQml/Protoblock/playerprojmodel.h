#ifndef PLAYERPROJMODEL_H
#define PLAYERPROJMODEL_H

#include <QObject>
#include <QString>
#include "../QmlSupermacros/QQmlConstRefPropertyHelpers.h"
#include "../QmlModels/QQmlObjectListModel.h"
#include "../QmlSupermacros/QQmlVarPropertyHelpers.h"

#include "StateData.pb.h"
#include "globals.h"
#include <unordered_map>
#include <QStringListModel>

#include <QtCore/qsortfilterproxymodel.h>

#include "sortfilterproxymodel.h"
#include "fbutils.h"
#include "pbgateways.h"

namespace pb {
using namespace fantasybit;


class PlayerProjModelItem : public QObject {
    Q_OBJECT
    QML_READONLY_CSTREF_PROPERTY (QString, fullname)
    QML_READONLY_CSTREF_PROPERTY (QString, lastname)
    QML_READONLY_CSTREF_PROPERTY (QString, firstname)
    QML_READONLY_CSTREF_PROPERTY (QString, pos)
    QML_READONLY_CSTREF_PROPERTY (QString, teamid)
    QML_READONLY_CSTREF_PROPERTY (int, status)
    QML_READONLY_CSTREF_PROPERTY (QString, playerid)
    QML_WRITABLE_VAR_PROPERTY(int, projection)
    QML_WRITABLE_VAR_PROPERTY (int, knownProjection)
    QML_WRITABLE_VAR_PROPERTY (int, projectionStatus)
    QML_READONLY_CSTREF_PROPERTY (QString, gameid)
    QML_READONLY_CSTREF_PROPERTY ( bool, isopen)
    QML_WRITABLE_VAR_PROPERTY (int, avg)
    QML_WRITABLE_VAR_PROPERTY (int, fname1)
    QML_WRITABLE_VAR_PROPERTY (int, fname2)
    QML_WRITABLE_VAR_PROPERTY (int, fname3)
    QML_WRITABLE_VAR_PROPERTY (int, fname4)
    QML_WRITABLE_VAR_PROPERTY (int, fname5)

public:

    explicit PlayerProjModelItem(const fantasybit::PlayerDetail &pd, const std::string &teamid,
                                 const std::string &playerid, const QString &gameid,
                                 int avg,
                                 bool gameopen,
                                 QObject *parent = nullptr) :  QObject(parent) {
        m_fullname =  QString("%1 %2")
                .arg ( pd.base.first ().data () )
                .arg ( pd.base.last ().data () );
        m_firstname = pd.base.first().data();
        m_lastname = pd.base.last().data();
        m_pos = pd.base.position().data();
        m_teamid = teamid.data();
        m_status = pd.team_status;
        m_playerid = playerid.data();
        m_gameid = gameid;
        m_projection = 0;
        m_knownProjection = 0;
        m_fname1 = 0;
        m_fname2 = 0;
        m_fname3 = 0;
        m_fname4 = 0;
        m_fname5 = 0;
        m_isopen = gameopen;
        set_avg(avg);
//        qDebug() << " PlayerProjModelItem"  << pd.base.DebugString().data() << teamid.data() << m_playerid.data();
    }
};

class PlayerProjModel : public QQmlObjectListModel<PlayerProjModelItem>{
    Q_OBJECT
//    QML_READONLY_CSTREF_PROPERTY(int, week)

public:
    explicit PlayerProjModel (QObject *          parent      = Q_NULLPTR,
                                  const QByteArray & displayRole = QByteArray (),
                                  const QByteArray & uidRole     = {"playerid"})
        : QQmlObjectListModel (parent,displayRole,uidRole) {}


    void updateRosters(std::vector<pb::GameRoster> &inrosters, pb::IDataService *ds) {

//        qDebug() << " updateWeeklySchedule"  << week << weekly.DebugString().data();

        clear();

//        setweek(week);

        for(const pb::GameRoster & game  : inrosters) {
            // add game
            QString gameId = game.info.id().data();
            //add home players
            for(const auto& player : game.homeroster) {
                append(new PlayerProjModelItem(player.second,game.info.home(),
                                               player.first.data(),gameId,
                                               ds->GetAvgProjection(player.first),
                                               game.status < GameStatus_Status_INGAME,
                                               this));
            }

            //add away players
            for(const auto& player : game.awayroster) {
                append(new PlayerProjModelItem(player.second,game.info.away(),
                                               player.first.data(),gameId,
                                               ds->GetAvgProjection(player.first),
                                               game.status < GameStatus_Status_INGAME,
                                               this));
            }
        }
    }
};

Q_DECLARE_METATYPE(PlayerProjModelItem*)
Q_DECLARE_METATYPE(PlayerProjModel*)
#include "weeklyschedulemodel.h"
#include <QItemSelectionModel>
class ProjectionsViewFilterProxyModel : public SortFilterProxyModel
{
    Q_OBJECT

    WeeklyScheduleModel  * myGameModelProxy;
    QItemSelectionModel * mySelectedGames;
//    QStringListModel * myPositionCombobox;
    bool myIsEnabled = true;
    QString myPos = "All";

public:
    Q_PROPERTY(QStringList userRoleNames READ userRoleNames CONSTANT)

    ProjectionsViewFilterProxyModel(//QStringListModel * positionCombobox = NULL,
                                    WeeklyScheduleModel  * gameModelProxy= NULL,
                                    QItemSelectionModel * gameSelectionModel=NULL,
                                    QObject *parent = 0)
        : SortFilterProxyModel(parent)
    {
//        myPositionCombobox = positionCombobox;
        myGameModelProxy = gameModelProxy;
//        if (myGameModelProxy != NULL) mySelectedGames = gameSelectionModel;
        mySelectedGames = gameSelectionModel;
    }

    QStringList ret;
    QStringList userRoleNames() // Return ordered List of user-defined roles
    {


        return ret;
    }

    bool isEnabled(){
        return myIsEnabled;
    }

    void disable(){
        myIsEnabled = false;
    }

    void enable(){
        myIsEnabled = true;
    }

    void bindFilter(){
//        if (myPositionCombobox!=NULL){
//            QObject::connect(myPositionCombobox,
//                             SIGNAL(currentTextChanged(QString)),
//                             this,SLOT(invalidate()));
//        }

        if (myGameModelProxy!=NULL){
            QObject::connect(myGameModelProxy,
                             SIGNAL(modelReset()),
                             this,SLOT(invalidate()));
        }

        if (mySelectedGames!=NULL){
            QObject::connect(mySelectedGames,
                             SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                             this,SLOT(invalidate()));
        }
    }

    Q_INVOKABLE void setPos(const QString &pos) {
        if ( pos != myPos ) {
            myPos = pos;
            invalidate();
        }
    }

    Q_INVOKABLE virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) Q_DECL_OVERRIDE {
        qDebug() << " sort called" << column;
        QSortFilterProxyModel::sort(column, order);

//                qDebug() << " << cc " << columnCount();
//        QSortFilterProxyModel::setSortRole(column);
//        QSortFilterProxyModel::sort(0, order);
    }

protected:
    //filtering
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
        if (!myIsEnabled) return true;

//                qDebug() << " << cc " << columnCount();
//        if ( !QSortFilterProxyModel::filterAcceptsRow(sourceRow,sourceParent)) {
//            qDebug() << " filterAcceptsRow  no parent" << sourceRow;
//            return false;
//        }
//        qDebug() << " filterAcceptsRow" << sourceRow;

        PlayerProjModel * model = dynamic_cast<PlayerProjModel *>(sourceModel());
        if (model==NULL) return true;


        if ( myPos != "All")
            if ( model->at(sourceRow)->get_pos() != myPos )
                return false;


//        QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
        auto gameid = model->at(sourceRow)->get_gameid();

//        qDebug() << " filterAcceptsRow gameid" << gameid;
//        if (item == NULL) return true;
//        QString gameId = item->propertyValue<PropertyNames::Game_ID>().toString();

        if (gameid=="")  return false;
        if (mySelectedGames!=NULL && myGameModelProxy != NULL){
            if ( !mySelectedGames->hasSelection() ) return true;

//            qDebug() << " filterAcceptsRow hasselection";

            int i = myGameModelProxy->indexOf(myGameModelProxy->getByUid(gameid));
            return mySelectedGames->isSelected(myGameModelProxy->index(i));
        }

        return true;
    }

    bool setData (const QModelIndex & index, const QVariant & value, int role) {
        if ( index.row() < 0 )
            return true;

        qDebug() << "setDatasetDatasetDatasetData setting data" << index.row() << index.column();

        auto myindex = mapToSource(index);

        qDebug() << "setDatasetDatasetDatasetData after map" << myindex.row() << myindex.column();

        PlayerProjModel * model = dynamic_cast<PlayerProjModel *>(sourceModel());
        if (model==NULL) return true;

        qDebug() << " index model->at(index.row())->get_firstname() " << model->at(myindex.row())->get_firstname();

        model->at(myindex.row())->set_projection(value.toInt());
//        if ( model->at(index.row())->get_firstname() )
//            return false;

        return true;
    }

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE {
        return SortFilterProxyModel::data(index, role);
//        qDebug() <<role << " << cc " << columnCount();
    }

//        if (myPositionCombobox!=NULL){
//            //get current postion from position combo box
//            QString position= myPositionCombobox->currentText().trimmed().toUpper();
//            if (position != "ALL"){
//                QString playerPosition=item->propertyValue<PropertyNames::Position>().toString();
//                if (playerPosition != position)
//                    return false;
//            }
//        }

//        if (myGameModelProxy!=NULL){
//            GamesFilter gameFilter = myGameModelProxy->filter();
//            if (gameFilter != GamesFilter::All) {
//            GameTableModel * allGames = dynamic_cast<GameTableModel *>(myGameModelProxy->sourceModel());
//            if (allGames==NULL) return false;
//            QVariant vvalue;
//            GameStatus_Status gameStatus;
//            bool propertyFound = allGames->itemPropertyValue<PropertyNames::Game_Status>(gameId,vvalue);
//            if (!propertyFound) return false;
//            gameStatus = qvariant_cast<GameStatus_Status>(vvalue);
//            if (!GameViewFilterProxyModel::testGameStatus(gameFilter,gameStatus))
//                return false;
//            }
//        }


//    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const{


//    }

//    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const{
//        ProjectionSheetTableModel * model = dynamic_cast<ProjectionSheetTableModel *>(sourceModel());
//        if (model==NULL) return false;
//        QVariant lefData = model->columnData(source_left.column(),source_left);
//        QVariant rightData = model->columnData(source_right.column(),source_right);
//        if (lefData.isNull())  return true;
//        if (rightData.isNull())  return false;
//        if (lefData.type()!=rightData.type()) return false;
//        return lefData < rightData;
//    }

};




class LeaderBaordFantasyNameModelItem : public QObject {
    Q_OBJECT
    QML_CONSTANT_CSTREF_PROPERTY (QString, name)
    QML_CONSTANT_CSTREF_PROPERTY (qint32, skill)
    QML_CONSTANT_CSTREF_PROPERTY (qint32, lastseason)
    QML_CONSTANT_CSTREF_PROPERTY (qint32, thisseason)
    QML_CONSTANT_CSTREF_PROPERTY (qint32, thisweek)
    QML_CONSTANT_CSTREF_PROPERTY (qint32, lastweek)
    QML_CONSTANT_CSTREF_PROPERTY (qint32, lastupdate)
    QML_CONSTANT_CSTREF_PROPERTY (qint32, numcomplete)
    QML_CONSTANT_CSTREF_PROPERTY (quint64, hash)
    QML_CONSTANT_CSTREF_PROPERTY (QString, pk)

public:

    explicit LeaderBaordFantasyNameModelItem(const fantasybit::FantasyNameBal &in) :  QObject(nullptr) {
        m_name = in.name().data();
        m_pk = in.public_key().data();
        m_skill = in.stake();
        m_hash = in.chash();
    }
};


class LeaderBaordFantasyNameModel : public QQmlObjectListModel<LeaderBaordFantasyNameModelItem> {};

Q_DECLARE_METATYPE(LeaderBaordFantasyNameModel *)















//struct PlayerDetail {
//    PlayerBase base;
//    PlayerStatus::Status team_status;
//    PlayerGameStatus game_status;
//};

//struct GameRoster {
//    GameInfo info;
//    GameStatus::Status  status;
//    std::unordered_map<std::string,PlayerDetail> homeroster;
//    std::unordered_map<std::string,PlayerDetail> awayroster;

//};

//unordered_map<std::string,int> DataService::GetProjByName(const std::string &fname) {

//unordered_map<std::string,int> DataService::GetProjById(const std::string &pid) {

//std::vector<fantasybit::GameRoster> DataService::GetCurrentWeekGameRosters()

}

#endif // PLAYERPROJMODEL_H

