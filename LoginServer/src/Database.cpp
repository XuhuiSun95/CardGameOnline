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

int Database::sign_up(const std::string& username, const std::string& password) {

    try {
        mysqlx::Session sess = mClient->getSession();

        try {
            mysqlx::Table tbl = sess.getDefaultSchema().getTable("member");

            using namespace CryptoPP;
            AutoSeededRandomPool prng;
            SHA256 hash;
            SecByteBlock key(AES::DEFAULT_KEYLENGTH);
            prng.GenerateBlock(key.data(), key.size());

            std::string salt, salted, pw;
            StringSource ss(key.data(), key.size(), true, new HexEncoder(new StringSink(salt)));
            salted = salt + password;
            StringSource s(salted, true, new HashFilter(hash, new HexEncoder(new StringSink(pw))));

            tbl.insert("username", "salt", "password")
                .values(username, salt, pw).execute();
            return 0;

        } catch (const mysqlx::Error& e) {
            std::cout << e << std::endl;
            return 101;
        }

    } catch (const mysqlx::Error& e) {
        std::cout << e << std::endl;
        return 1;
    }
}

int Database::sign_in(const std::string& username, const std::string& password) {

    try {
        mysqlx::Session sess = mClient->getSession();
        mysqlx::Table tbl = sess.getDefaultSchema().getTable("member");

        mysqlx::RowResult row_res = tbl.select("salt", "password")
            .where("username = :username")
            .bind("username", username).execute();

        if(row_res.count() == 0)
            return 201;
        else {
            using namespace CryptoPP;
            SHA256 hash;

            std::string salt, hash_pw, salted, pw;
            mysqlx::Row row = row_res.fetchOne();
            salt = std::string(row[0]);
            hash_pw = std::string(row[1]);
            salted = salt + password;
            StringSource s(salted, true, new HashFilter(hash, new HexEncoder(new StringSink(pw))));

            if(hash_pw == pw)
                return 0;
            else
                return 202;
        }

    } catch (const mysqlx::Error& e) {
        std::cout << e << std::endl;
        return 1;
    }
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
            mysqlx::ClientOption::POOL_MAX_SIZE, 8,
            mysqlx::ClientOption::POOL_QUEUE_TIMEOUT, 1000,
            mysqlx::ClientOption::POOL_MAX_IDLE_TIME, 500
            );
}

Database::~Database() {

    mClient->close();
    delete mClient;
}
