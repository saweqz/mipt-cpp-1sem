#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
private:
    int rows;
    int cols;
    std::vector<std::vector<bool>> board;
    std::vector<std::vector<int>> is_open;

public:
    Board();
    Board(int rows, int cols);
    bool is_won();
    void print();
    void setMine(int row, int col);
    void create_many_mines(int count_mines);
    bool open_cell(int row, int col);
    bool is_mine(int row, int col);
    void reveal_all();
};

#endif // BOARD_H