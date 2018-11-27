#include "Database.h"

Database* Database::sInstance = nullptr;

Database* Database::Instance(const Config& cfg) {

    if(sInstance==nullptr)
        sInstance = new Database(cfg);

    return sInstance;
}

void Database::Release() {

    delete sInstance;
    sInstance = nullptr;
}

Database::Database(const Config& cfg) {

    mConfig = &cfg;
    mClient = new mysqlx::Client(
            mysqlx::SessionOption::USER, mConfig->db_username,
            mysqlx::SessionOption::PWD, mConfig->db_password,
            mysqlx::SessionOption::HOST, mConfig->db_host,
            mysqlx::SessionOption::PORT, mConfig->db_port,
            mysqlx::SessionOption::DB, mConfig->db_name,
            mysqlx::SessionOption::SSL_MODE, mysqlx::SSLMode::REQUIRED,
            mysqlx::ClientOption::POOLING, true,
            mysqlx::ClientOption::POOL_MAX_SIZE, 12,
            mysqlx::ClientOption::POOL_QUEUE_TIMEOUT, 1000,
            mysqlx::ClientOption::POOL_MAX_IDLE_TIME, 500
            );
}

Database::~Database() {

    mClient->close();
}
