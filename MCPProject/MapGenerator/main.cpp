#include <iostream>
#include "MapGenerator.h"

const int ROWS = 20;
const int COLS = 30;

int main() {
    int map[ROWS * COLS];

    // Apelăm funcția din DLL
    GenerateGameMap(map);

    // Afișăm harta generată
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << map[i * COLS + j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
