#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

class Game {
private:
    int rows;
    int cols;

public:
    Game(int rows, int cols);
    void start_game();
};

#endif // MINESWEEPER_GAME_H