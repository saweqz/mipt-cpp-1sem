#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>

// Журнал оценок: группы -> студенты -> оценки. Программа читает журнал,
// считает средний балл каждой группы и находит в ней лучшего студента.
//
// int*** нужен, потому что данные трёхуровневые: в группах разное
// число студентов, у студентов разное число оценок. Запись grades[g][s][i]
// даёт i-ю ячейку строки студента (в ячейке 0 лежит число оценок).
//
// void* нужен, потому что malloc возвращает память без типа. В один блок
// кладутся таблицы int**, таблицы int* и сами int-ы: из блока вырезаются
// куски нужных типов. Один malloc и один free.

int main() {
  // Ввод 1: число групп
  int groupCount = 0;
  if (!(std::cin >> groupCount) || groupCount <= 0) {
    return 1;
  }

  // Ввод 2: число студентов в каждой группе
  int* studentsInGroup = new int[groupCount];
  int totalStudents = 0;
  for (int g = 0; g < groupCount; ++g) {
    if (!(std::cin >> studentsInGroup[g]) || studentsInGroup[g] < 0) {
      delete[] studentsInGroup;
      return 1;
    }
    totalStudents += studentsInGroup[g];
  }

  // Ввод 3: число оценок у каждого студента (подряд по всем группам)
  int* gradesCount = new int[totalStudents];
  int totalGrades = 0;
  for (int i = 0; i < totalStudents; ++i) {
    if (!(std::cin >> gradesCount[i]) || gradesCount[i] < 0) {
      delete[] gradesCount;
      delete[] studentsInGroup;
      return 1;
    }
    totalGrades += gradesCount[i];
  }

  std::size_t bytes = groupCount * sizeof(int**) +
                      totalStudents * sizeof(int*) +
                      (totalStudents + totalGrades) * sizeof(int);

  void* memory = std::malloc(bytes);
  if (memory == nullptr) {
    delete[] gradesCount;
    delete[] studentsInGroup;
    return 1;
  }

  char* ptr = static_cast<char*>(memory);

  int*** grades = reinterpret_cast<int***>(ptr);
  ptr += groupCount * sizeof(int**);

  for (int g = 0; g < groupCount; ++g) {
    grades[g] = reinterpret_cast<int**>(ptr);
    ptr += studentsInGroup[g] * sizeof(int*);
  }

  int* data = reinterpret_cast<int*>(ptr);

  int studentIndex = 0;
  for (int g = 0; g < groupCount; ++g) {
    for (int s = 0; s < studentsInGroup[g]; ++s) {
      int count = gradesCount[studentIndex++];

      grades[g][s] = data;
      *data++ = count;

      // Ввод 4: сами оценки студента
      for (int i = 0; i < count; ++i) {
        std::cin >> *data;
        ++data;
      }
    }
  }

  delete[] gradesCount;

  if (!std::cin) {
    delete[] studentsInGroup;
    std::free(memory);
    return 1;
  }

  std::cout << std::fixed << std::setprecision(2);

  for (int g = 0; g < groupCount; ++g) {
    int sum = 0;
    int marks = 0;
    int bestStudent = -1;
    double bestAverage = 0.0;

    for (int s = 0; s < studentsInGroup[g]; ++s) {
      const int* row = grades[g][s];
      int count = row[0];

      if (count == 0) {
        continue;
      }

      int studentSum = 0;
      for (int i = 1; i <= count; ++i) {
        studentSum += row[i];
      }

      sum += studentSum;
      marks += count;

      double average = static_cast<double>(studentSum) / count;
      if (bestStudent == -1 || average > bestAverage) {
        bestAverage = average;
        bestStudent = s;
      }
    }

    if (marks == 0) {
      std::cout << "Group " << g << ": no grades\n";
    } else {
      std::cout << "Group " << g << ": average "
                << static_cast<double>(sum) / marks << ", best student #"
                << bestStudent << " (" << bestAverage << ")\n";
    }
  }

  delete[] studentsInGroup;
  std::free(memory);

  return 0;
}