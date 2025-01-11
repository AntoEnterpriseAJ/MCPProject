#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

#define DLL_EXPORT extern "C" __declspec(dllexport)

const int ROWS = 20;
const int COLS = 30;

struct Point {
    int x, y;
};

bool isValid(int x, int y, const std::vector<std::vector<int>>& grid) {
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] != 3;
}

bool isMapTraversable(std::vector<std::vector<int>>& grid, const std::vector<Point>& playerPositions) {
    std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
    std::queue<Point> q;

    q.push(playerPositions[0]);
    visited[playerPositions[0].x][playerPositions[0].y] = true;

    int reachableCells = 1;
    while (!q.empty()) {
        Point current = q.front();
        q.pop();

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

    for (const auto& player : playerPositions) {
        if (!visited[player.x][player.y]) {
            return false;
        }
    }

    return reachableCells >= ROWS * COLS / 2;
}

void generateMap(std::vector<std::vector<int>>& grid, std::vector<Point>& playerPositions) {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned>(time(0)));
        initialized = true;
    }

    do {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                grid[i][j] = rand() % 4;
            }
        }

        playerPositions = { {0, 0}, {0, COLS - 1}, {ROWS - 1, 0}, {ROWS - 1, COLS - 1} };
        for (const auto& player : playerPositions) {
            grid[player.x][player.y] = 0;
        }

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                grid[i][j] = 0;
                grid[i][COLS - 1 - j] = 0;
                grid[ROWS - 1 - i][j] = 0;
                grid[ROWS - 1 - i][COLS - 1 - j] = 0;
            }
        }

    } while (!isMapTraversable(grid, playerPositions));
}

DLL_EXPORT void GenerateGameMap(int* map) {
    if (!map) {
        std::cerr << "Error: Null pointer passed to GenerateGameMap.\n";
        return;
    }

    std::vector<std::vector<int>> grid(ROWS, std::vector<int>(COLS, 0));
    std::vector<Point> playerPositions;

    generateMap(grid, playerPositions);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            map[i * COLS + j] = grid[i][j];
        }
    }
}
