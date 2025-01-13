#include "Database.h"
#include <stdexcept>

using namespace sqlite_orm;

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

bool DatabaseManager::addPlayer(const std::string& username, const std::string& password) {
    try {
        Player player{
            -1,  // ID will be auto-assigned
            username,
            hashPassword(password),
            0    // Initial points
        };
        m_storage->insert(player);
        return true;
    }
    catch (const std::exception& e) {
        return false;  // Username might already exist
    }
}

bool DatabaseManager::verifyCredentials(const std::string& username, const std::string& password) {
    try {
        auto players = m_storage->get_all<Player>(
            where(c(&Player::username) == username)
        );

        if (players.empty()) {
            return false;
        }

        return verifyPassword(password, players[0].password_hash);
    }
    catch (const std::exception& e) {
        return false;
    }
}

std::optional<uint16_t> DatabaseManager::getPlayerPoints(const std::string& username) {
    try {
        auto players = m_storage->get_all<Player>(
            where(c(&Player::username) == username)
        );

        if (players.empty()) {
            return std::nullopt;
        }

        return players[0].points;
    }
    catch (const std::exception& e) {
        return std::nullopt;
    }
}

bool DatabaseManager::setPlayerPoints(const std::string& username, uint16_t points) {
    try {
        auto players = m_storage->get_all<Player>(
            where(c(&Player::username) == username)
        );

        if (players.empty()) {
            return false;
        }

        auto& player = players[0];
        player.points = points;
        m_storage->update(player);
        return true;
    }
    catch (const std::exception& e) {
        return false;
    }
}

std::string DatabaseManager::hashPassword(const std::string& password) {
    // This is a placeholder - implement proper password hashing!
    return password;  // DO NOT use this in production!
}

bool DatabaseManager::verifyPassword(const std::string& password, const std::string& hash) {
    // This is a placeholder - implement proper password verification!
    return password == hash;  // DO NOT use this in production!
}