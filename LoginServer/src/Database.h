#ifndef DATABASE_H
#define DATABASE_H

#include <mysqlx/xdevapi.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include "ConfigLoader.h"

class Database {

public:

    static Database* Instance(const Config& cfg);
    static void Release();

    int sign_up(const std::string& username, const std::string& password);
    int sign_in(const std::string& username, const std::string& password);

private:

    static Database* sInstance;

    // private variables
    const Config* mConfig;
    mysqlx::Client* mClient;

    Database(const Config& cfg);
    ~Database();

};

#endif
