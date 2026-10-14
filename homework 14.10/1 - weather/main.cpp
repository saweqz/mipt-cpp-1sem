#include <iomanip>
#include <iostream>

struct MinMax {
  int min;
  int max;
};

double averageTemp(const int* temps, int n) {
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += temps[i];
  }
  return static_cast<double>(sum) / n;
}

MinMax findMinMax(const int* temps, int n) {
  MinMax result = {temps[0], temps[0]};
  for (int i = 1; i < n; ++i) {
    if (temps[i] < result.min) {
      result.min = temps[i];
    }
    if (temps[i] > result.max) {
      result.max = temps[i];
    }
  }
  return result;
}

int countFrostyDays(const int* temps, int n) {
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (temps[i] < 0) {
      ++count;
    }
  }
  return count;
}

int main() {
  int n = 0;
  if (!(std::cin >> n) || n <= 0) {
    return 1;
  }

  int* temps = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> temps[i];
  }

  MinMax minMax = findMinMax(temps, n);
  std::cout << std::fixed << std::setprecision(1) << averageTemp(temps, n)
            << '\n';
  std::cout << minMax.min << ' ' << minMax.max << '\n';
  std::cout << countFrostyDays(temps, n) << '\n';

  delete[] temps;
  return 0;
}