#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <cstdlib>
#include "ConfigLoader.h"
#include "CardGameServer.h"

class SystemManager {

public:
    
    static SystemManager* Instance(const std::string& config_path);
    static void Release();

    void Run();

private:

    static SystemManager* sInstance;

    // private variables
    Config mConfig;
    CardGameServer* mCG;

    SystemManager(const std::string& config_path);
    ~SystemManager();

};

#endif
