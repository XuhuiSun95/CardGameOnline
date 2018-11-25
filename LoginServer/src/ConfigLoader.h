#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <iostream>
#include "INIReader.h"

struct Config {

    // MySQL
    std::string db_host;
    int db_port;
    std::string db_name;
    std::string db_username;
    std::string db_password;

    // Servoce
    int server_port;
    std::string doudizhu_host;
    int doudizhu_port;
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
