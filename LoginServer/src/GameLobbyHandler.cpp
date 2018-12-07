#include "GameLobbyHandler.h"

GameLobbyHandler::GameLobbyHandler(const Config& cfg, Database* ptr) {

    mConfig = &cfg;
    mDB = ptr;
}

bool GameLobbyHandler::sign_up(const std::string& username, const std::string& password) {

    int res = mDB->sign_up(username, password);
    switch(res) {
        case 0:
            return true;
        case 101:
            {
                InvalidOperation io;
                io.err_code = 101;
                io.why = "username exist";
                throw io;
            }
        case 1:
            {
                InvalidOperation io;
                io.err_code = 1;
                io.why = "system busy";
                throw io;
            }
        default:
            return false;
    }
}

bool GameLobbyHandler::sign_in(const std::string& username, const std::string& password) {

    int res = mDB->sign_in(username, password);
    switch(res) {
        case 0:
            return true;
        case 202:
            {
                InvalidOperation io;
                io.err_code = 202;
                io.why = "username/password not match";
                throw io;
            }
        case 201:
            {
                InvalidOperation io;
                io.err_code = 201;
                io.why = "username not exist";
                throw io;
            }
        case 1:
            {
                InvalidOperation io;
                io.err_code = 1;
                io.why = "system busy";
                throw io;
            }
        default:
            return false;
    }
}

void GameLobbyHandler::add_game(const Game& g) {

    list_mtx.lock();
    mGames.push_back(g);
    list_mtx.unlock();
}

void GameLobbyHandler::fetch_games(std::vector<Game>& _return) {

    _return = mGames;
}
