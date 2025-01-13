#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <optional>
#include <memory>

struct Player {
    int id;
    std::string username;
    std::string password_hash;
    uint16_t points;
};

using namespace sqlite_orm;
inline auto init_storage(const std::string& path) {
    return make_storage(path,
        make_table("players",
            make_column("id", &Player::id, sqlite_orm::primary_key(), sqlite_orm::primary_key().autoincrement()),
            make_column("username", &Player::username, sqlite_orm::unique()),
            make_column("password_hash", &Player::password_hash),
            make_column("points", &Player::points, sqlite_orm::default_value(0))
        ));
}

using Storage = decltype(init_storage(""));

class DatabaseManager {
public:
    explicit DatabaseManager(const std::string& db_path);
    ~DatabaseManager();

    bool addPlayer(const std::string& username, const std::string& password);
    bool verifyCredentials(const std::string& username, const std::string& password);
    std::optional<uint16_t> getPlayerPoints(const std::string& username);
    bool setPlayerPoints(const std::string& username, uint16_t points);

private:
    std::unique_ptr<Storage> m_storage;
    std::string hashPassword(const std::string& password);
    bool verifyPassword(const std::string& password, const std::string& hash);
};