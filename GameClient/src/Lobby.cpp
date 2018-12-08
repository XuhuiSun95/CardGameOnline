#include "Lobby.h"

Lobby::Lobby(QGraphicsScene *ptr, boost::shared_ptr<apache::thrift::transport::TTransport> trans, GameLobbyClient* clt) {

    mScene = ptr;
    transport = trans;
    client = clt;
}

void Lobby::display_lobby_menu() {

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

void Lobby::connect_game(Game g) {

    // Clear all
    mScene->clear();

    // connect game server
    // fetch table info
    std::vector<bool> info = {false, true, false};

    // Game title
    QGraphicsTextItem* lobbyText = new QGraphicsTextItem(QString::fromStdString(g.name));
    QFont titleFont("Clarendon", 30);
    lobbyText->setFont(titleFont);
    double txPos = mScene->width()/2 - lobbyText->boundingRect().width()/2;
    double tyPos = mScene->height()/15;
    lobbyText->setPos(txPos,tyPos);
    mScene->addItem(lobbyText);

    // render tables
    Table* table1 = new Table(mScene, 1);
    double ixPos = mScene->width()/10*2 - table1->boundingRect().width()/2;
    double iyPos = mScene->height()/10*5;
    table1->setPos(ixPos,iyPos);
    mScene->addItem(table1);
    table1->upate_slots(info);



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
