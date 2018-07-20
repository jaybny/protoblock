/*
//  Node.cpp
//
//  Protoblock
//
//  Created by Jay Berg on 5/21/2018
//
*/
#include "Node.h"
#include <QNetworkReply>
#include <openssl/rand.h>
#include <QTimer>
#include <peerwire.h>
#include <QTimerEvent>


using namespace pb;
using namespace fantasybit;

Q_GLOBAL_STATIC(Node, nodeClient)

static const int NatTestTimerDelay = 5000;

Node *Node::instance()
{
    return nodeClient();
}

Node::Node(QObject *parent) : QTcpServer(parent), http(this)
{}


void Node::init() {
    qRegisterMetaType<PeerWire::DoAction>("PeerWire::DoAction");

    mPeer.set_is_listening(Peer::NOTSURE);
    mPeer.set_port(PORT_DEFAULT);

    mSessionId.ByteSize();

    mSessionId.set_network_id(IS_TEST_NET ? SessionId::TEST : SessionId::PROD);
    mSessionId.set_wire_version(WIRE_VERSION);

    int startupTime = int(QDateTime::currentDateTime().toTime_t());
    mSessionId.set_start_time(startupTime - GENEIS_EPOCH);
    unsigned char buf[6];
    int ret = RAND_bytes(buf, 6);

    if ( ret != 1 )
        qDebug() << " error generating uuid";
    else
        mSessionId.set_uuid(QByteArray((const char *)buf,6).toBase64().toStdString());

    auto s = mSessionId.DebugString();
    qDebug() << s.data();

    mPeerChainStatus.set_chain_state(PeerChainStatus::STARTING);

    pstore.init();
    for ( const auto pp : pstore.peersmm ) {
        Peer *np = new Peer();
        np->CopyFrom(pp.second);
        if ( np->port() == 0 )
            np->set_port(PORT_DEFAULT);
        np->set_is_listening (Peer::YES);
        knownpeers.insert({pp.first,np});
    }

}

Node::~Node() {


}

void Node::startPoint()
{
    init();
    connect(this, &Node::tryGetIp, this, &Node::getMyIp, Qt::QueuedConnection);

    getMyIp();
}

void Node::getMyIp()
{
    if (ipUrlsTry >= IP_URLS.size()) {
        gotPublicIp(false);
        return;
    }

    auto inu = IP_URLS.at(ipUrlsTry);

    QObject::connect(&http, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *qreply) {

                if (qreply->error()) {
                    qDebug() << "err" << qreply->errorString();
                    qreply->deleteLater();
                    qreply->abort();
                    emit tryGetIp();
                }

                else if ( qreply->bytesAvailable() > 0 ) {
                    QString answer = qreply->readAll();

                    qDebug() << "answer" << answer << qreply->isFinished() << answer.trimmed();

                    qreply->deleteLater();
                    qreply->abort();
                    if ( !gotMyIp ) {
                        if ( answer == "")
                            emit tryGetIp();
                        else {
                            mMyAddress = answer.toStdString();
                            qDebug() << " got ip" << mMyAddress.data();
                            gotMyIp = true;
                            gotPublicIp(true);
                        }
                    }
                }
            }
    );

    QString url = inu.data();
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    http.get(req);
    ipUrlsTry++;

    return;
}

void Node::gotPublicIp(bool gotip)  {
    if ( !gotip ) {
        qDebug() << "dont know my ip!";
        mPeer.set_address("");
    }
    else
        mPeer.set_address(mMyAddress);

    startServer();
}


void Node::startServer() {
    connect(this,&QTcpServer::acceptError,
            this, [this] (QAbstractSocket::SocketError socketError) {
                qDebug() << socketError << " tcpserver" << this->errorString();
            });

    // Start the server
    qDebug() << " startserver ";
    if (!this->isListening()) {
        // Set up the peer wire server
        this->listen(QHostAddress::AnyIPv4, PORT_DEFAULT);
        if (!this->isListening()) {
            qDebug() << " !listening " << errorString();
            mPeer.set_is_listening(Peer::NO);
            mPeer.set_port(0);
            return;
        }
        else {
            qDebug() << "server listening " <<
            this->serverAddress() << this->serverPort();
        }
    }

    mPeerChainStatus.set_chain_state(PeerChainStatus::SEARCHING);
    callPeerConnector();
}

void Node::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << " incomingConnection ";
//    PeerWire *client = new PeerWire(PeerWire::Incoming,this);

    Peer *p = new fantasybit::Peer;
    p->set_is_listening(Peer::NOTSURE);
    p->set_port(0);
    p->set_address("");

    PeerWire *client = newPeerWire(p,false);
    if ( client ) client->setSocketDescriptor(socketDescriptor);

//    p->set_address(QHostAddress(qh.toIPv4Address()).toString().toStdString());
//    client->sendIntro();
}

void Node::callPeerConnector()
{
    if (!connectingToClients) {
        connectingToClients = true;
        QTimer::singleShot(10000, this, SLOT(connectToPeers()));
    }
}

inline PeerChainStatus::ChainState Node::getChainState() const {
    return mPeerChainStatus.chain_state();
}

inline void Node::setChainState(const PeerChainStatus::ChainState state) {
    return mPeerChainStatus.set_chain_state(state);
}

void Node::connectToPeers()
{
    connectingToClients = false;

    if (    getChainState() == PeerChainStatus::REORG ||
            getChainState() == PeerChainStatus::STOPPING ||
            getChainState() == PeerChainStatus::ABORTING )
        return;

    if (getChainState() == PeerChainStatus::STARTING || getChainState() == PeerChainStatus::SEARCHING)
        setChainState(PeerChainStatus::CONNECTING);

//    // Find the list of peers we are not currently connected to, where
//    // the more interesting peers are listed more than once.
    std::vector<std::string> freePeers;//{knownpeersbegin(),knownpeers.end()};
    for (const auto &s : knownpeers)
        freePeers.push_back(s.first);

//    for ( )
    std::vector<bool> used;
    used.assign(freePeers.size(),false);
    int remaining = freePeers.size();
    // Start as many connections as we can
    while (m_numoutgoing < MAX_OUTBOUND && remaining > 0) {
//        RateController::instance()->addSocket(client);
//        ConnectionManager::instance()->addConnection(client);

//        initializeConnection(client);
//        d->connections.insert(client);

        // Pick a random peer from the list of weighed peers.
        int index = 0;
        do {
            index = (qrand() % freePeers.size());
            if ( used.at(index) ) {
                index++;
                if ( index >= freePeers.size())
                    index = 0;
            }
        } while (used.at(index));
        remaining--;
        used.at(index) = true;
        auto host = freePeers.at(index);
        if ( host == m_selfkey)
            continue;


//        client->setPeer();
//        peer->connectStart = QDateTime::currentDateTime().toTime_t();
//        peer->lastVisited = peer->connectStart;

        // Connect to the peer.
//        qDebug() << peer->address << peer->port;
//        peer->noConnectTries++;
//        client->setPeer(peer);
        Peer *p = knownpeers[host];
        if ( m_connections.find(p) != end(m_connections) )
            continue;

        PeerWire *client = newPeerWire(p,true);
        client->connectToHost();
    }

//    if ( freePeers.size() == 0 )
    callPeerConnector();
}

void Node::WireConnected() {
    PeerWire *pr = qobject_cast<PeerWire *>(sender());

    if ( pr->PeerState() & PeerWire::Outgoing ) {
        if ( testingnat.find(pr->peer()) != end(testingnat)) {
            if ( m_numoutgoing < MAX_OUTBOUND ) {
                ++m_numoutgoing;
                testingnat.erase(pr->peer());
                emit pr->NewAction(PeerWire::Intro);
            }
            else emit pr->NewAction(PeerWire::NatIntro);
        }
        else {
            ++m_numoutgoing;
            emit pr->NewAction(PeerWire::Intro);
        }
    }
    else ++m_numincomming;
}

void Node::WireDisconnected() {
    PeerWire *pr = qobject_cast<PeerWire *>(sender());

    if ( pr->PeerState() & PeerWire::Outgoing ) {
        if ( testingnat.find(pr->peer()) != end(testingnat)) {
             testingnat.erase(pr->peer());
             qDebug() << "WireDisconnected  Outgoing Nat " << pr->peer()->address().data();
        }
        else {
            qDebug() << "WireDisconnected  Outgoing";
            --m_numoutgoing;
        }
    }
    else {
        qDebug() << "WireDisconnected  InComing";
        --m_numincomming;
    }

    qDebug() << "WireDisconnected" << pr->peer()->DebugString().data();
    qDebug() << "WireDisconnected" << pr->mSessionId.DebugString().data();

}


PeerWire * Node::newPeerWire(Peer *p, bool isOutgoing) {
    PeerWire *client = new PeerWire(isOutgoing ? PeerWire::Outgoing : PeerWire::Incoming,this);

    m_connections.insert({p,client});
    client->setPeer(p);
    client->init();

    connect(client,&PeerWire::NewWireMsg,this,&Node::OnNewWireMsg);
    connect(client,&PeerWire::OnConnected,this,&Node::WireConnected);
    connect(client,&PeerWire::OnDisconnected,this,&Node::WireDisconnected);
    connect(client,&PeerWire::OnTimeout,this,&Node::WireTimeout);

    return client;
}


/*
* Session 1
 *  1. PeerA connect to PeerB
 *  2. PeerA send intro to PeerB
 *             iam.start_time - global session start
 *             youare.start_time - time this socket connected
 * 3. PeerB send intro to PeerA
 *             iam.start_time - global session start
 *             youare.start_time - time this socket connected
 *
 * PeerA is outgoing
 * PeerB is incomming
 *
 * Rule1 - outgoing will initiate disconnect on duplicate
 * Rule2 - on two connecttions most recent outgoing - youare.start_time will disconnect
 *
 * PeerA - OutIntro->youare-starttime  - is used
 * PeerB - InIntro -> youare-starttime  - is used
 *
 *
 * * Session 2
 *  1. PeerB connect to PeerA
 *  2. PeerB send intro to PeerA
 *             iam.start_time - global session start
 *             youare.start_time - time this socket connected
 * 3. PeerA send intro to PeerB
 *             iam.start_time - global session start
 *             youare.start_time - time this socket connected
 *
 * PeerB is outgoing
 * PeerA is incomming
 *
 * Rule1 - outgoing will initiate disconnect on duplicate
 * Rule2 - on two connecttions most recent outgoing - youare.start_time will disconnect
 *
 * PeerB - OutIntro->youare-starttime  - is used
 * PeerA - InIntro -> youare-starttime  - is used
 *
 *
 * Algo to decide:
 *
 * PeerA -  On-OutGoing-InIntroMsg (if OutGoing->OutIntro->youare-starttime > Incoming->InIntro->youare-starttime) disconnect outgoing
 * PeerB -  On-OutGoing-InIntroMsg  (if OutGoing->OutIntro->youare-starttime > Incoming>InIntro->youare-starttime) disconnect outgoing
 *
 * */

void Node::OnNewWireMsg(const WireMsg &msg) {

    switch ( msg.type() ) {
    case MsgType::INTRO: {
        SessionId const& hisid =  msg.intro().iam().session_id();
        SessionId const& myid =  msg.intro().youare().session_id();

        Peer const& hpeer =  msg.intro().iam().peer();
        Peer const& mpeer =  msg.intro().youare().peer();
        PeerWire *pr = qobject_cast<PeerWire *>(sender());

        //check self connection
        if ( hisid.uuid() == mSessionId.uuid()) {
            qDebug() << " connected to self " << pr->PeerState();

            emit pr->NewAction(PeerWire::Disconnect);

            if ( pr->PeerState() & PeerWire::Incoming)
                m_selfkey = PeerIpPort(mpeer);

            return;
        }

        //now i know im listening - and not somehow self connecting
        if ( mPeer.is_listening() != Peer::YES && (pr->PeerState() & PeerWire::Incoming) ) {
            mPeer.set_is_listening(Peer::YES);
            emit ListeningStateChange();
        }

        if ( hisid.uuid() == "NAT" ) {
            if ( mPeer.is_listening() != Peer::NO && mpeer.is_listening() == Peer::NO ) {
                mPeer.set_is_listening(Peer::NO);
                emit ListeningStateChange();
            }

            return;
        }

        if ( hisid.network_id() != mSessionId.network_id() || hisid.wire_version() != mSessionId.wire_version()) {
            qDebug() << " bad id disconnect" << hisid.DebugString().data();

            if ( pr->PeerState() & PeerWire::Incoming )
                emit pr->NewAction(PeerWire::Intro);
            else
                emit pr->NewAction(PeerWire::Disconnect);

            break;
        }

        auto uit = m_connectedUUID.find(hisid.uuid());
        bool knowuuid = ( uit != end(m_connectedUUID));

        pr->mInIntro = msg.intro();
        if ( pr->PeerState() & PeerWire::Incoming ) {
            std::string hispaddress = PeerIpPort(hpeer);
            auto pit = knownpeers.find(hispaddress);
            bool knowp = ( pit != end(knownpeers));

            auto pp = m_connections.find(pr->peer());
            bool haveconn = (pp != end(m_connections));

            if ( !haveconn ) {
                qCritical() << " should be connected ";
                emit pr->NewAction(PeerWire::Disconnect);
            }
            else if ( pr != pp->second ){
                qCritical() << " is diff connection ";
                emit pr->NewAction(PeerWire::Disconnect);
            }
            else if ( !knowuuid ) {  //normal case
                m_connectedUUID.insert({hisid.uuid(),pr->peer()});
                pr->mSessionId.set_uuid(hisid.uuid());
                if ( hpeer.is_listening() == Peer::NO) {
                    pr->peer()->set_is_listening(Peer::NO);
                }
                else if ( hpeer.is_listening() == Peer::YES ) {
                    if ( !knowp ) {
                        AddKnownPeer(hispaddress,pr->peer());
//                        knownpeers.insert({hispaddress,pr->peer()});
                        //emit newPeer(*pr->peer()); ToDo:
                    }
                    pr->peer()->set_is_listening(Peer::ITHINKSO);
                }
                else if ( hpeer.is_listening() == Peer::NO )
                   pr->peer()->set_is_listening(Peer::NO);

                else if ( hpeer.is_listening() == Peer::NOTSURE) {
                    if ( hispaddress == m_selfkey )
                        pr->peer()->set_is_listening(Peer::NO);
                    else {
                        qDebug() << "queue nat test ";
                        //do connect test
                        m_pending_nat_test.push(pr);
                        if (!m_pendingNatTimer)
                            m_pendingNatTimer = startTimer(NatTestTimerDelay);
                   }
                }

                emit pr->NewAction(PeerWire::Intro);
            }
            else if ( !(pr->PeerState() & PeerWire::Outgoing) ) {
                if ( uit->second == pr->peer() ) {
                    qCritical() << "a should never be here - same address differnt peer pointer" ;
//                    pr->diconnectFromHost();
                    break;
                }

                if ( myid.uuid() == mSessionId.uuid() ) {
                    qCritical() << "b should never be here - he shouldnt not know me yet";
//                    break;
                }

                if ( !knowp ) {
                    qCritical() << "c should never be here - i should know this peer";
                    break;
                }

                auto c2 = m_connections.find(uit->second);
                if ( c2 == end(m_connections)) {
                    qCritical() << "d should never be here - should have other connection";
                    break;
                }

                PeerWire *out = c2->second;
                if ( out->mSessionId.uuid() != hisid.uuid())
                    qCritical() << "e should never be here - hisid incoming should be out.sessionid";
                else if ( out->PeerState() & PeerWire::Incoming)
                    qCritical() << "f should never be here - out should be out";
                else {
                    pr->SetPeerState(pr->PeerState() | PeerWire::Outgoing);
                    out->SetPeerState(out->PeerState() | PeerWire::Incoming);

                    pr->mSessionId.set_uuid (out->mInIntro.iam ().session_id ().uuid ());
                    pr->setPeer(out->peer());
                    emit pr->NewAction(PeerWire::Intro);

                    if ( out->mInIntro.youare ().session_id ().start_time () > pr->mSessionId.start_time () )
                        emit out->NewAction(PeerWire::Disconnect);
                }
            }
            else {
                if ( myid.uuid() != mSessionId.uuid())
                    qCritical() << "g should never be here - he should know me by now";
                emit pr->NewAction(PeerWire::Hello);
            }
        }
        else {
            std::string peeradd = PeerIpPort(*pr->peer ());
            auto pita = knownpeers.find(peeradd);
            bool knowpa = ( pita != end(knownpeers));

            if ( !knowpa ) // connected to peer, but have not added to known hosts yet
                AddKnownPeer(peeradd,pr->peer());

            auto natit = testingnat.find(pr->peer());
            if ( natit != end(testingnat)) {
//                testingnat.erase(natit);
                emit pr->NewAction(PeerWire::Disconnect);
                break;
            }

            if (knowuuid ) {
                auto c2 = m_connections.find(uit->second);
                if ( c2 == end(m_connections)) {
                    qCritical() << "d2 should never be here - should have connection 1";
                    break;
                }

                PeerWire *in = c2->second;
                if ( in->mSessionId.uuid() != hisid.uuid())
                    qCritical() << "e2 should never be here hisid outgoing should be in.sessionid";
                else if ( in->PeerState() & PeerWire::Outgoing)
                    qCritical() << "f2 should never be here in should be in";
                else {
                    //disconnect one of the connections
                    pr->SetPeerState(pr->PeerState() | PeerWire::Incoming);
                    in->SetPeerState(in->PeerState() | PeerWire::Outgoing);

                    pr->mSessionId.set_uuid (in->mOutIntro.youare().session_id().uuid ());

                    if ( pr->mOutIntro.youare ().session_id ().start_time () > in->mInIntro.youare ().session_id ().start_time () ) {
                        in->SetPeerState(in->PeerState() | PeerWire::Outgoing);
                        emit pr->NewAction(PeerWire::Disconnect);
                    }
                }
            }
//                * PeerA -  On-OutGoing-InIntroMsg (if OutGoing->OutIntro->youare-starttime > Incoming->InIntro->youare-starttime) disconnect outgoing
            else { //outgoing new connection
                if ( hpeer.address () == mMyAddress ) {
                    //someone else on my network is listening
                    if ( PeerIpPort(mPeer) == PeerIpPort (hpeer)) {
                        if ( mPeer.is_listening () != Peer::NO ) {
                            mPeer.set_is_listening(Peer::NO);
                            emit ListeningStateChange();
                        }
                    }
                }

                if ( mpeer.is_listening() == Peer::NO && mPeer.is_listening() == Peer::NOTSURE) {
                    mPeer.set_is_listening(Peer::NO);
                    emit ListeningStateChange();
                }

                m_connectedUUID.insert({hisid.uuid(),pr->peer()});
                pr->mSessionId.set_uuid (hisid.uuid ());
                emit pr->NewAction(PeerWire::Hello);
            }

        }
    }
    default:
        break;
    }

    qDebug() << " OnNewWireMsg " << msg.DebugString().data();
}


void Node::timerEvent(QTimerEvent *event) {
    if ( event->timerId() == m_pendingNatTimer ) {
        PeerWire * pr = m_pending_nat_test.front ();
        Peer natpeer = pr->mInIntro.iam().peer();
        m_pending_nat_test.pop ();

        if ( m_pending_nat_test.empty() )
            killTimer(m_pendingNatTimer);

        bool haveconn = false;

        auto pit = knownpeers.find(PeerIpPort(natpeer));
        bool knowp = ( pit != end(knownpeers));

        if ( knowp ) {
            auto pp = m_connections.find(pit->second);
            bool haveconn = (pp != end(m_connections));
        }

        if ( !haveconn ) {
            Peer *p;

            if ( knowp )
                p = pit->second;
            else {
                p = new fantasybit::Peer();
                p->CopyFrom (natpeer);
                p->set_is_listening (Peer::YES);
            }

//            if ( m_numoutgoing >= MAX_OUTBOUND)
            testingnat.insert (p);

            PeerWire *client = newPeerWire(p,true);
            connect(client,&PeerWire::OnTimeout,pr,&PeerWire::NatTimeout,Qt::QueuedConnection);
            client->connectToHost ();
        }
    }
}

decltype(pb::Node::IP_URLS) pb::Node::IP_URLS {
    "http://api.ipify.org/",
    "http://myexternalip.com/raw",
    "http://icanhazip.com/",
     "http://myip.dnsomatic.com/",
     "http://ifcaonfig.me/ip"
};

//decltype (pb::Node::mSessionId) pb::Node::mSessionId{};
//decltype (pb::Node::mPeer)      pb::Node::mPeer{};