// main.cpp
import mapgenerator;

#include <iostream>

const int ROWS = 20;
const int COLS = 30;

int main() {
    int map[ROWS * COLS];

    // Creează instanța MapGenerator
    MapGenerator generator(ROWS, COLS);

    // Apelează funcția pentru a genera harta
    generator.GenerateGameMap(map);

    // Afișează harta
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << map[i * COLS + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
