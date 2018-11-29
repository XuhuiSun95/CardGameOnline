#ifndef GAMELOBBYSERVER_H
#define GAMELOBBYSERVER_H

#include "GameLobbyHandler.h"
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/concurrency/PosixThreadFactory.h>

class GameLobbyServer {

public:

    static GameLobbyServer* Instance(const Config& cfg, Database* ptr);
    static void Release();

    void Run();

private:

    static GameLobbyServer* sInstance;

    // private variable
    const Config* mConfig;
    static const int THREAD_NUM;
    boost::shared_ptr<GameLobbyHandler> handler;
    boost::shared_ptr<apache::thrift::TProcessor> processor;
    boost::shared_ptr<apache::thrift::protocol::TProtocolFactory> protocolFactory;
    boost::shared_ptr<apache::thrift::concurrency::ThreadManager> threadManager;
    boost::shared_ptr<apache::thrift::concurrency::PosixThreadFactory> threadFactory;

    GameLobbyServer(const Config& cfg, Database* ptr);
    ~GameLobbyServer();

};

#endif
