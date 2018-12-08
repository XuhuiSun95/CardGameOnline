#ifndef CARDGAMESERVER_H
#define CARDGAMESERVER_H

#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/transport/TSocket.h>
#include "CardGameHandler.h"
#include "GLS/GameLobby.h"

class CardGameServer {

public:

    static CardGameServer* Instance(const Config& cfg);
    static void Release();

    void Run();

private:

    static CardGameServer* sInstance;

    // private variable
    const Config* mConfig;
    static const int THREAD_NUM;
    boost::shared_ptr<CardGameHandler> handler;
    boost::shared_ptr<apache::thrift::TProcessor> processor;
    boost::shared_ptr<apache::thrift::protocol::TProtocolFactory> protocolFactory;
    boost::shared_ptr<apache::thrift::concurrency::ThreadManager> threadManager;
    boost::shared_ptr<apache::thrift::concurrency::PosixThreadFactory> threadFactory;

    CardGameServer(const Config& cfg);
    ~CardGameServer();

};

#endif
