// MapGenerator.h
#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <iostream>
#include <vector>
#include <queue>
#include <string_view>

export module mapgenerator;

export class __declspec(dllexport) MapGenerator
{
public:
    enum class CellType : int
    {
        Empty = 0,      // spațiu liber
        BreakableWall = 1, // perete care poate fi spart
        Bush = 2,       // bush prin care se poate trece
        UnbreakableWall = 3 // perete care nu poate fi spart
    };

    // Constructor
    MapGenerator(int rows, int cols);

    // Funcție pentru generarea unei hărți
    void GenerateGameMap(int* map);

    // Funcție pentru a seta dimensiunile hărții
    void SetDimensions(int rows, int cols);

private:
    bool isValid(int x, int y, const std::vector<std::vector<int>>& grid) const;
    bool isMapTraversable(std::vector<std::vector<int>>& grid, const std::vector<Point>& playerPositions) const;
    void generateMap(std::vector<std::vector<int>>& grid, std::vector<Point>& playerPositions);

    struct Point
    {
        int x, y;
    };

    int m_rows, m_cols;
};

#endif // MAPGENERATOR_H