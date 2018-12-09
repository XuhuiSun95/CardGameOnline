#ifndef LOBBYMANAGER_H
#define LOBBYMANAGER_H

#include "GLS/GameLobby.h"
#include "TableManager.h"

class LobbyManager : public QObject {
    Q_OBJECT
public:

    LobbyManager(QGraphicsScene* ptr, boost::shared_ptr<apache::thrift::transport::TTransport> trans, GameLobbyClient* clt);

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
