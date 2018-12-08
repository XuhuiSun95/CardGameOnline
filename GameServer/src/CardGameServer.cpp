#include "CardGameServer.h"

using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::concurrency;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::transport;

CardGameServer* CardGameServer::sInstance = nullptr;
const int CardGameServer::THREAD_NUM = 8;

CardGameServer* CardGameServer::Instance(const Config& cfg) {

    if(sInstance==nullptr)
        sInstance = new CardGameServer(cfg);

    return sInstance;
}

void CardGameServer::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void CardGameServer::Run() {

    boost::shared_ptr<TTransport> socket(new TSocket(mConfig->login_host, mConfig->login_port));
    boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TCompactProtocol(transport));
    GameLobbyClient client(protocol);

    try {
        transport->open();
    
        Game g;
        g.name = mConfig->game_name;
        g.host = "127.0.0.1";
        g.port = mConfig->game_port;
        client.add_game(g);
    
    } catch (const std::exception& e) {
        transport->close();
        std::cout << e.what() << std::endl;
        exit(1);
    }
    transport->close();

    TNonblockingServer server(processor, protocolFactory, mConfig->game_port, threadManager);
    server.serve();
}

CardGameServer::CardGameServer(const Config& cfg) :
    handler(new CardGameHandler(cfg)), 
    processor(new CardGameProcessor(handler)), 
    protocolFactory(new TCompactProtocolFactory()) {

    mConfig = &cfg;
    threadManager = ThreadManager::newSimpleThreadManager(THREAD_NUM);
    threadFactory = boost::shared_ptr<PosixThreadFactory> (new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();
}

CardGameServer::~CardGameServer() {
}
