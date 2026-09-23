#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H
#include "board.h"
class Game {
private:
    int rows;
    int cols;
    Board board_;
public:
    Game(int rows, int cols);
    void start_game();
};

#endif // MINESWEEPER_GAME_H