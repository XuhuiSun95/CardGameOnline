#include "ConfigLoader.h"

ConfigLoader* ConfigLoader::sInstance = nullptr;

ConfigLoader* ConfigLoader::Instance(const std::string& path, Config& cfg) {

    if(sInstance==nullptr)
        sInstance = new ConfigLoader(path, cfg);

    return sInstance;
}

void ConfigLoader::Release() {

    delete sInstance;
    sInstance = nullptr;
}

bool ConfigLoader::LoadConfig() {
    
    INIReader reader(*mPath);

    if(reader.ParseError() < 0) {
        std::cerr << "Can't load .ini" << std::endl;
        return false;
    }

    // Service
    if((mConfig->login_host = reader.GetString("service", "login_host", "UNKNOW"))=="UNKNOW") {
        std::cerr << "Unknow game name" << std::endl;
        return false;
    }
    if(!(mConfig->login_port = reader.GetInteger("service", "login_port", 0))) {
        std::cerr << "Unknow game port" << std::endl;
        return false;
    }
    if((mConfig->game_name = reader.GetString("service", "game_name", "UNKNOW"))=="UNKNOW") {
        std::cerr << "Unknow game name" << std::endl;
        return false;
    }
    if(!(mConfig->game_port = reader.GetInteger("service", "game_port", 0))) {
        std::cerr << "Unknow game port" << std::endl;
        return false;
    }

    std::cout << "The configuration was successfully loaded" << std::endl;
    return true;
}

void ConfigLoader::PrintConfig() {

    std::cout << "==========Config Detail==========" << std::endl;
    std::cout << "Service:\n"
              << "login_host = " << mConfig->login_host
              << "\nlogin_port = " << mConfig->login_port
              << "\ngame_name = " << mConfig->game_name
              << "\ngame_port = " << mConfig->game_port
              << std::endl;
    std::cout << "=================================" << std::endl;
    
}

ConfigLoader::ConfigLoader(const std::string& path, Config& cfg) {

    mPath = &path;
    mConfig = &cfg;
}

ConfigLoader::~ConfigLoader() {
}
