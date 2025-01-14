#include "MapGenerator.h"
#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <random>

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
    std::random_device rd;
    std::mt19937 gen(rd());
    srand(gen());

    auto countNeighbors = [&](int x, int y, int type, bool diagonals) -> int  // calculeaza vecinii unui block
        {
            const int dx[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
            const int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1 };
            int count = 0;

            int i;
            if (diagonals)
                i = 7;
            else
                i = 3;
            for (; i >= 0; --i)
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

    const int MAX_CLUSTER_SIZE = 10;

    std::function<int(int, int, int, std::vector<std::vector<bool>>&, int&)> countClusterSize =
        [&](int x, int y, int type, std::vector<std::vector<bool>>& visited, int& currentSize) -> int
        {
            if (x < 0 || x >= ROWS || y < 0 || y >= COLS || visited[x][y] || grid[x][y] != type)
                return 0;

            visited[x][y] = true;
            currentSize++;

            if (currentSize > MAX_CLUSTER_SIZE)
                return currentSize;

            const int dx[] = { -1, 1, 0, 0, -1, -1, 1, 1 };
            const int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1 };

            for (int i = 0; i < 8; ++i)
            {
                countClusterSize(x + dx[i], y + dy[i], type, visited, currentSize);
            }

            return currentSize;
        };

    do {
        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                std::vector<std::pair<int, int>> probabilities = { {0, 20}, {1, 40}, {2, 30}, {3, 10} };
                std::sort(probabilities.begin(), probabilities.end(), [&](const auto& a, const auto& b) {
                    return countNeighbors(i, j, a.first, true) > countNeighbors(i, j, b.first, true);
                    });

                for (const auto& prob : probabilities)
                {
                    int type = prob.first;
                    int chance = prob.second;

                    int randValue = rand() % 100;
                    if (randValue < chance)
                    {
                        grid[i][j] = type;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                if (grid[i][j] == 1 || grid[i][j] == 2)
                {
                    const int dx[] = { -1, 1, 0, 0 };
                    const int dy[] = { 0, 0, -1, 1 };

                    for (int k = 0; k < 4; ++k)
                    {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS && grid[nx][ny] == 0)
                        {
                            std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
                            int clusterSize = 0;
                            countClusterSize(i, j, grid[i][j], visited, clusterSize);

                            if (clusterSize > MAX_CLUSTER_SIZE)
                            {
                                grid[i][j] = 0;
                            }
                        }
                    }
                }

                if (grid[i][j] == 0)
                {
                    if (countNeighbors(i, j, 1, false) == 4)
                        grid[i][j] = 0;
                    else if (countNeighbors(i, j, 2, false) == 4)
                        grid[i][j] = 2;
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

void GenerateGameMap(std::array<int, MapGenerator::ROWS* MapGenerator::COLS>& map)
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