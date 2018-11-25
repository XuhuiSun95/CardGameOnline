#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <cstdlib>
#include "ConfigLoader.h"
#include "Database.h"
//#include "RTSP.h"

class SystemManager {

public:
    
    static SystemManager* Instance(const std::string& config_path);
    static void Release();

    void Run();

private:

    static SystemManager* sInstance;

    // private variables
    Config mConfig;
    Database* mDB;
    //RTSP* mRTSP;

    SystemManager(const std::string& config_path);
    ~SystemManager();

};

#endif
