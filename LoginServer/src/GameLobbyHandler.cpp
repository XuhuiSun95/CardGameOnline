#include "GameLobbyHandler.h"

GameLobbyHandler::GameLobbyHandler(const Config& cfg, Database* ptr) {

    mConfig = &cfg;
    mDB = ptr;
}

bool GameLobbyHandler::sign_up(const std::string& username, const std::string& password) {

    std::cout << "sign up:" << std::endl;
    std::cout << username << "|" << password << std::endl;
    return true;
}

bool GameLobbyHandler::sign_in(const std::string& username, const std::string& password) {

    std::cout << "sign in:" << std::endl;
    std::cout << username << "|" << password << std::endl;
    return true;
}

void GameLobbyHandler::fetch_game(Path& _return, const Game::type g) {

    switch(g) {
        case Game::DOUDIZHU: {  _return.host = mConfig->doudizhu_host;
                                 _return.port = mConfig->doudizhu_port;
                                 break;
                             }
        default: break;
    }
}
