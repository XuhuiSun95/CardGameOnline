#include "GameLobbyServer.h"

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::concurrency;
using namespace ::apache::thrift::server;

GameLobbyServer* GameLobbyServer::sInstance = nullptr;
const int GameLobbyServer::THREAD_NUM = 12;

GameLobbyServer* GameLobbyServer::Instance(const Config& cfg, Database* ptr) {

    if(sInstance==nullptr)
        sInstance = new GameLobbyServer(cfg, ptr);

    return sInstance;
}

void GameLobbyServer::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void GameLobbyServer::Run() {

    TNonblockingServer server(processor, protocolFactory, mConfig->server_port, threadManager);
    server.serve();
}

GameLobbyServer::GameLobbyServer(const Config& cfg, Database* ptr) :
    handler(new GameLobbyHandler(cfg, ptr)), 
    processor(new GameLobbyProcessor(handler)), 
    protocolFactory(new TCompactProtocolFactory()) {

    mConfig = &cfg;
    threadManager = ThreadManager::newSimpleThreadManager(THREAD_NUM);
    threadFactory = boost::shared_ptr<PosixThreadFactory> (new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
}

GameLobbyServer::~GameLobbyServer() {
}
