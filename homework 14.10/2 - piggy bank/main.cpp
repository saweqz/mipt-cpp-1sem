#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

using Operation = bool (*)(int&);

bool deposit(int& balance) {
  int amount = 0;

  if (!(std::cin >> amount) || amount <= 0) {
    std::cin.clear();
    return false;
  }

  balance += amount;
  return true;
}

bool withdraw(int& balance) {
  int amount = 0;

  if (!(std::cin >> amount) || amount <= 0 || amount > balance) {
    std::cin.clear();
    return false;
  }

  balance -= amount;
  return true;
}

bool showBalance(int& balance) {
  std::cout << balance << '\n';
  return true;
}

bool reset(int& balance) {
  balance = 0;
  return true;
}

bool doubleBalance(int& balance) {
  balance *= 2;
  return true;
}

struct Command {
  const char* name;
  Operation operation;
};

const Command commands[] = {
    {"deposit", deposit}, {"withdraw", withdraw},    {"balance", showBalance},
    {"reset", reset},     {"double", doubleBalance},
};

int main() {
  int balance = 0;
  char command[20];
  int count = sizeof(commands) / sizeof(commands[0]);

  while (std::cin >> std::setw(sizeof(command)) >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }

    Operation operation = nullptr;

    for (int i = 0; i < count; ++i) {
      if (std::strcmp(command, commands[i].name) == 0) {
        operation = commands[i].operation;
        break;
      }
    }

    if (operation == nullptr || !operation(balance)) {
      std::cout << "error\n";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return 0;
}