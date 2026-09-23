#include "board.h"
#include "game.h"
#include <bits/stdc++.h>

using namespace std;
int main() {
    cout << "Enter the field size.\n";
    cout << "Count rows: ";
    int rows; cin >> rows;
    cout << "Count cols: ";
    int cols; cin >> cols;
    Game(rows, cols);
    Game.start_game(rows, cols);

}