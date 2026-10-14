#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

const int kRows = 5;
const int kCols = 10;

void clearBoard(char board[kRows][kCols]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kCols; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool inBounds(int x, int y) {
  return x >= 0 && x < kCols && y >= 0 && y < kRows;
}

bool put(char board[kRows][kCols], int x, int y, char c) {
  if (!inBounds(x, y)) {
    return false;
  }

  board[y][x] = c;
  return true;
}

bool writeText(char board[kRows][kCols], int x, int y, const char* word) {
  int len = static_cast<int>(std::strlen(word));

  if (len == 0 || !inBounds(x, y) || !inBounds(x + len - 1, y)) {
    return false;
  }

  for (int i = 0; i < len; ++i) {
    put(board, x + i, y, word[i]);
  }

  return true;
}

void printBoard(const char board[kRows][kCols]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kCols; ++x) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

void skipBadLine() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
  char board[kRows][kCols];
  char command[32];

  clearBoard(board);

  while (std::cin >> std::setw(sizeof(command)) >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    }

    bool ok = true;

    if (std::strcmp(command, "clear") == 0) {
      clearBoard(board);
    } else if (std::strcmp(command, "print") == 0) {
      printBoard(board);
    } else if (std::strcmp(command, "put") == 0) {
      int x = 0;
      int y = 0;
      char c = ' ';

      if (!(std::cin >> x >> y >> c)) {
        skipBadLine();
        ok = false;
      } else {
        ok = put(board, x, y, c);
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x = 0;
      int y = 0;
      char word[256];

      if (!(std::cin >> x >> y >> std::setw(sizeof(word)) >> word)) {
        skipBadLine();
        ok = false;
      } else {
        ok = writeText(board, x, y, word);
      }
    } else {
      ok = false;
    }

    if (!ok) {
      std::cout << "error\n";
    }
  }

  return 0;
}