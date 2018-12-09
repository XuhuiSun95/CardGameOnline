#include "LobbyManager.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using boost::shared_ptr;

LobbyManager::LobbyManager(QGraphicsScene *ptr, boost::shared_ptr<apache::thrift::transport::TTransport> trans, GameLobbyClient* clt) {

    mScene = ptr;
    transport = trans;
    client = clt;
}

void LobbyManager::display_lobby_menu() {

    // Clear all
    mScene->clear();

    // Lobby title
    QGraphicsTextItem* lobbyText = new QGraphicsTextItem(QString("Available Games"));
    QFont titleFont("Clarendon", 50);
    lobbyText->setFont(titleFont);
    double txPos = mScene->width()/2 - lobbyText->boundingRect().width()/2;
    double tyPos = mScene->height()/5;
    lobbyText->setPos(txPos,tyPos);
    mScene->addItem(lobbyText);

    // Update&display game list
    try {
        transport->open();

        client->fetch_games(mGames);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    transport->close();

    int h = 4;
    for(int i=0; i<mGames.size(); i++) {

        // create the game button
        Button* gameButton = new Button(QString::fromStdString(mGames[i].name),200,50);
        double ixPos = mScene->width()/2 - gameButton->boundingRect().width()/2;
        double iyPos = mScene->height()/10*h;
        h++;
        gameButton->setPos(ixPos,iyPos);
        connect(gameButton, &Button::clicked, this, [this, i]{ connect_game(mGames[i]); });
        mScene->addItem(gameButton);
    }

    // Refresh button
    Button* refreshButton = new Button(QString("Refresh"),200,50);
    double ixPos = mScene->width()/10*8 - refreshButton->boundingRect().width()/2;
    double iyPos = mScene->height()/10;
    refreshButton->setPos(ixPos,iyPos);
    connect(refreshButton, &Button::clicked, this, [this]{ display_lobby_menu(); });
    mScene->addItem(refreshButton);
}

void LobbyManager::connect_game(Game g) {

    // Clear all
    mScene->clear();

    // connect game server
    boost::shared_ptr<TTransport> g_socket(new TSocket(g.host, g.port));
    boost::shared_ptr<TTransport> g_transport(new TFramedTransport(g_socket));
    boost::shared_ptr<TProtocol> g_protocol(new TCompactProtocol(g_transport));
    CardGameClient g_client(g_protocol);

    // fetch table info
    std::vector<Table> info;
    try {
        g_transport->open();

        g_client.fetch_tables(info);
        g_transport->close();

    } catch (const std::exception& e) {
        g_transport->close();
        std::cout << e.what() << std::endl;
    }

    // Game title
    QGraphicsTextItem* lobbyText = new QGraphicsTextItem(QString::fromStdString(g.name));
    QFont titleFont("Clarendon", 30);
    lobbyText->setFont(titleFont);
    double txPos = mScene->width()/2 - lobbyText->boundingRect().width()/2;
    double tyPos = mScene->height()/50;
    lobbyText->setPos(txPos,tyPos);
    mScene->addItem(lobbyText);

    // Refresh button
    Button* refreshButton = new Button(QString("Refresh"),200,50);
    double ixPos = mScene->width()/10*8 - refreshButton->boundingRect().width()/2;
    double iyPos = mScene->height()/50;
    refreshButton->setPos(ixPos,iyPos);
    connect(refreshButton, &Button::clicked, this, [this, g]{ connect_game(g); });
    mScene->addItem(refreshButton);

    // render tables
    for(int i=0; i<info.size(); i++) {
        TableManager* t = new TableManager(mScene, g, i);
        double ixPos = mScene->width()/10*(1+4*(i%3)) - t->boundingRect().width()/2;
        double iyPos = mScene->height()/10*(2+3*(i/3));
        t->setPos(ixPos,iyPos);
        mScene->addItem(t);
        t->upate_slots(info[i].slot);
    }

/*
    std::cout << g.name << std::endl;
    Card* c = new Card("BackBlue");
    c->setPos(190, 300);
    mScene->addItem(c);

    Card* c2 = new Card("Spade2");
    c2->setPos(200, 300);
    mScene->addItem(c2);

    Card* c3 = new Card("Heart5");
    c3->setPos(210, 300);
    mScene->addItem(c3);
*/
}
