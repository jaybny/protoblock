/*
//  peer.h
//
//  Protoblock
//
//  Created by Jay Berg on 5/7/2018
//
*/
#ifndef PEER_H
#define PEER_H

#include <leveldb/db.h>
#include <mutex>
#include <unordered_map>
#include "P2PData.pb.h"
#include <QDebug>

namespace pb {

using fantasybit::Peer;

//struct peerdb {
//   std::string address;
//   int64_t     epoch;
//};

static int PORT_HAND = 10130;
static int PORT_SYNC_SERV = 10125;
static int PORT_LIVE_BLOCK = 10126;
static int PORT_LIVE_TX = 10127;
static int PORT_LIVE_TX_NAT = 10128;

static std::string ROOT_DIR_("C:/fantasybit/");

static std::string GET_ROOT_DIR() {
    return ROOT_DIR_;
}

static std::string FB_PORT(int port) {
    return std::string(":").append(std::to_string(port));
}

class peer {

    std::auto_ptr<leveldb::DB> peersdb;
    std::mutex ldb_mutex;
    leveldb::WriteOptions write_sync;
//    typename T::memtype memmap;
//    typename T::pbufty pbufmsg;

    std::unordered_map<std::string, Peer> peersmm;
    Peer peerbuf;

public:
    peer() {
        write_sync.sync = true;
    }

    void init() {
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status;
        leveldb::DB *db;
        qDebug() << "peer::init open ldb" << filedir("peers").data();

        if ( leveldb::DB::Open(options, filedir("peers"), &db).ok() ) {
            peersdb.reset(db);

            auto *it = peersdb->NewIterator(leveldb::ReadOptions());
            for (it->SeekToFirst(); it->Valid(); it->Next()) {
                peersmm[it->key().ToString()].ParseFromArray(it->value().data(),it->value().size());
            }
        }
    }

    std::string filedir(const std::string &in) {
        return GET_ROOT_DIR() + in;
    }

    bool add2mem(const std::string &key, const Peer& inp) {
        peersdb->Put(write_sync, key, inp.SerializeAsString());

        peersmm[key] = inp;
    }
};

}
#endif // PEER_H
