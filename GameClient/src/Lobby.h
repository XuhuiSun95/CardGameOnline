#ifndef LOBBY_H
#define LOBBY_H

#include <thrift/transport/TBufferTransports.h>
#include "GLS/GameLobby.h"
#include "Button.h"
#include "Card.h"
#include "Table.h"

class Lobby : public QObject {
    Q_OBJECT
public:

    Lobby(QGraphicsScene* ptr, boost::shared_ptr<apache::thrift::transport::TTransport> trans, GameLobbyClient* clt);

    void display_lobby_menu();

private:

    QGraphicsScene* mScene;
    QWidget* mParent;
    boost::shared_ptr<apache::thrift::transport::TTransport> transport;
    GameLobbyClient* client;
    std::vector<Game> mGames;

private slots:

    void connect_game(Game g);

};

#endif // LOBBY_H
