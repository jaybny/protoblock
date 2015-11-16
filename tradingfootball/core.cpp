#include "core.h"
#include <iostream>
#include "ApiData.pb.h"


Core::Core(){}
void Core::bootstrap(){

    qRegisterMetaType<fantasybit::GlobalState>("fantasybit::GlobalState");
    qRegisterMetaType<fantasybit::MyFantasyName>("fantasybit::MyFantasyName");
    qRegisterMetaType<fantasybit::FantasyBitProj>("fantasybit::FantasyBitProj");
    qRegisterMetaType<vector<fantasybit::FantasyBitProj>>("vector<fantasybit::FantasyBitProj>");
    qRegisterMetaType<vector<fantasybit::MyFantasyName>>("vector<fantasybit::MyFantasyName>");
    qRegisterMetaType<pair<string,fantasybit::PlayerStatus>>("pair<string,fantasybit::PlayerStatus>");
    qRegisterMetaType<fantasybit::PlayerStatus>("fantasybit::PlayerStatus");
    qRegisterMetaType<fantasybit::FantasyNameBal>("fantasybit::FantasyNameBal");
    qRegisterMetaType<fantasybit::GameStatus_Status>("fantasybit::GameStatus_Status");
    qRegisterMetaType<fantasybit::Distribution>("fantasybit::Distribution");
    qRegisterMetaType<fantasybit::FantasyNameHash>("fantasybit::FantasyNameHash");
    qRegisterMetaType<int32_t>("int32_t");


    qRegisterMetaType<string>("string");
    qSetMessagePattern(AppSettings::instance()->getSetting(AppSettings::LogMessagePattern).toString());
    qInstallMessageHandler(messageHandler);
    registerNamedInstance("coreapi",myCoreApi.object());
    QObject::connect(myCoreApi.thread(),SIGNAL(started()),myCoreApi.object(),SLOT(startPoint()));
    myCoreApi.thread()->start();
}

void Core::waitForGui(){
    myWaitForGuiMutex.lock();
    myWaitForGUI.wait(&myWaitForGuiMutex);
}

void Core::guiIsAwake(){
    myWaitForGUI.wakeAll();
}

Core::~Core(){}

void messageHandler(QtMsgType type,
                    const QMessageLogContext &context,
                    const QString &message)
{

#ifndef ALLOW_DEBUG
    return;
#else
    static QMutex messageHandlerMutex ;
    QMutexLocker lock(&messageHandlerMutex);
    QString logFileName = AppSettings::instance()->getSetting(AppSettings::LogFilePath).toString();
    static std::ofstream  logFile(logFileName.toStdString(),std::ofstream::app);
    if (logFile)
        logFile << qPrintable(qFormatLogMessage(type,context, message))<< std::endl;
#endif

#ifdef QT_DEBUG    
 //   std::cerr  << qPrintable(qFormatLogMessage(type,context, message))<< std::endl;

#endif

    /**/
}

