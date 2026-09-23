#include "board.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>


Board::Board() {
    rows = 0;
    cols = 0;
}

Board::Board(int given_rows, int given_cols) {
    rows = given_rows;
    cols = given_cols;
    board.assign(rows, std::vector<bool>(cols, false));
    is_open.assign(rows, std::vector<int>(cols, 0));
}

void Board::print() {
    std::cout << "  ";
    for (int i = 0; i < cols; i++) {
        std::cout << i ;
    }
    std::cout << '\n';
    for (int i = 0; i < rows; i++) {
        std::cout << i << " ";
        for (int j = 0; j < cols; j++) {
            if (is_open[i][j] == 0) {          // туман
                std::cout << "#";
            } else if (board[i][j] == true) {  // мина
                std::cout << "*";
            } else {
                int cnt = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (is_mine(i + di, j + dj)) {
                            cnt += 1;
                        }
                    }
                }
                std::cout << cnt;
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void Board::setMine(int row, int col) {
    board[row][col] = true;
}

bool Board::is_mine(int row, int col) {
    if (row < 0 || col < 0 || row >= rows || col >= cols) {
        return false;
    }
    return board[row][col];
}

bool Board::open_cell(int row, int col) {
    if (row < 0 || col < 0 || row >= rows || col >= cols) {
        return false;
    }
    if (board[row][col] == true) {
        return true;  // попали на мину
    }
    is_open[row][col] = 1;
    return false;
}

void Board::create_many_mines(int count_mines) {
    assert(count_mines <= rows * cols);
    std::vector<int> permutation(rows * cols);
    std::iota(permutation.begin(), permutation.end(), 0);

    std::random_device rd;
    std::mt19937 rnd(rd());           // без фиксированного зерна

    shuffle(permutation.begin(), permutation.end(), rnd);
    for (int i = 0; i < count_mines; i++) {
        setMine(permutation[i] / cols, permutation[i] % cols);
    }
}

bool Board::is_won() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == false && is_open[i][j] == 0) {
                return false;  // есть закрытая не-минная клетка
            }
        }
    }
    return true;
}

void Board::reveal_all() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            is_open[i][j] = 1;
        }
    }
}