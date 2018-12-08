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

    mCG->Run();
}

SystemManager::SystemManager(const std::string& config_path) {

    ConfigLoader* cfg_loader = ConfigLoader::Instance(config_path, mConfig);
    if(!cfg_loader->LoadConfig())
        exit(1);
    cfg_loader->PrintConfig();
    ConfigLoader::Release();
    cfg_loader = nullptr;

    mCG = CardGameServer::Instance(mConfig);
}

SystemManager::~SystemManager() {

    CardGameServer::Release();
    mCG = nullptr;
}
