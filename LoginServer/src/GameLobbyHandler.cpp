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

void GameLobbyHandler::fetch_game(Path& _return, const Game::type g) {

    switch(g) {
        case Game::DOUDIZHU:
            _return.host = mConfig->doudizhu_host;
            _return.port = mConfig->doudizhu_port;
            break;
        default:
            break;
    }
}
