#include "board.h"
#include "game.h"
#include <iostream>


int main() {
    std::cout << "Enter the field size.\n";
    std::cout << "Count rows: ";
    int rows;
    if (!(std::cin >> rows) || rows <= 0) {
        std::cout << "Invalid rows\n";
        return 1;
    }
    std::cout << "Count cols: ";
    int cols;
    if (!(std::cin >> cols) || cols <= 0) {
        std::cout << "Invalid cols\n";
        return 0;
    }
    std::cout << "Mine percent: ";
    int percent;
    if (!(std::cin >> percent)) {
        std::cout << "Invalid percent\n";
        return 0;
    }

    Game game(rows, cols, percent);
    game.start_game();

    return 0;
}