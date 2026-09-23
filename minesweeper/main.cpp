#include "board.h"
#include "game.h"
#include <iostream>


int main() {
    std::cout << "Enter the field size.\n";
    std::cout << "Count rows: ";
    int rows;
    std::cin >> rows;
    std::cout << "Count cols: ";
    int cols;
    std::cin >> cols;
    std:: cout << "Mine percent : ";
    int percent;
    std::cin >> percent;
    Game game(rows, cols, percent);
    game.start_game();

    return 0;
}