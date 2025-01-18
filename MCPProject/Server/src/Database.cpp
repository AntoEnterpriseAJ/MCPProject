#include "Database.h"
#include <stdexcept>

DatabaseManager::DatabaseManager(const std::string& db_path) {
    try {
        auto storage = init_storage(db_path);
        storage.sync_schema();
        m_storage = std::make_unique<Storage>(std::move(storage));
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Failed to initialize database: " + std::string(e.what()));
    }
}

DatabaseManager::~DatabaseManager() = default;

bool DatabaseManager::userExists(const std::string& username)
{
    try {
        auto users = m_storage->get_all<User>(
            sql::where(sql::c(&User::username) == username)
        );
        return !users.empty();
    }
    catch (const std::exception& e) {
        return false;
    }
}

bool DatabaseManager::addUser(const std::string& username, const std::string& password) {
    try {
        User user{ -1, username, password, 0 };
        m_storage->insert(user);
        return true;
    }
    catch (const std::exception& e) {
        return false;
    }
}

bool DatabaseManager::verifyCredentials(const std::string& username, const std::string& password) {
    try {
        auto users = m_storage->get_all<User>(
            sql::where(sql::c(&User::username) == username)
        );
        if (users.empty()) {
            return false;
        }
        return password == users[0].password;
    }
    catch (const std::exception& e) {
        return false;
    }
}

uint16_t DatabaseManager::getUserPoints(uint16_t id)
{
    try {
        auto users = m_storage->get_all<User>(
            sql::where(sql::c(&User::id) == id)
        );
        if (users.empty()) {
            return 0;
        }
        return users[0].points;
    }
    catch (const std::exception& e) {
        return 0;
    }
}

std::optional<uint16_t> DatabaseManager::getUserPoints(const std::string& username) {
    try {
        auto users = m_storage->get_all<User>(
            sql::where(sql::c(&User::username) == username)
        );
        if (users.empty()) {
            return std::nullopt;
        }
        return users[0].points;
    }
    catch (const std::exception& e) {
        return std::nullopt;
    }
}

int DatabaseManager::getUserID(const std::string& username)
{
    try {
        auto users = m_storage->get_all<User>(
            sql::where(sql::c(&User::username) == username)
        );
        if (users.empty()) {
            return -1;
        }
        return users[0].id;
    }
    catch (const std::exception& e) {
        return -1;
    }
}

uint16_t DatabaseManager::setUserPoints(uint16_t id, uint16_t points)
{
    try {
        auto users = m_storage->get_all<User>(
            sql::where(sql::c(&User::id) == id)
        );
        if (users.empty()) {
            return 0;
        }
        auto& user = users[0];
        user.points = points;
        m_storage->update(user);
        return points;
    }
    catch (const std::exception& e) {
        return 0;
    }
}

bool DatabaseManager::setUserPoints(const std::string& username, uint16_t points) {
    try {
        auto users = m_storage->get_all<User>(
            sql::where(sql::c(&User::username) == username)
        );
        if (users.empty()) {
            return false;
        }
        auto& user = users[0];
        user.points = points;
        m_storage->update(user);
        return true;
    }
    catch (const std::exception& e) {
        return false;
    }
}