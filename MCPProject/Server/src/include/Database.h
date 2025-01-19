#pragma once
#include <sqlite_orm/sqlite_orm.h>
#include <string>
#include <optional>
#include <memory>

namespace sql = sqlite_orm;

struct User {
    int id;
    std::string username;
    std::string password;
    uint16_t score;
};

inline auto init_storage(const std::string& path) {
    return sql::make_storage(path,
        sql::make_table("Users",
            sql::make_column("id", &User::id, sql::primary_key().autoincrement()),
            sql::make_column("username", &User::username, sql::unique()),
            sql::make_column("password", &User::password),
            sql::make_column("score", &User::score, sql::default_value(0))
        ));
}

using Storage = decltype(init_storage(""));

class DatabaseManager {
public:
    explicit DatabaseManager(const std::string& db_path);
    ~DatabaseManager();
    bool userExists(const std::string& username);
    bool addUser(const std::string& username, const std::string& password);
    bool verifyCredentials(const std::string& username, const std::string& password);
    uint16_t getUserScore(uint16_t id);
    std::optional<uint16_t> getUserScore(const std::string& username);
    int getUserID(const std::string& username);
    void addScore(uint16_t id, uint16_t score);
    uint16_t setUserScore(uint16_t id, uint16_t score);
    bool setUserScore(const std::string& username, uint16_t score);
private:
    std::unique_ptr<Storage> m_storage;
};