#ifndef GAMELOBBYEHANDLER_H
#define GAMELOBBYEHANDLER_H

#include <mutex>
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
    std::vector<Game> mGames;
    std::mutex list_mtx;

    // handler
    bool sign_up(const std::string& username, const std::string& password);
    bool sign_in(const std::string& username, const std::string& password);
    void add_game(const Game& g);
    void fetch_games(std::vector<Game>& _return);

};

#endif
