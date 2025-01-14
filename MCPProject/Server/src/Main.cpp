#include <iostream>
#include <crow.h>
#include "Routing.h"
#include "Database.h"
#include "../../MapGenerator/MapGenerator.h"

int main()
{
    Routing routing;
    routing.run();

    //Database testings
  /*  try {
        DatabaseManager db("game.db");

        const std::vector<std::pair<std::string, std::string>> Users = {
            {"User1", "pass123"},
            {"User2", "secret456"},
            {"User3", "gaming789"},
            {"User4", "test000"},
            {"User5", "password111"}
        };

        for (const auto& [username, password] : Users) {
            if (db.addUser(username, password)) {
                std::cout << "Added User: " << username << std::endl;
                db.setUserPoints(username, std::rand() % 1000);
            }
            else {
                std::cout << "Failed to add User: " << username << std::endl;
            }
        }

        std::cout << "\nVerifying User1 credentials:" << std::endl;
        if (db.verifyCredentials("User1", "pass123")) {
            std::cout << "User1 login successful" << std::endl;
        }
        else {
            std::cout << "User1 login failed" << std::endl;
        }

        if (db.verifyCredentials("User1", "wrongpass")) {
            std::cout << "User1 wrong password login successful (this shouldn't happen)" << std::endl;
        }
        else {
            std::cout << "User1 wrong password login failed (as expected)" << std::endl;
        }

        std::cout << "\nDatabase contents:" << std::endl;
        std::cout << "Username\tPoints" << std::endl;
        std::cout << "----------------" << std::endl;

        for (const auto& [username, _] : Users) {
            if (auto points = db.getUserPoints(username)) {
                std::cout << username << "\t\t" << *points << std::endl;
            }
        }

    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }*/

}

//int main() {
//    // Dimensiunile hărții
//    const int ROWS = MapGenerator::ROWS;
//    const int COLS = MapGenerator::COLS;
//
//    // Array pentru stocarea hărții generate
//    std::array<int, ROWS* COLS> map;
//
//    // Apel funcție din DLL
//    GenerateGameMap(map);
//
//    // Afișare hartă
//    for (int i = 0; i < ROWS; ++i) {
//        for (int j = 0; j < COLS; ++j) {
//            std::cout << map[i * COLS + j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    return 0;
//}
