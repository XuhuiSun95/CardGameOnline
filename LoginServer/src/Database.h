#ifndef DATABASE_H
#define DATABASE_H

#include <mysqlx/xdevapi.h>
#include "ConfigLoader.h"

class Database {

public:

    static Database* Instance(const Config& cfg);
    static void Release();

private:

    static Database* sInstance;

    // private variables
    const Config* mConfig;
    mysqlx::Client* mClient;

    Database(const Config& cfg);
    ~Database();

};

#endif
