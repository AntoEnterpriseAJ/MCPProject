#include "MapGenerator.h"
#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>

bool MapGenerator::isValid(int x, int y, const std::vector<std::vector<int>>& grid) 
{
    return x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] != 3;
}

bool MapGenerator::isMapTraversable(std::vector<std::vector<int>>& grid, const std::vector<Point>& playerPositions) 
{
    std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
    std::queue<Point> q;

    q.push(playerPositions[0]);
    visited[playerPositions[0].x][playerPositions[0].y] = true;

    int reachableCells = 1;
    while (!q.empty()) 
    {
        Point current = q.front();
        q.pop();

        const int dx[] = { -1, 1, 0, 0 };
        const int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; ++i) 
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (isValid(nx, ny, grid) && !visited[nx][ny]) 
            {
                visited[nx][ny] = true;
                q.push({ nx, ny });
                reachableCells++;
            }
        }
    }

    for (const auto& player : playerPositions) 
    {
        if (!visited[player.x][player.y]) 
        {
            return false;
        }
    }

    return reachableCells >= ROWS * COLS / 2;
}

void MapGenerator::generateMap(std::vector<std::vector<int>>& grid, std::vector<Point>& playerPositions)
{
    static bool initialized = false;
    if (!initialized) 
    {
        srand(static_cast<unsigned>(time(0)));
        initialized = true;
    }

    auto countNeighbors = [&](int x, int y, int type) -> int 
        {
        const int dx[] = { -1, 1, 0, 0 };
        const int dy[] = { 0, 0, -1, 1 };
        int count = 0;

        for (int i = 0; i < 4; ++i) 
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && grid[nx][ny] == type) 
            {
                count++;
            }
        }

        return count;
        };

    do {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                int randValue = rand() % 100;
                if (randValue < 60) 
                {
                    grid[i][j] = 0;
                }
                else if (randValue < 80) 
                {
                    grid[i][j] = 1;
                }
                else if (randValue < 95) 
                {
                    grid[i][j] = 2;
                }
                else 
                {
                    grid[i][j] = 3;
                }

                if (grid[i][j] == 3 && countNeighbors(i, j, 3) > 1) 
                {
                    grid[i][j] = 0;
                }
            }
        }

        playerPositions = { {0, 0}, {0, COLS - 1}, {ROWS - 1, 0}, {ROWS - 1, COLS - 1} };
        for (const auto& player : playerPositions)
        {
            grid[player.x][player.y] = 0;
        }

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                grid[i][j] = 0;
                grid[i][COLS - 1 - j] = 0;
                grid[ROWS - 1 - i][j] = 0;
                grid[ROWS - 1 - i][COLS - 1 - j] = 0;
            }
        }

    } while (!isMapTraversable(grid, playerPositions));
}

void GenerateGameMap(std::array<int, MapGenerator::ROWS * MapGenerator::COLS>& map)
{
    std::vector<std::vector<int>> grid(MapGenerator::ROWS, std::vector<int>(MapGenerator::COLS, 0));
    std::vector<MapGenerator::Point> playerPositions;

    MapGenerator::generateMap(grid, playerPositions);

    for (int i = 0; i < MapGenerator::ROWS; ++i) 
    {
        for (int j = 0; j < MapGenerator::COLS; ++j) 
        {
            map[i * MapGenerator::COLS + j] = grid[i][j];
        }
    }
}
