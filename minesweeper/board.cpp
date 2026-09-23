#include "Board.h"
#include <bits/stdc++.h>

using namespace std;

Board::Board(int given_rows, int given_cols) {
    rows = given_rows;
    cols = given_cols;
    board.assign(rows, vector<bool>(cols, 0));
    is_open.assign(rows, vector<int>(cols, 0));
}
void Board::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (is_open[i][j] == 0) {//туман
                cout << "#";
            } else if (board[i][j] == true){//мина
                cout << "*";
            } else {
                int cnt = 0;
                for (int i1 = -1; i1 <= 1; i1++) {
                    for (int j1 = -1; j1 <= 1; j1++) {
                        if (is_mine(i + i1, j + j1)) {
                            cnt+=1;
                        }
                    }
                }
                cout << cnt;
            }
        }
        cout << '\n';
    }
    cout << '\n';
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
    if (board[row][col] == true) {
        return true;//проиграли
    }
    is_open[row][col] = 1;
    return true;
}

void Board::create_many_mines(int count_mines) {
    assert(count_mines <= rows * cols);
    vector<int> permutation(rows * cols);
    iota(permutation.begin(), permutation.end(), 0);
    mt19937 rnd(228);
    shuffle(permutation.begin(), permutation.end(), rnd);
    for (int i = 0; i < count_mines; i++) {
        setMine(permutation[i] / cols, permutation[i] % cols);
    }
}
