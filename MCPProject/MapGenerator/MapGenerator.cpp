#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

#define DLL_EXPORT extern "C" __declspec(dllexport)

const int ROWS = 20;
const int COLS = 30;

// Structura pentru punctele din matrice
struct Point {
    int x, y;
};

// Verifică dacă o poziție este validă și accesibilă
bool isValid(int x, int y, const std::vector<std::vector<int>>& grid) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] != 3;
}

// BFS pentru a verifica conectivitatea hărții
bool isMapTraversable(std::vector<std::vector<int>>& grid, const std::vector<Point>& playerPositions) {
    std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
    std::queue<Point> q;

    // Începem din prima poziție a unui jucător
    q.push(playerPositions[0]);
    visited[playerPositions[0].x][playerPositions[0].y] = true;

    int reachableCells = 1;
    while (!q.empty()) {
        Point current = q.front();
        q.pop();

        // Direcții de deplasare: sus, jos, stânga, dreapta
        const int dx[] = { -1, 1, 0, 0 };
        const int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValid(nx, ny, grid) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                q.push({ nx, ny });
                reachableCells++;
            }
        }
    }

    // Verificăm dacă toate pozițiile jucătorilor sunt accesibile
    for (const auto& player : playerPositions) {
        if (!visited[player.x][player.y]) {
            return false;
        }
    }

    return reachableCells >= ROWS * COLS / 2; // Aproximativ jumătate din hartă trebuie să fie traversabilă
}

// Generare hartă
void generateMap(std::vector<std::vector<int>>& grid, std::vector<Point>& playerPositions) {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned>(time(0)));
        initialized = true;
    }

    do {
        // Resetăm matricea
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                grid[i][j] = rand() % 4;
            }
        }

        // Asigurăm că pozițiile jucătorilor sunt 0 (spațiu liber)
        playerPositions = { {0, 0}, {0, COLS - 1}, {ROWS - 1, 0}, {ROWS - 1, COLS - 1} };
        for (const auto& player : playerPositions) {
            grid[player.x][player.y] = 0;
        }

        // Marcăm colțurile 2x2 ca libere (0)
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                grid[i][j] = 0;                         // Stânga-sus
                grid[i][COLS - 1 - j] = 0;              // Dreapta-sus
                grid[ROWS - 1 - i][j] = 0;              // Stânga-jos
                grid[ROWS - 1 - i][COLS - 1 - j] = 0;   // Dreapta-jos
            }
        }

    } while (!isMapTraversable(grid, playerPositions)); // Generăm până când harta este validă
}

// Funcția exportată
DLL_EXPORT void GenerateGameMap(int* map) {
    if (!map) {
        std::cerr << "Error: Null pointer passed to GenerateGameMap.\n";
        return;
    }

    std::vector<std::vector<int>> grid(ROWS, std::vector<int>(COLS, 0));
    std::vector<Point> playerPositions;

    // Generăm harta
    generateMap(grid, playerPositions);

    // Copiem matricea în pointerul dat
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            map[i * COLS + j] = grid[i][j];
        }
    }
}
