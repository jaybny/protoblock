
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "server.h"
#include "txpool.h"


#include "Commissioner.h"
void sortedPermutations ( char str[] );
#ifdef NOT_NOW
// Driver program to test above function
int main()
{
    char str[] = "ABCD";
    sortedPermutations( str );
    return 0;
}



const unsigned long num_elements = 17;
const unsigned long comb_len = 4;
void combinations_r(const vector<char> &elems, unsigned long req_len);

int main()
{
    vector<char> elements(num_elements);
    char elements_str[num_elements + 1] = "ACEFGHIJKNOPSTUXY";
    copy(elements_str, elements_str + num_elements, elements.begin());

    combinations_r(elements, comb_len);
    cout << " count " << elements.size() << endl;
    return 0;
}


QDebug operator<<(QDebug out, const std::string& str)
{
    out << str.data();
    return out;
}

#endif
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("ProRoto WebSocket server");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: PB_WS_TX_PORT]."),
            QCoreApplication::translate("main", "port"), QLatin1Literal("PB_WS_TX_PORT"));
    parser.addOption(portOption);
    parser.process(a);

    bool debug = parser.isSet(dbgOption);
    int port = parser.value(portOption).toInt();


    TxPool::init();

    qDebug() << " num tx st " << TxPool::myTxSt.size();
    fantasybit::FantasyNameData mNameData;
    mNameData.init();


    for ( auto mnm : Server::myNewNames) {
        if ( mnm.first == "" ) continue;
        if ( TxPool::myTxSt.find(mnm.first) == end(TxPool::myTxSt)) {
            qDebug() << mnm.first << " no tx found " << mnm.second.DebugString().data();
        }
        else qDebug() << mnm.first << "yes tx found " << TxPool::myTxSt[mnm.first].DebugString().data();
    }

    return 0;
    TxServer *txserver = new TxServer(PB_WS_TX_PORT, debug);
    QObject::connect(txserver, &TxServer::closed, &a, &QCoreApplication::quit);

    LiteServer *nameServer = new LiteServer(PB_WS_LITE_AGENT_PORT,debug);
    QObject::connect(nameServer, &LiteServer::closed, &a, &QCoreApplication::quit);

    Server::TheExchange.OnLive(true);

//    ExchangeOrder eo;

//    eo.set_playerid("1");
//    eo.set_type(ExchangeOrder::NEW);

//    OrderCore core;
//    core.set_buyside(true);
//    core.set_size(1);
//    core.set_price(10);

//    eo.mutable_core()->CopyFrom(core);
//    auto fn = Commissioner::getName("JayBNY");

////    Server::TheExchange.OnNewOrderMsg(eo,1,fn);

//    core.set_buyside(false);
//    core.set_size(1);
//    core.set_price(25);
//    eo.mutable_core()->CopyFrom(core);
//    fn = Commissioner::getName("clarity");

//    Server::TheExchange.OnNewOrderMsg(eo,2,fn);


    return a.exec();
}

#ifdef NOT_NOT
static std::map<char,char> CHARMAPS
{
{"B","C"},
{"D","E"},
{"L","N"},
{"M","O"},
{"Q","S"},
{"R","T"},
{"V","X"},
{"W","Y"},
{"Z","A"},
};


void sequnces() {
    static const char* valids = "ACEFGHIJKNOPSTUXY";
    static const char* invalids = "BDLMQRVWZ";
    static const char* invalid2validmap = "CENOSTXYA";

    static const char* maptoperiod = "-_.";

    //weeks:
    //A  C  E  F  G  H  I  J  K  N  O  P  S  T  U  X  Y
    //01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17
    /*
     *
     * 1. get initials - replace invalid chars
     * 2. get unique seq of 0-4 chars from these initials
     * 4. append  initials.unique.year.week
     * */

    std::set<std::string> validInitials;
    for ( char valid1 : valids ) {
        for ( char valid2 : valids ) {
            std::string v;
            v.append(valid1);
            v.append(valid2);
            validInitials.insert(v);
        }
    }
}

std::string convertToValid(char first, char second) {
    std::string v;
    v.append(convertToValid(first));
    v.append(convertToValid(second));
    return v;
}

char convertToValid(char in) {
    if ( srtchr(invalids, in) )
        return CHARMAPS[in];
    else if ( strchr( valids,in) )
        return in;
    else
        return "";
}

std::vector<std::string> orderSequence() {
    std::vector<std::string> ret;
    ret.push_back(".");



}

std::vector<std::string> getValid(int picks) {
    std::vector<std::string> ret;

    for ( auto i : picks ) {
        for ( char valid1 : valids ) {
            for ( char valid2 : valids ) {
                std::string v;
                v.append(valid1);
                v.append(valid2);
                validInitials.insert(v);
            }
        }
    }

    std::string base;
    base.append(".");
    for ( int i = 0; i < picks; i++ ) {
        for ( char valid1 : valids ) {
            return getValid(base + valid1);
        }
    }
    ret.push_back(base + valid1);
    if ( picks < 4)
        return getValid(base, picks+1);
    else
        return ret;
}


#endif
