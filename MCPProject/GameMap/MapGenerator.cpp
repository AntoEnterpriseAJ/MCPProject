// MapGenerator.cpp
import mapgenerator;

#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <format>

export module mapgenerator;

MapGenerator::MapGenerator(int rows, int cols) : m_rows{ rows }, m_cols{ cols } {}

void MapGenerator::SetDimensions(int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;
}

bool MapGenerator::isValid(int x, int y, const std::vector<std::vector<int>>& grid) const
{
    return x >= 0 && x < m_rows && y >= 0 && y < m_cols && grid[x][y] != static_cast<int>(CellType::UnbreakableWall);
}

bool MapGenerator::isMapTraversable(std::vector<std::vector<int>>& grid, const std::vector<Point>& playerPositions) const
{
    std::vector<std::vector<bool>> visited(m_rows, std::vector<bool>(m_cols, false));
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

    return reachableCells >= m_rows * m_cols / 2; // Aproximativ jumătate din hartă trebuie să fie traversabilă
}

void MapGenerator::generateMap(std::vector<std::vector<int>>& grid, std::vector<Point>& playerPositions)
{
    do {
        // Resetăm matricea
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                grid[i][j] = rand() % 4;  // Generăm o valoare aleatoare între 0 și 3
            }
        }

        // Asigurăm că pozițiile jucătorilor sunt 0 (spațiu liber)
        playerPositions = { {0, 0}, {0, m_cols - 1}, {m_rows - 1, 0}, {m_rows - 1, m_cols - 1} };
        for (const auto& player : playerPositions) {
            grid[player.x][player.y] = static_cast<int>(CellType::Empty);
        }
    } while (!isMapTraversable(grid, playerPositions)); // Generăm până când harta este validă
}

// Funcția exportată pentru a fi utilizată din DLL
export void MapGenerator::GenerateGameMap(int* map)
{
    std::vector<std::vector<int>> grid(m_rows, std::vector<int>(m_cols, 0));
    std::vector<Point> playerPositions;

    // Generăm harta
    generateMap(grid, playerPositions);

    // Copiem matricea în pointerul dat
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            map[i * m_cols + j] = grid[i][j];
        }
    }
}
