#include "game.h"

#include "board.h"
#include <iostream>

Game::Game(int given_rows, int given_cols, int percent) {
    rows = given_rows;
    cols = given_cols;
    board_ = Board(rows, cols);
    mine_percent = percent;
}

void Game::start_game() {
    int count_mines = rows * cols * mine_percent / 100;
    count_mines = std::min(count_mines, rows * cols - 1);
    count_mines = std::max(count_mines, 1);
    board_.create_many_mines(count_mines);
    while (true) {
        board_.print();
        std::cout << "Enter row and col : \n";
        int r, c;
        std::cin >> r >> c;
        if (r < 0 || c < 0 || r >= rows || c >= cols) {
            std::cout << "Out of bounds\n";
            continue;
        }
        bool is_not_good = board_.open_cell(r, c);
        if (is_not_good) {
            std::cout << "You hit a mine! Game over!\n";
            board_.reveal_all();
            board_.print();
            return;
        }
        if (board_.is_won() == true) {
            board_.print();
            std::cout << "Congratulations! You won !\n";
            return;
        }
    }
}
