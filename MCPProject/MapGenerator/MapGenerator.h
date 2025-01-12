#include <vector>

    __declspec(dllexport) void GenerateGameMap(int* map);

class MapGenerator {
public:
    static const int ROWS = 20;
    static const int COLS = 30;

    struct Point {
        int x, y;
    };

    static void generateMap(std::vector<std::vector<int>>& grid, std::vector<Point>& playerPositions);
    static bool isValid(int x, int y, const std::vector<std::vector<int>>& grid);
    static bool isMapTraversable(std::vector<std::vector<int>>& grid, const std::vector<Point>& playerPositions);
};