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

    // MySQL
    if((mConfig->db_host = reader.GetString("mysql", "db_host", "UNKNOW"))=="UNKNOW") {
        std::cerr << "Unknow MySQL host address" << std::endl;
        return false;
    }
    if(!(mConfig->db_port = reader.GetInteger("mysql", "db_port", 0))) {
        std::cerr << "Unknow MySQL port number" << std::endl;
        return false;
    }
    if((mConfig->db_name = reader.GetString("mysql", "db_name", "UNKNOW"))=="UNKNOW") {
        std::cerr << "Unknow MySQL database name" << std::endl;
        return false;
    }
    if((mConfig->db_username = reader.GetString("mysql", "db_username", "UNKNOW"))=="UNKNOW") {
        std::cerr << "Unknow MySQL username" << std::endl;
        return false;
    }
    if((mConfig->db_password = reader.GetString("mysql", "db_password", "UNKNOW"))=="UNKNOW") {
        std::cerr << "Unknow MySQL password" << std::endl;
        return false;
    }

    // Service
    if(!(mConfig->server_port = reader.GetInteger("service", "server_port", 0))) {
        std::cerr << "Unknow login server port number" << std::endl;
        return false;
    }

    std::cout << "The configuration was successfully loaded" << std::endl;
    return true;
}

void ConfigLoader::PrintConfig() {

    std::cout << "==========Config Detail==========" << std::endl;
    std::cout << "MySQL Database:\n"
              << "db_host = " << mConfig->db_host
              << "\ndb_port = " << mConfig->db_port
              << "\ndb_name = " << mConfig->db_name
              << "\ndb_username = " << mConfig->db_username
              << std::endl;
    std::cout << "\nService:\n"
              << "server_port = " << mConfig->server_port
              << std::endl;
    std::cout << "=================================" << std::endl;
    
}

ConfigLoader::ConfigLoader(const std::string& path, Config& cfg) {

    mPath = &path;
    mConfig = &cfg;
}

ConfigLoader::~ConfigLoader() {
}
