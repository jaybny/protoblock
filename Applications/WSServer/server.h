#ifndef SERVER_H
#define SERVER_H

#include "StateData.pb.h"
#include "TxServer.h"
#include "LiteServer.h"
#include "ExchangeData.h"
#include "Data.h"

using namespace fantasybit;

class Server {
public:
    static fantasybit::GetAllNamesRep AllNamesRep;
    static fantasybit::ExchangeData TheExchange;
//    static fantasybit::GetROWMarketRep ROWMarketRep;
    static NFLStateData  NFLData;
    static std::unordered_map<std::string,FantasyNameBal *> Pk2Bal;

    static void AddNames(const FantasyNameBal &fnb) {
        Server::AllNamesRep.add_names(fnb.name());
        FantasyNameBal *p = Server::AllNamesRep.add_fnb();
        p->CopyFrom(fnb);
        Pk2Bal.insert({fnb.public_key(),p});
    }

    static void AddNames(FantasyNameBal *pFn) {
        Server::AllNamesRep.add_names(pFn->name());
        Server::AllNamesRep.mutable_fnb()->AddAllocated(pFn);
        Pk2Bal.insert({pFn->public_key(),pFn});

    }
};


#endif //SERVER_H
