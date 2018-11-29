#include "SystemManager.h"

SystemManager* SystemManager::sInstance = nullptr;

SystemManager* SystemManager::Instance(const std::string& config_path) {

    if(sInstance==nullptr)
        sInstance = new SystemManager(config_path);

    return sInstance;
}

void SystemManager::Release() {

    delete sInstance;
    sInstance = nullptr;
}

void SystemManager::Run() {

    mGL->Run();
}

SystemManager::SystemManager(const std::string& config_path) {

    ConfigLoader* cfg_loader = ConfigLoader::Instance(config_path, mConfig);
    if(!cfg_loader->LoadConfig())
        exit(1);
    cfg_loader->PrintConfig();
    ConfigLoader::Release();
    cfg_loader = nullptr;

    mDB = Database::Instance(mConfig);
    mGL = GameLobbyServer::Instance(mConfig, mDB);
}

SystemManager::~SystemManager() {

    Database::Release();
    mDB = nullptr;

    GameLobbyServer::Release();
    mGL = nullptr;
}
