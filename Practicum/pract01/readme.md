# Практикум №1 по СД, спец. ИС

## Функцията std::sort
`std::sort` е стандартна функция в C++, която се използва за сортиране на елементи от дадена колекция от данни. Тя е част от стандартната библиотека `<algorithm>`, която съдържа различни алгоритми за обработка на колекции от данни.

Най-често е имплементирана или чрез `Quick Sort`, или чрез алгоритъм, комбиниращ `Quick Sort`, `Heap Sort` (за който ще научите по-натам в курса) и `Insertion Sort`. 

Декларация на функцията:
```c++
#include <algorithm>

template <class RandomIt>
void sort(RandomIt first, RandomIt last);

template <class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);

```

- `Параметри`:
  - first: Итератор, указващ началото на колекцията елементи, които трябва да бъдат сортирани.
  - last: Итератор, указващ края на колекцията елементи, които трябва да бъдат сортирани (сочи елементът след последния елемент в диапазона).
  - comp (по избор): критерий за сортиране (по default се използва operator<).

- `Сложност`: std::sort има средна времева сложност O(n*log n), където n е броят на елементите, които искаме да бъдат сортирани.
- `In-Place`: std::sort е in-place алгоритъм.
- `Stable`: std::sort не е стабилен алгоритъм.

- Пример с функция:
```c++
#include <iostream>
#include <algorithm>
#include <vector>

bool compareLastDigit(int a, int b) {
    return (a % 10) < (b % 10); 
}

int main() {
    std::vector<int> v = {25, 42, 33, 14, 56};

    std::sort(v.begin(), v.end(), compareLastDigit);

    for (const int& n : v) {
        std::cout << n << ' ';
    }
    return 0;
}

```

- Пример с **ламбда** функция:
```c++
#include <iostream>
#include <algorithm>
#include <vector>

struct PairOfInt {
    int first;
    int second;
};

int main() {
    std::vector<PairOfInt> v = { {1, 2}, {2, 1}, {5, 7}, {3, 3}, {4, 3} };

    std::sort(v.begin(), v.end(), [](const PairOfInt& lhs, const PairOfInt& rhs) { return lhs.second < rhs.second; });

    for (const auto& n : v) {
        std::cout << n.first << ' ' << n.second << std::endl;
    }
    return 0;
}

```

## Задачи и линк към методите на `std::vector`
- [**std::vector**](https://cplusplus.com/reference/vector/vector/)
- [**Линк към задачите**](https://leetcode.com/problem-list/an1ryio3/)
