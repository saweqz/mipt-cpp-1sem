#include "board.h"
#include "game.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Enter the field size.\n";
    cout << "Count rows: ";
    int rows;
    cin >> rows;
    cout << "Count cols: ";
    int cols;
    cin >> cols;

    Game game(rows, cols);
    game.start_game();

    return 0;
}