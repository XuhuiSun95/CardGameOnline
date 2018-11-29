#ifndef GAMELOBBYEHANDLER_H
#define GAMELOBBYEHANDLER_H

#include "GLS/GameLobby.h"
#include "ConfigLoader.h"
#include "Database.h"

class GameLobbyHandler : virtual public GameLobbyIf {

public:
    
    GameLobbyHandler(const Config& cfg, Database* ptr);

private:

    // private variable
    const Config* mConfig;
    Database* mDB;

    // handler
    bool sign_up(const std::string& username, const std::string& password);
    bool sign_in(const std::string& username, const std::string& password);
    void fetch_game(Path& _return, const Game::type g);

};

#endif
