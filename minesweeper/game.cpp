#include "game.h"

#include "board.h"
#include <iostream>

Game::Game(int given_rows, int given_cols) {
    rows = given_rows;
    cols = given_cols;
    board_ = Board(rows, cols);
}

void Game::start_game() {

}
