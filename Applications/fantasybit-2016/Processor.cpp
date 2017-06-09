//
//  Processor.cpp
//  fantasybit
//
//  Created by Jay Berg on 8/24/14.
//
//

#include <utility>
#include "Commissioner.h"
#include "ProtoData.pb.h"
#include <utils/utils.h>
#include <algorithm>
#include <iostream>
#include "fbutils.h"
//#include "Source.h"
#include "DistributionAlgo.h"
#include "blockrecorder.h"
#include "Processor.h"
#include "platform.h"
#include "globals.h"
#include "ApiData.pb.h"
#include "RestFullCall.h"
#include "fbutils.h"
#include "pbutils.h"
#include "ldbwriter.h"

#if defined(DATAAGENTWRITENAMES) || defined(DATAAGENTWRITEPROFIT) || defined(SQL)
//#include "playerloader.h"
#include "../../../fantasybit-2015/tradingfootball/playerloader.h"

#endif

#ifdef BLOCK_EXPLORER
#include "blockexplorer.h"
#ifdef BLOCK_EXPLORER_WRITE_FILLS
#include "utils.h"
#endif
#endif

namespace fantasybit
{

#if defined(SQL) || defined(DATAAGENTWRITENAMES) || defined(DATAAGENTWRITEPROFIT)
    SqlStuff sql("satoshifantasy","distribution");
#endif

void BlockProcessor::hardReset() {
    mRecorder.closeAll();
    mData.closeAll();
    mNameData.closeAll();
#ifdef TRADE_FEATURE
    mExchangeData.closeAll();
    mExchangeData.removeAll();
#endif

    pb::remove_all(Platform::instance()->getRootDir() + "index/");
#ifndef NOUSE_GENESIS_BOOT
    NFLStateData::InitCheckpoint();
#endif
    BlockRecorder::InitCheckpoint(BlockRecorder::zeroblock);

}

int32_t BlockProcessor::init() {

    mRecorder.init();
    if (!mRecorder.isValid() ) {
        emit InvalidState(mRecorder.getLastBlockId());
        qInfo() <<  "mRecorder not valid! ";
        mRecorder.closeAll();
        pb::remove_all(Platform::instance()->getRootDir() + "index/");
        qInfo() <<  "delete all leveldb, should have nothing";

#ifndef NOUSE_GENESIS_BOOT
        NFLStateData::InitCheckpoint();
#endif
        BlockRecorder::InitCheckpoint(BlockRecorder::zeroblock);
        qDebug() << "BlockProcessor::init() zb" << BlockRecorder::zeroblock;

        mRecorder.init();
        if (!mRecorder.isValid() ) {
            qInfo() <<  "mRecorder not valid! ";
            InvalidState(mRecorder.getLastBlockId());
            return -1;
        }

    }

    mData.init();
    mNameData.init();
#ifdef TRADE_FEATURE
    mExchangeData.init();
#endif

//    OnSeasonStart(mData.GetGlobalState().season());

    //qInfo() <<  "YES mRecorder is valid";

    lastidprocessed =  mRecorder.getLastBlockId();

#ifdef BLOCK_EXPLORER
    bx.init();//lastidprocessed);
#endif

    return lastidprocessed;
}


int32_t BlockProcessor::process(Block &sblock) {

    //qDebug() << "BlockProcessor process head().num(): " << sblock.signedhead().head().num();
#ifdef TRACE
    if ( sblock.signed_transactions_size() > 0) {
        qDebug() << "BlockProcessor processsb0 sblock.signed_transactions(0).DebugString().data() ";
//        qDebug() << sblock.signed_transactions(0).DebugString().data();
    }
#endif

    if (!verifySignedBlock(sblock)) {
        //qCritical() << "verifySignedBlock failed! ";
        qCritical() << "verifySignedBlock failed! ";
        return -1;
    }
    else {
        //qInfo() << "yes verifySignedBlock " <<  sblock.signedhead().head().num();
    }

//    if ( sblock.signedhead().head().num() == 139 ) {
//        auto bs = sblock.DebugString();
//        qInfo() << bs.data();
//    }

    mRecorder.startBlock(sblock.signedhead().head().num());

//    if ( sblock.signedhead().head().num() == 1199 ) {
//        qInfo() << sblock.DebugString();
//        auto str = sblock.DebugString();
//        qDebug() << str.data();
//    }

#ifdef CLEAN_BLOCKS
    mRecorder.newBlock(sblock);
#endif

    if (sblock.signedhead().head().blocktype() == BlockHeader::Type::BlockHeader_Type_DATA)
        processDataBlock(sblock);
    else
        processTxfrom(sblock);

    qInfo() << " BLOCK(" << sblock.signedhead().head().num() << ") processed! ";
    lastidprocessed = mRecorder.endBlock(sblock.signedhead().head().num());

#ifndef NOUSE_GENESIS_BOOT
    if ( mLastWeekStart ) {
        mLastWeekStart = false;
        int week = mData.GetGlobalState().week();
        auto boot = mData.makeBootStrap(2016,
                                        mData.GetGlobalState().week(),
                                        lastidprocessed-1);
        boot.set_key((week < 10 ? "20160" : "2016") + to_string(week));
        boot.set_previd(sblock.signedhead().head().prev_id());
        mNameData.addBootStrap(&boot,true);

    }
#endif

#ifdef CLEAN_BLOCKS
    mRecorder.endBlock();
#ifdef BLOCK_EXPLORER
    bx.pblock(mRecorder.cleanBlock);
    bx.endit();

#ifdef BLOCK_EXPLORER_WRITE_FILLS
    while (!fantasybit_bx::staticglobal::FILL_QUEUE.isEmpty())
        sql.fills(fantasybit_bx::staticglobal::FILL_QUEUE.dequeue());
#endif

    //assert( Commissioner::getName("FantasyAgent")->getBalance() == bx.SkillBalance("FantasyAgent"));

    if ( Commissioner::getName("FantasyAgent")->getBalance() != bx.SkillBalance("FantasyAgent")) {
        qDebug()
                << "bad fantasyagent " << Commissioner::getName("FantasyAgent")->getBalance()
                <<  bx.SkillBalance("FantasyAgent");
    }

#endif

#endif

    //qDebug() << " outDelta " << outDelta.DebugString();

    return lastidprocessed;
}

bool BlockProcessor::processDataBlock(const Block &sblock) {
    if (sblock.signed_transactions_size() < 1) {
        qCritical() << "expect Transition for Data block";
        return false;
    }

#ifdef JAYHACK
    if ( sblock.signedhead().head().num() == 1 ) {
        qDebug() << " jay hack 1";
        processTxfrom(sblock,1,true);
        for ( int i = 1; i < sblock.signed_transactions_size(); i++) {
            if ( sblock.signed_transactions(i).trans().type() != TransType::DATA)
                continue;

            auto dt = sblock.signed_transactions(i).trans().GetExtension(DataTransition::data_trans);
            if (dt.data_size() > 0)
                process(dt.data(), "FantasyAgent", dt.type(),dt.season());

            process(dt);
        }

        qDebug() << " jay hack 2";


//        return true;
    }
#endif

    auto st = sblock.signed_transactions(0);
    if (st.trans().type() != TransType::DATA)  {
        qCritical() << "expect first Transaction for Data block to be Data";
        return false;
    }

    auto dt = st.trans().GetExtension(DataTransition::data_trans);
    if (dt.data_size() > 0)
        process(dt.data(), st.fantasy_name(), dt.type(), dt.season());

    if (sblock.signed_transactions_size() > 1)
        processTxfrom(sblock, 1);

    qDebug() << "processing ccccc" << dt.type() << dt.season() << dt.week();
//    qDebug() << dt.DebugString().data();
    process(dt);

    return true;
}

/*
bool BlockProcessor::isInWeekGame(const std::string &id, int week ) {
    auto it = Source::TeamWeek.find(id);
    if ( it == end(Source::TeamWeek) )
        return false;

    return  (it->second.first == week ) && (it->second.second);
}

bool BlockProcessor::sanity(const FantasyPlayerPoints &fpp) {
    if ( !fpp.has_season() || !fpp.has_week()
         || !fpp.has_playerid() || !fpp.has_points() )
        return false;

    if ( fpp.season() != mGlobalState.season() ) return false;

    auto it = Source::PlayerTeam.find(fpp.playerid());
    if (it == end(Source::PlayerTeam))
        return false;

    return isInWeekGame(it->second,fpp.week());
}
*/
void BlockProcessor::process(decltype(DataTransition::default_instance().data()) in,
            const std::string &blocksigner,TrType transtype, int season )  {

    //outDelta.mutable_datas()->CopyFrom(in);

    bool haveresults = false;
    for (const auto d : in) {
        Data *nd;
        PlayerData tpd{};
        GameData ttd{};
        ResultData rd{};
        switch (d.type()) {
            case Data_Type_PLAYER: {
                tpd = d.GetExtension(PlayerData::player_data);
                if ( !tpd.has_playerid() ) {
                    qCritical() << "no playerid" + QTD(tpd.DebugString());
                    break;
                }
//                int pid = std::stoi(tpd.playerid());
//                if (pid > 0 && pid <= 32 ) { //Team DEF
//                    if ( transtype !=  SEASONSTART) {
//                        qCritical() << "Teams cant change names" << d.DebugString().data();
//                        break;
//                    }

//                    mData.TeamNameChange(tpd.playerid(),tpd.player_base(),tpd.player_status());
//                    break;
//                }
                if ( tpd.has_player_base() )
                    mData.AddNewPlayer(tpd.playerid(),tpd.player_base());
                if ( tpd.has_player_status() )
                    mData.UpdatePlayerStatus(tpd.playerid(),tpd.player_status());
                if ( tpd.has_player_game_status() )
                    ;//ToDo

                break;
            }
            case Data_Type_GAME:
                ttd = d.GetExtension(GameData::game_data);
                if ( ttd.has_status() && ttd.has_gameid() )
                    mData.UpdateGameStatus(ttd.gameid(),ttd.status());
                else {
                    qCritical() << "no data" << ttd.DebugString().data();
                }
                break;
            case Data_Type_RESULT:
            {
                rd = d.GetExtension(ResultData::result_data);

                if ( !rd.has_game_result()) {
                    qCritical() << "no data" << ttd.DebugString().data();
                    break;
                }

//                if ( rd.game_result().gameid() == "201601111")
//                    qDebug() << " 201601111";
                /*
                if ( !sanity(rd.fpp()) ) {
                    qCritical() << " invalid result skipping" << rd.DebugString();
                    break;
                }
                */
                auto st = mData.GetUpdatedGameStatus(rd.game_result().gameid());
                if ( st.status() == GameStatus::CLOSED ) {
                    qWarning() << rd.game_result().gameid().data() << " game already closed - ignorning result ";
                    break;
                }

                auto allprojs = mNameData.GetGameProj(rd.game_result().gameid());
                bool nopnl = false;
#ifdef TRADE_FEATURE
                GameSettlePos gsp;
                if ( !mExchangeData.GetGameSettlePos(rd.game_result().gameid(),gsp) )
                   nopnl = true;
#else
                nopnl = true;
#endif
//                qDebug() << allprojs.DebugString().data();

                unordered_map<string,std::unordered_map<std::string,int>> projmaps;
                unordered_map<string,BookPos *> posmap;

                for (auto ha : {QString("home"),QString("away")}) {
                    for ( auto fpj : (ha == QString("home")) ? allprojs.home() : allprojs.away())
                        projmaps[fpj.playerid()].insert(make_pair(fpj.name(),fpj.proj()));

                    if ( nopnl ) continue;

#ifdef TRADE_FEATURE
                    auto rgsp =  (ha == QString("home")) ? gsp.mutable_home() : gsp.mutable_away();
                    for ( int i=0; i<rgsp->size();i++) {
                        BookPos *bp = rgsp->Mutable(i);
                        posmap[bp->playerid()] = bp;
                    }
#endif
                }


                //for ( auto fpj : allprojs.away())
                //   projmaps[fpj.playerid()].insert(make_pair(fpj.name(),fpj.proj()));


                for (auto ha : {QString("home"),QString("away")}) {

                    qDebug() << "****" << ha;
                    int size =  (ha == QString("home")) ?
                                rd.game_result().home_result_size()
                                :  rd.game_result().away_result_size();

                    if( size <= 0) {
                        qCritical() << "no" << ha << " result" << rd.DebugString().data();
                        continue;
                    }

                    decltype(rd.game_result().home_result())
                            haresult = (ha == QString("home")) ?
                                rd.game_result().home_result()
                                :  rd.game_result().away_result();

                    decltype(rd.mutable_game_result()->mutable_home_result())
                            mut_haresult = (ha == QString("home")) ?
                                rd.mutable_game_result()->mutable_home_result()
                                :  rd.mutable_game_result()->mutable_away_result();

                    double total = 0.0;
                    for ( int i =0; i < size; i++) {
                        //qDebug() << haresult.Get(i).playerid()
                          //       << haresult.Get(i).result();

                        auto proj = projmaps[haresult.Get(i).playerid()];

                        BookPos  *bpos = nullptr;
                        if ( !nopnl ) {
                            bpos = posmap[haresult.Get(i).playerid()];
                        }

                        total += haresult.Get(i).result();
                        processResultProj(mut_haresult->Mutable(i),proj,bpos,blocksigner);
                        mData.UpdatePlayerStats(haresult.Get(i));
                    }

                    if ( ha == QString("home") )
                        rd.mutable_game_result()->set_hometotal(total);
                    else
                        rd.mutable_game_result()->set_awaytotal(total);

                }

                /*
                if( rd.game_result().away_result_size() <= 0 )
                    qCritical() << "no away result" + QTD(rd.DebugString());
                else
                    //for (auto result : rd.game_result().away_result() ) {
                    for ( int i =0; i < rd.game_result().away_result_size(); i++) {
                        qDebug() << rd.game_result().away_result(i).playerid()
                                 << rd.game_result().away_result(i).result();

                        auto proj = projmaps[rd.game_result().away_result(i).playerid()];
                        //if ( proj.size() == 0 )
                        //    continue;
                        processResultProj(rd.mutable_game_result()->mutable_away_result(i),
                                          proj,blocksigner);
                        //result.mutable_fantaybitaward()->CopyFrom(delta.fantaybitaward());
                        //rd.mutable_game_result()->
                        //        mutable_away_result(i)->mutable_fantaybitaward()->CopyFrom(delta.fantaybitaward());
                    }

                //for (auto result : rd.game_result().away_result() )
                //    qDebug() << result.playerid() << result.fantaybitaward_size();

                */
                mData.ProcessAddGameResult(rd.game_result().gameid(),rd.game_result());
                haveresults = true;
#if defined DATAAGENTWRITENAMES || defined DATAAGENTWRITEPROFIT
                {
#ifndef DATAAGENTWRITENAMES_FORCE
                if ( !amlive ) break;
#endif

#ifdef DATAAGENTWRITENAMES_FORCE_GAMEID
                if ( rd.game_result().gameid() != "201601224" ) break;
                qDebug() << " DATAAGENTWRITENAMES_FORCE !!!!!!!!!!!!!!!!!!!!!!!!";
#endif

                Distribution dist{};
                Profits prof{};
                dist.set_gameid(rd.game_result().gameid());
                prof.set_gameid(dist.gameid());
                auto gs = mData.GetGlobalState();
                dist.set_season(gs.season());
                dist.set_week(gs.week());
                prof.set_season(dist.season());
                prof.set_week(dist.week());

                auto gi = mData.GetGameInfo(dist.gameid());
                dist.set_teamid(gi.home());
                prof.set_teamid(dist.teamid());
                for ( auto res : rd.game_result().home_result()) {
                    dist.set_playerid(res.playerid());
                    dist.set_result(res.result());
                    prof.set_playerid(dist.playerid());
                    prof.set_result(dist.result());
                    for ( auto fba : res.fantaybitaward()) {
                        dist.set_fantasy_nameid(FantasyName::name_hash(fba.name()));
                        dist.set_proj(fba.proj());
                        dist.set_award(fba.award());
#ifdef DATAAGENTWRITENAMES
                        sql.distribute(dist);
#endif
                    }

                    for ( auto fba : res.fantasybitpnl()) {

                        prof.set_fantasy_nameid(FantasyName::name_hash(fba.name()));
                        prof.set_qty(fba.spos().qty());
                        prof.set_price(fba.spos().price() / ( (prof.qty() == 0) ? 1 : -prof.qty()));
                        prof.set_pnl(fba.pnl());
#ifdef DATAAGENTWRITEPROFIT
                        sql.profit(prof);
#endif
                    }
                }

                dist.set_teamid(gi.away());
                prof.set_teamid(dist.teamid());
                for ( auto res : rd.game_result().away_result()) {
                    dist.set_playerid(res.playerid());
                    dist.set_result(res.result());
                    prof.set_playerid(dist.playerid());
                    prof.set_result(dist.result());

                    for ( auto fba : res.fantaybitaward()) {
                        dist.set_fantasy_nameid(FantasyName::name_hash(fba.name()));
                        dist.set_proj(fba.proj());
                        dist.set_award(fba.award());
                        emit new_dataDistribution(dist);
                        auto ds = dist.SerializeAsString();

#ifdef DATAAGENTWRITENAMES
                        sql.distribute(dist);
#endif

                    }

                    for ( auto fba : res.fantasybitpnl()) {

                        prof.set_fantasy_nameid(FantasyName::name_hash(fba.name()));
                        prof.set_qty(fba.spos().qty());
                        prof.set_price(fba.spos().price() / ( (prof.qty() == 0) ? 1 : -prof.qty()));
                        prof.set_pnl(fba.pnl());

#ifdef DATAAGENTWRITEPROFIT
                        sql.profit(prof);
#endif

                    }
                }
                }
#endif
                break;
            }
            case Data_Type_SCHEDULE: {
                auto sd = d.GetExtension(ScheduleData::schedule_data);
                if ( sd.has_week() && sd.has_weekly() )
                    mData.AddNewWeeklySchedule(season,sd.week(),sd.weekly());
                else {
                    qCritical() << "no data" + QTD(sd.DebugString());
                }
                break;
            }

            case Data_Type_MESSAGE: {
                auto msg = d.GetExtension(MessageData::message_data);
                if ( msg.has_msg() ) {
                    onControlMessage(QString::fromStdString(msg.msg()));

//                    qWarning() << "Control messgae" << msg.DebugString().data();
                }
                /*
#ifdef Q_OS_MAC
                    if ( msg.msg().find("win64") != string::npos )
#endif
#ifdef Q_OS_WIN
                    if ( msg.msg().find("osx64") != string::npos )
#endif
                        break;

                    //if ( !amlive )
                    //    break;
                    //else
                    if ( msg.has_gt() || msg.has_lt()) {
                        int version =
                                MAJOR_VERSION * 1000 +
                                MINOR_VERSION * 100 +
                                REVISION_NUMBER * 10+
                                BUILD_NUMBER;

                        if ( (msg.has_gt() && version > msg.gt())
                             ||
                              (msg.has_lt() && version < msg.lt()))
                        onControlMessage(QString::fromStdString(msg.msg()));

                    }
                    else
                        onControlMessage(QString::fromStdString(msg.msg()));

                }
                */
                break;
            }
            default:
                qWarning() << "unexpedted type" << d.type();
                break;
        }
    }

    if ( haveresults && amlive )
        emit FinishedResults();
}


void BlockProcessor::processResultProj(PlayerResult* playerresultP,
                                       std::unordered_map<std::string,int> &proj,
                                       BookPos *pbpos,
                                       const std::string &blocksigner) {
    auto &playerresult = *playerresultP;
//    PlayerResult awards;
    DistribuePointsAvg dist(proj);
    auto rewards = dist.distribute(playerresult.result(), blocksigner);

    //if ( !playerresult.has_result() && playerresult.has_stats()) {
        //auto calc = CalcResults(playerresult.stats());
        //playerresult.set_result(calc);
    //}

    //decltype(PlayerResult::default_instance().fantaybitaward())
    for (auto r : rewards ) {
        FantasyBitAward &fba = *playerresult.mutable_fantaybitaward()->Add();
        fba.set_name(r.first);
        auto m = proj[r.first];
        fba.set_proj(m);
        fba.set_award(r.second);
        //awards.add_fantaybitaward()->CopyFrom(fba);
        mNameData.AddBalance(r.first,r.second);
    }
    //playerresult.mutable_fantaybitaward()->CopyFrom(awards.fantaybitaward());
    //return awards;

    if ( pbpos == nullptr) return;

    SettlePositionsRawStake set(*pbpos);
    auto pnls = set.settle(playerresult.result(), blocksigner);
    for (auto r : pnls ) {
        FantasyBitPnl &fba = *playerresult.mutable_fantasybitpnl()->Add();
        fba.mutable_spos()->CopyFrom(r.second.first);
        fba.set_pnl(r.second.second);
        fba.set_name(r.first);
        //awards.add_fantaybitaward()->CopyFrom(fba);
        mNameData.AddPnL(r.first,r.second.second);
    }
}

void BlockProcessor::process(const DataTransition &indt) {
    auto mGlobalState = mData.GetGlobalState();
    switch (indt.type())
    {
    case TrType::SEASONSTART:
        if (mGlobalState.state() != GlobalState_State_OFFSEASON)
            qWarning() << indt.type() << " bad transition for current state " << mGlobalState.state();

        {
            qInfo() <<  indt.season() << " Season Start week" << indt.week();
            if (mGlobalState.season() != indt.season()) {
                qWarning() << "wrong season! " << indt.DebugString().data();
                mGlobalState.set_season(indt.season());
            }
            mGlobalState.set_week(0);//indt.week());
            mGlobalState.set_state(GlobalState_State_INSEASON);
            mData.OnGlobalState(mGlobalState);
            OnSeasonStart(indt.season());
            if ( indt.week() != 0)
                OnWeekStart(indt.week());
        }
        break;
    case TrType::SEASONEND:
        break;
        if (mGlobalState.state() != GlobalState_State_INSEASON) {
            qWarning() << indt.type() << " baad transition for current state " << mGlobalState.state();
//            break;
        }
        else {
            qInfo() <<  indt.season() << " Season End :( ";

            if (mGlobalState.season() == indt.season() - 1) {
                qInfo() <<  indt.season() << "bad Season End :( " << mGlobalState.season();
            }
            else if (mGlobalState.season() == indt.season()) {
                OnSeasonEnd(mGlobalState.season());
                mGlobalState.set_season(indt.season()+1);
                mGlobalState.set_week(0);

            }
            else {
                qWarning() << "warning wrong season! using mGlobalState.season()+1" << mGlobalState.season()+1  << indt.DebugString().data();
            }
        }

        mGlobalState.set_state(GlobalState_State_OFFSEASON);
        mData.OnGlobalState(mGlobalState);


        //outDelta.mutable_globalstate()->CopyFrom(mGlobalState);
        break;

    case TrType::HEARTBEAT:
        //todo: deal w data in this msg
        if (mGlobalState.season() != indt.season()) {
            qWarning() << "wrong season! " << indt.DebugString();
            //mGlobalState.set_season(indt.season());
        }

        if (mGlobalState.week() != indt.week()) {
            if ( mGlobalState.week() == 0 && indt.week() == 1) {
                mGlobalState.set_week(1);
                mData.OnGlobalState(mGlobalState);
                OnWeekStart(1);
            }
            else
                qWarning() << "wrong week! " << indt.DebugString().data() << mGlobalState.DebugString().data();
            //mGlobalState.set_week(indt.week());
        }

        break;
    case TrType::GAMESTART:
        for (auto t : indt.gamedata()) {
            mData.OnGameStart(t.gameid(),t.status());
            qInfo() <<  "Kickoff for game " << t.DebugString().data();
            auto gi =  mData.GetGameInfo(t.gameid());
            auto homeroster = mData.GetTeamRoster(gi.home());
            auto awayroster = mData.GetTeamRoster(gi.away());
            vector<string> homep, awayp;
            for ( auto hr : homeroster)
                homep.push_back(hr.first);
            for ( auto hr : awayroster)
                awayp.push_back(hr.first);

            mNameData.OnGameStart(t.gameid(),homep,awayp);
#ifdef TRADE_FEATURE
            mExchangeData.OnGameStart(t.gameid(),homep,awayp);
#endif

        }
        break;
    case TrType::WEEKOVER:
    {

        if (mGlobalState.state() != GlobalState_State_INSEASON)
            qWarning() << indt.type() << " baad transition for current state " << mGlobalState.state();

        if ( indt.week() != mGlobalState.week())
            qWarning() << indt.type() << " wrong week" << mGlobalState.week() << indt.week();
#ifdef TRADE_FEATURE
        std::unordered_map<string,BookPos> pos;
        mExchangeData.GetRemainingSettlePos(pos);
        for ( auto sbp : pos ) {
            SettlePositionsRawStake set(sbp.second);
            auto pnls = set.settle(0.0, Commissioner::FantasyAgentName());
            for (auto r : pnls ) {
                //FantasyBitPnl &fba = *playerresult.mutable_fantasybitpnl()->Add();
                //fba.mutable_spos()->CopyFrom(r.second.first);
                //fba.set_pnl(r.second.second);
                //awards.add_fantaybitaward()->CopyFrom(fba);
                mNameData.AddPnL(r.first,r.second.second);
            }
        }
#endif

#ifdef JAYHACK
//        if (indt.week() == 16)
//            break;
#endif
        OnWeekOver(indt.week());
        int newweek = indt.week() + 1;
        qInfo() <<  "week " << indt.week() << " Over ";
        if (indt.week() == 16) {
            if (mGlobalState.season() == indt.season()) {
                OnSeasonEnd(mGlobalState.season());
                mGlobalState.set_season(indt.season()+1);
            }
            else {
                OnSeasonEnd(mGlobalState.season());
                mGlobalState.set_season(mGlobalState.season()+1);
                qWarning() << "warning wrong season! using mGlobalState.season()+1" << mGlobalState.season()+1  << indt.DebugString().data();
            }


            newweek = 0;
            qInfo() <<  "season " << indt.season() << " Over ";
            mGlobalState.set_state(GlobalState_State_OFFSEASON);
            mGlobalState.set_week(0);
            mData.OnGlobalState(mGlobalState);
            //OnSeasonStart(mGlobalState.season());
            //OnWeekStart(0);
        }
        else {
            mGlobalState.set_week(newweek);
            mData.OnGlobalState(mGlobalState);
            OnWeekStart(newweek);
        }
        break;
    }
    case TrType::TRADESESSIONSTART:
    {
        mExchangeData.OnTradeSessionStart(indt.week());
        break;
    }
    default:
        break;
    }
}

bool BlockProcessor::isValidTx(const SignedTransaction &st) {
    const Transaction &t = st.trans();
    pb::sha256 digest = pb::hashit(t.SerializeAsString());
    if (digest.str() != st.id()) {
        qCritical() << "digest.str() != st.id() ";
        //fbutils::LogFalse(std::string("Processor::process signed transaction hash error digest ").append(st.DebugString()));
        return false;
    }

    if (t.version() != Commissioner::TRANS_VERSION) {
        qCritical() << "t.version() != Commissioner::TRANS_VERSION";
        //fbutils::LogFalse(std::string("Processor::process wrong transaction version ").append(st.DebugString()));
        return false;
    }

    pb::signature sig = Commissioner::str2sig(st.sig());
    if ( st.trans().type() == TransType::STAMPED) {
        if ( Commissioner::verifyOracle(sig, digest) )
            return true;

        qCritical() << "TransType::STAMPED !Commissioner::verifyOracle";
        return false;
    }

    if ( st.fantasy_name() == "") {
        qCritical() << " Blank FantasyName";
        return false;
    }

    if (t.type() == TransType::NAME) {
        auto nt = t.GetExtension(NameTrans::name_trans);
        if (!verify_name(st, nt, sig, digest)) {
            qDebug() << "t.type() == TransType::NAME !verify name";
            return false;
        }

        return true;
    }

    if (!Commissioner::verifyByName(sig, digest, st.fantasy_name())) {
        qCritical() << "!Commissioner::verifyByName";
        //fbutils::LogFalse(std::string("Processor::process cant verify trans sig").append(st.DebugString()));
        return false;;
    }

    return true;
}

void BlockProcessor::processTxfrom(const Block &b,int start, bool nameonly ) {

    //first do name transactions
    for (int i = start; i < b.signed_transactions_size(); i++) {

        if ( b.signed_transactions(i).trans().type() != TransType::NAME)
            continue;

        qDebug() << "processing name tx " << i;//b.signed_transactions(i).trans().DebugString().data();// TransType_Name(t.type());
        auto &st = b.signed_transactions(i);
        if ( !isValidTx(st)) {
            qDebug() << " imvalid tx 1" << st.DebugString().data() ;
            continue;
        }

#ifdef CLEAN_BLOCKS
        mRecorder.addTx(st);
#endif

        const NameTrans & nt = b.signed_transactions(i).trans().GetExtension(NameTrans::name_trans);
        mNameData.AddNewName(nt.fantasy_name(), nt.public_key(), b.signedhead().head().num() );
        qInfo() <<  "verified " << FantasyName::name_hash(nt.fantasy_name());

    }

    if ( nameonly ) return;

   // for (const SignedTransaction &st : b.signed_transactions()) //
    for (int j = start; j < b.signed_transactions_size(); j++)
    {
        if ( b.signed_transactions(j).trans().type() == TransType::NAME)
            continue;

        const SignedTransaction &st = b.signed_transactions(j);
        const Transaction &t = b.signed_transactions(j).trans();
        //pb::sha256 digest = pb::sha256::hash(t.SerializeAsString());

        //qDebug() << "processing tx " << st.DebugString().data();

        if (!isValidTx(st)) {
            qDebug() << " imvalid tx 2" << st.DebugString().data();
            continue;
        }
#ifdef CLEAN_BLOCKS
        mRecorder.addTx(st);
#endif

        switch (t.type())
        {
        case TransType::PROJECTION_BLOCK: {
            const ProjectionTransBlock & ptb = t.GetExtension(ProjectionTransBlock::proj_trans_block);
            //qDebug() << st.fantasy_name() << "new projection block";// << ptb.DebugString();
            for (const PlayerPoints & pt : ptb.player_points() ) {
                mNameData.AddProjection(st.fantasy_name(), pt.playerid(), pt.points(),b.signedhead().head().num());
            }

            break;

        }

        case TransType::PROJECTION:
        {
            auto pt = t.GetExtension(ProjectionTrans::proj_trans);
//            qDebug() << st.fantasy_name() << "new projection " << pt.DebugString().data();
            mNameData.AddProjection(st.fantasy_name(), pt.playerid(), pt.points(),b.signedhead().head().num());
            break;
        }

        case TransType::TIME: {
            break;
        }

        case TransType::STAMPED: {
            auto stamped = t.GetExtension(StampedTrans::stamped_trans);
            qDebug() << "new StampedTrans " << stamped.timestamp() << stamped.seqnum();

            ProcessInsideStamped(stamped.signed_orig(),stamped.seqnum(),b.signedhead().head().num());

            break;
        }

        default:
            break;
        }
    }
}

void BlockProcessor::ProcessInsideStamped(const SignedTransaction &inst,int32_t seqnum,int32_t blocknum) {
    auto fn = BlockProcessor::getFNverifySt(inst);
    if ( !fn ) {
        qWarning() << "invalid tx inside stamped" << inst.trans().type();
        return;
    }

    const Transaction &t = inst.trans();
    switch (t.type()) {
        case TransType::EXCHANGE:
        {
#ifndef TRADE_FEATURE
            break;
#endif
            auto emdg = t.GetExtension(ExchangeOrder::exchange_order);
            //qDebug() << "new ExchangeOrder " << emdg.DebugString();

            //bool subscribe = mNameData.IsSubscribed(fn->FantasyName.alias());
            mExchangeData.OnNewOrderMsg(emdg,seqnum,fn,blocknum);
            break;
        }
        default:
            break;
    }

}

void BlockProcessor::OnWeekOver(int week) {
    mNameData.OnWeekOver(week);
    mData.OnWeekOver(week);
#ifdef TRADE_FEATURE
    mExchangeData.OnWeekOver(week);
#endif

    emit WeekOver(week);
}

void BlockProcessor::OnWeekStart(int week) {
    mNameData.OnWeekStart(week);
    mData.OnWeekStart(week);
#ifdef TRADE_FEATURe
    mExchangeData.OnWeekStart(week);
#endif
    mLastWeekStart = true;

    emit WeekStart(week);
}

void BlockProcessor::OnSeasonStart(int season) {
    mNameData.OnSeasonStart(season);
    mData.OnSeasonStart(season);
//    mExchangeData.OnSeasonStart(season);
    emit SeasonStart(season);
}

void BlockProcessor::OnSeasonEnd(int season) {
//    mNameData.OnSeasonEnd(season);
    mData.OnSeasonEnd(season);
//    mExchangeData.OnSeasonStart(season);
//    emit WeekStart(week);
}


bool BlockProcessor::verifySignedBlock(const Block &sblock)
{
//    return true;
    //qDebug() << verifySignedBlock;
#ifdef TRACEDEBUG
    qDebug() << " verifySignedBlock " << sblock.signedhead().head().DebugString().data();
#endif

    if (sblock.signedhead().head().version() != Commissioner::BLOCK_VERSION)
    {
        qCritical() << " !verifySignedBlock wrong block version! ";
    //    return false;
    }

#ifdef TRACEDEBUG
    else
        qDebug() << "yes verifySignedBlock " ;
#endif
    pb::sha256 digest = pb::hashit(sblock.signedhead().head().SerializeAsString());

    //qDebug() << "qqqqqq" << sblock.signedhead().head().num()
    //         << digest.str().data() << sblock.signedhead().head().prev_id();
    //if (digest.str() != sblock.signedhead().id())
    //	return
    //fbutils::LogFalse(std::string("Processor::process block hash error digest \n").append(sblock.DebugString()).append(digest.str()));
    //assert(digest.str() == sblock.id());

    pb::signature sig = Commissioner::str2sig(sblock.signedhead().sig());

    //assert(Commissioner::verifyOracle(sig, digest));
    if (!Commissioner::verifyOracle(sig, digest))
#ifdef NO_ORACLE_CHECK_TESTING
        if (!Commissioner::GENESIS_NUM == sblock.block().head().num())
#endif
        {
            qCritical() << " Invalid Block Signer!";
            return false;
        }

    return true;
}

bool BlockProcessor::verifySignedTransaction(const SignedTransaction &st) {
    qDebug() << st.DebugString().data();

    if (st.trans().version() != Commissioner::TRANS_VERSION)
    {
        qCritical() << " !verifySignedTransaction wrong trans version! ";
        return false;
    }

    pb::sha256 digest = pb::hashit(st.trans().SerializeAsString());
    if (digest.str() != st.id()) {
        qCritical() << "digest.str() != st.id() ";
        return false;
    }

    if ( st.fantasy_name() == "") {
        qCritical() << " Blank FantasyName";
        return false;;
    }

    pb::signature sig = Commissioner::str2sig(st.sig());
    if (st.trans().type() != TransType::NAME)
        if (!Commissioner::verifyByName(sig, digest, st.fantasy_name()))
        {
            qCritical() << "!Commissioner::verifyByName";
            qCritical() << "sig :" << st.sig();
            qCritical() << "st.fantasy_name() :" << st.fantasy_name();

            return false;;
        }

    return true;
}

bool BlockProcessor::verifyBootstrap(LdbWriter &ldb,const Bootstrap &bs) {

//    std::string errorstr;
//    std::unordered_map<std::string,PlayerMeta> m_playermetamap;
    //    auto mroot = loadMerkleMap(ldb,bs.playermetaroot(),m_playermetamap);

    std::vector<std::string> roots{bs.playermetaroot(), bs.gamemetaroot(), bs.fnamemetaroot() };
    for ( auto root : roots) {
        MerkleTree mtree;
        ldb.read(root,mtree);
        if ( mtree.root() != root )
            return false;

        mtree.set_root(pb::makeMerkleRoot(mtree.leaves()));
        if ( mtree.root() != root )
            return false;

        MerkleTree mtree2;
        for ( auto shp : mtree.leaves()) {
            mtree2.add_leaves(pb::hashit(ldb.read(shp)).str());
        }

        mtree.set_root(pb::makeMerkleRoot(mtree2.leaves()));
        if ( mtree.root() != root )
            return false;
    }

    return true;
}

std::shared_ptr<FantasyName> BlockProcessor::getFNverifySt(const SignedTransaction &st) {
    {
    auto ret = Commissioner::getName(st.fantasy_name());

    if ( !isValidTx(st) )
        ret.reset();

    return ret;
    }
    std::shared_ptr<FantasyName> ret;
    if (st.trans().version() != Commissioner::TRANS_VERSION) {
        qCritical() << " !verifySignedTransaction wrong trans version! ";
        return ret;
    }

    pb::sha256 digest = pb::hashit(st.trans().SerializeAsString());
    if (digest.str() != st.id()) {
        qCritical() << "digest.str() != st.id() ";
        return ret;
    }

    if ( st.fantasy_name() == "") {
        qCritical() << " Blank FantasyName";
        return ret;
    }



    ret = Commissioner::getName(st.fantasy_name());
    if ( !ret )
        qCritical() << " cant find FantasyName" << st.fantasy_name().data();
    else {
        pb::signature sig = Commissioner::str2sig(st.sig());
        if ( !Commissioner::verify(sig,digest,ret->pubkey()) ) {
            ret.reset();
            qCritical() << "verify error" << st.fantasy_name().data() << "getFNverifySt";
        }
    }
    return ret;
}

bool BlockProcessor::verify_name(const SignedTransaction &st, const NameTrans &nt, 
    const pb::signature& sig, const pb::sha256 &digest) {

    if ( !Commissioner::isAliasAvailable(nt.fantasy_name()) )
    {
        qCritical() << "Processor::process failure: FantasyName(" << nt.fantasy_name().data() << ")  hash already used ";
        return false;
    }


    auto pk = Commissioner::str2pk(nt.public_key());
    auto name = Commissioner::getName(pk);
    if ( name != nullptr ) {
        qCritical() << "verfiy_name failure: FantasyName(" <<
                        nt.fantasy_name().data() << ")  pubkey already n use" <<
                         name->ToString().data();
                        //.append(st.DebugString());

        return false;
    }

    if ( !Commissioner::verify(sig,digest,pk)) {
        if ( !Commissioner::verifyOracle(sig,digest)) {
            qDebug() << "verfiy_name verify failure";
            return false;
        }
    }
    else qDebug() << " ssssss veroify name";

	auto proof = nt.proof();
	switch (proof.type())
	{
		case NameProof_Type_TWEET:
		{
			auto tp = proof.GetExtension(TweetProof::tweet_proof);
			//TODO verify tweet
			return true;
		}
		break;

		case NameProof_Type_ORACLE:
		{
			return true;//TODO
			//verify oracle
			if (!Commissioner::verifyOracle(sig, digest))
#ifdef NO_ORACLE_CHECK_TESTING
			if (!Commissioner::verifyByName(sig, digest, st.fantasy_name()))
#endif
            {
                qCritical() << "Processor::process name proof oracle failed";
                qDebug() << st.DebugString().data();

                return false;
            }
            else
                return true;
		}
		break;

		default:
            return true;
			break;
	}
	/*
	assert(pow.hash() == pfn->hash());
	Commissioner::Hash2Pk.emplace(pow.hash(), pfn->pubkey);
	Commissioner::FantasyNames.emplace(pfn->pubkey, pfn);
	if (nt.has_name_pow())

	else if (nt.has_tweet_proof())
	{
	auto top = nt.tweet_proof();
	pfn->pubkey = Commissioner::str2pk(top.public_key());
	pfn->alias = nt.fantasy_name();
	//assert(pow.hash() == pfn->hash());
	Commissioner::Hash2Pk.emplace(pfn->hash(), pfn->pubkey);
	Commissioner::FantasyNames.emplace(pfn->pubkey, pfn);
	continue;
	}
	*/
}

BlockProcessor::BlockProcessor(NFLStateData &data, FantasyNameData &namedata, ExchangeData &ed) :
    mData(data), mNameData(namedata) , mExchangeData(ed) {}


}

