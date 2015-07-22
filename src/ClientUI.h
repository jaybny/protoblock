//
//  ClientUI.h
//  fantasybit
//
//  Created by Jay Berg on 4/5/14.
//
//

#ifndef __fantasybit__ClientUI__
#define __fantasybit__ClientUI__

#include "nn.hpp"
#include <nanomsg/pair.h>
#include <assert.h>
#include <string>
#include "ProtoData.pb.h"
#include <iostream>

#include "boostLog.h"
#define LOG(logger, severity) LOGIT(logger, severity,  __FILE__, __LINE__, __FUNCTION__)

namespace fantasybit
{

class ClientUI
{
    nn::socket sockserv, sockgui, sockdelta;
public:
    ClientUI(std::string addrserv,std::string addrgui,std::string addrdelta)
		: sockserv{ AF_SP, NN_PAIR }, sockgui{ AF_SP, NN_PAIR }, sockdelta{AF_SP, NN_PAIR}
    {
		int timeout = 5000;
		sockserv.setsockopt(NN_SOL_SOCKET, NN_RCVTIMEO, &timeout, sizeof(timeout));

		sockdelta.bind(addrdelta.c_str());
		LOG(lg, trace) << "connect server" << addrserv;

        sockserv.connect(addrserv.c_str());
		LOG(lg, trace) << "connect server" << addrserv;

        sockgui.bind(addrgui.c_str());
		LOG(lg, trace) << "bind gui" << addrgui;

    }
    void run();
    void runit();

    void stop()
    {
        running = false;
    }
    
private:
    volatile bool running = true;
};

}

#endif /* defined(__fantasybit__ClientUI__) */
