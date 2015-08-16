//
//  client.cpp
//  cute-fantasy
//
//  Created by Jay Berg on 4/8/14.
//
//
#include "client.h"
#include <nanomsg/pair.h>
#include <MsgSock.h>
#include <string>
#include <ProtoData.pb.h>
#include <QDebug>
#include <QProcess>
#include <QCoreApplication>
#include <iostream>

using namespace fantasybit;
using namespace std;

Client::Client(const string &a, QObject *parent) :
                    address(a),
                    QObject(parent) , sock {AF_SP, NN_PAIR},
                    receiver{sock}, timer(new QTimer(this)), timer2(new QTimer(this))
{
    //hbdata.set_type(InData_Type_HEARTBEAT);
    connect(timer2, SIGNAL(timeout()), this, SLOT(pollServer()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(heartbeat()));
    connect(this, SIGNAL(doPoll()), this, SLOT(pollServer()));
}

bool Client::event(QEvent *ev)
{
    if  (ev->type() == QEvent::ThreadChange)
    {
        QTimer::singleShot(0, this, SLOT(start()));
    }

    return QObject::event(ev);
}

void Client::start() {
    try {
        dostart();
    }
    catch(...) {}
}

//slots
void Client::dostart()
{

    //InData ind{};
    sock.connect(address.c_str());
    //indata.set_type(InData_Type_CONNECT);
    //Sender::Send(sock,indata);
    //timer->start(10000);
    timer2->start(500);
    emit doPoll();


}

void Client::toServer(const InData &in)
{
    try {
        Sender::Send(sock,in);
    }
    catch(...) {}
}

void Client::pollServer()
{
    try {
        if ( receiver.receive(outdata,NN_DONTWAIT))
        {
            //std::cout << outdata.DebugString() << " \n";
            qDebug() << QString::fromStdString(outdata.DebugString());
            emit onData(outdata);
        }
    }
    catch(...) {}
    //emit doPoll();
}

void Client::quit()
{
    //indata.set_type(InData_Type_QUIT);
    //Sender::Send(sock,indata);
    //nn::term();
}
