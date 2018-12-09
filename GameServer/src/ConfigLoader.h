#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <iostream>
#include "INIReader.h"

struct Config {

    // Service
    std::string login_host;
    int login_port;
    std::string game_name;
    int game_port;

    // Lobby
    int table_size;
    int slot_size;
};

class ConfigLoader {

public:
    
    static ConfigLoader* Instance(const std::string& path, Config& cfg);
    static void Release();

    bool LoadConfig();
    void PrintConfig();

private:

    static ConfigLoader* sInstance;

    // private variables
    const std::string* mPath;
    Config* mConfig;

    ConfigLoader(const std::string& path, Config& cfg);
    ~ConfigLoader();

};

#endif
