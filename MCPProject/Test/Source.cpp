#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Dimensiunile hărții
const int ROWS = 20;
const int COLS = 30;

// Funcția pentru generarea hărții cu logică
void generateLogicalMap(int map[ROWS][COLS]) {
    srand(time(0));

    // Inițializăm harta cu pereți care nu pot fi sparți
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
                map[i][j] = 3; // Pereți care nu pot fi sparți (marginea)
            }
            else {
                map[i][j] = 0; // Spațiu liber (interiorul)
            }
        }
    }

    // Adăugăm obstacole și bush-uri
    for (int i = 1; i < ROWS - 1; i++) {
        for (int j = 1; j < COLS - 1; j++) {
            int randVal = rand() % 100;

            if (randVal < 10) {
                map[i][j] = 3; // Pereți care nu pot fi sparți (10%)
            }
            else if (randVal < 30) {
                map[i][j] = 1; // Pereți care pot fi sparți (20%)
            }
            else if (randVal < 50) {
                map[i][j] = 2; // Bush-uri (20%)
            }
            // Restul (50%) rămâne spațiu liber
        }
    }

    // Creăm câteva drumuri libere
    for (int i = 2; i < ROWS - 2; i++) {
        map[i][COLS / 2] = 0; // Drum vertical în mijloc
    }
    for (int j = 2; j < COLS - 2; j++) {
        map[ROWS / 2][j] = 0; // Drum orizontal în mijloc
    }
}

// Funcția pentru afișarea hărții
void printMap(int map[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] == 0) {
                cout << ". ";  // Spațiu liber
            }
            else if (map[i][j] == 1) {
                cout << "# ";  // Perete care poate fi spart
            }
            else if (map[i][j] == 2) {
                cout << "B ";  // Bush
            }
            else {
                cout << "X ";  // Perete care nu poate fi spart
            }
        }
        cout << endl;
    }
}

int main() {
    // Harta 20x30
    int map[ROWS][COLS];

    // Generăm harta
    generateLogicalMap(map);

    // Afișăm harta
    cout << "Harta generată logic este:" << endl;
    printMap(map);

    return 0;
}
