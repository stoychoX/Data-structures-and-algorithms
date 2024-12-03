# Практикум №9 по Структури от данни, спец. ИС

## `Binary Heap`
**Binary Heap**-a представлява дървовидна структура от данни, която изпълнява 2 условия:
1) пълно двоично дърво е (всички нива са запълнени освен последното);
2) всеки връх има стойност <= (респективно >=) на тази на родителя си (heap property);

> [!IMPORTANT]
> От условията следва, че винаги най-големият (респективно най-малкият) елемент е на върха на пирамидата, НО данните вътре не са винаги сортирани.

Обикновено се представя чрез масив, като е изпълнено следното:
- за всеки родител на индекс i лявото му дете е на индекс 2i + 1, а дясното - на 2i + 2;
- за всяко дете на индекс i родителят му се намира на индекс (i - 1) / 2;
- коренът е на индекс 0.

Разграничаваме 2 вида heap:
- `minHeap` - най-малкият елемент е най-отгоре;
- `maxHeap` - най-големият елемент е най-отгоре;

### Как от вектор можем да създадем heap?
STL поддържа методи, които ни позволяват да работим с вектор като с heap. Това са следните:
- **Превръщане на heap**: `std::make_heap(begin_it, end_it)` - O(N)
- **Добавяне на елемент**:
  - Добавяме елемент в края на контейнера.
  - Викаме `std::push_heap(begin, end)` - O(logN)
- **Извличане на най-големия елемент**:
  - Викаме `std::pop_heap(begin, end)` - O(logN)
  - Премахваме елемента в края.
- **Проверка дали е heap**: `std::is_heap(begin, end)` - O(N)

Нека разгледаме и техните имплементации:
```c++
#include <iostream>
#include <vector>

template <typename RandomIt, typename Compare>
void heapify(RandomIt first, size_t rootIdx, size_t size, Compare comp) {
    size_t largest = rootIdx;
    size_t leftChild = 2 * rootIdx + 1;
    size_t rightChild = 2 * rootIdx + 2;

    if (leftChild < size && comp(*(first + largest), *(first + leftChild)))
        largest = leftChild;

    if (rightChild < size && comp(*(first + largest), *(first + rightChild)))
        largest = rightChild;

    if (largest != rootIdx) {
        std::swap(*(first + rootIdx), *(first + largest));
        heapify(first, largest, size, comp);
    }
}

template <typename RandomIt, typename Compare = std::less<>>
void make_heap(RandomIt first, RandomIt last, Compare comp = Compare()) {
    size_t size = last - first; // should use std::dist for when its not vector

    for (int i = size / 2; i >= 0; --i)
        heapify(first, i, size, comp);
}

template <typename RandomIt, typename Compare>
void bubble_up(RandomIt first, size_t index, Compare comp) {
    while (index > 0) {
        size_t parentIndex = (index - 1) / 2;

        if (!comp(*(first + parentIndex), *(first + index)))
            break;

        std::swap(*(first + parentIndex), *(first + index));
        index = parentIndex; 
    }
}

template <typename RandomIt, typename Compare = std::less<>>
void push_heap(RandomIt first, RandomIt last, Compare comp = Compare()) {
    size_t size = last - first; // should use std::dist for when its not vector

    if (size > 1) 
        bubble_up(first, size - 1, comp);
}

template <typename RandomIt, typename Compare = std::less<>>
void pop_heap(RandomIt first, RandomIt last, Compare comp = Compare()) {
    size_t size = last - first; // should use std::dist for when its not vector

    if (size > 1) {
        std::swap(*first, *(last - 1));
        heapify(first, 0, size - 1, comp);
    }
}

template <typename RandomIt, typename Compare = std::less<>>
bool is_heap(RandomIt first, RandomIt last, Compare comp = Compare()) {
    size_t size = last - first; // should usestd:: dist for when its not vector

    for (size_t i = 0; i < size / 2; ++i) {
        size_t leftChild = 2 * i + 1;
        size_t rightChild = 2 * i + 2;

        if (leftChild < size && comp(*(first + i), *(first + leftChild)))
            return false;

        if (rightChild < size && comp(*(first + i), *(first + rightChild)))
            return false;
    }

    return true;
}
```

Както се вижда, по default методите използват `std::less<>` за сравнение на обектите, така че default-ния heap е `maxHeap`. 

> [!NOTE]
> Ако искаме да създадем `minHeap`, то като comparator трябва да подадем `std::greater<>`.

Структурата от данни, която е създадена на базата на `Binary Heap`-a, е т.нар. `Priority Queue` или приоритетна опашка на български.

## `std::priority_queue`

`std::priority_queue` представлява обвиващ клас за контейнер (std::vector по default), изграден на основата на heap-a. По default е изграден като maxHeap, т.е.
ни гарантира, че винаги най-големия елемент ще е първи. Поддържа следните операции:
- **Добавяне на елемент**: `pq.push(value)` - O(logN)
- **Премахване на елемента с най-висок приоритет**: `pq.pop()` - O(logN)
- **Достъп до елемента с най-висок приоритет**: `pq.top()` - O(1)
- **Проверка на размера**: `pq.size()` - O(1)
- **Проверка за празнота**: `pq.empty()` - O(1)

Нека разгледаме какви параметри приема в шаблона си:
```c++
template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class priority_queue;
```


Ето и примерна имплементация:
```c++
#include <iostream>
#include <vector>
#include <algorithm>

template<class T, class Container = std::vector<T>, class Comp = std::less<T>>
class priority_queue
{
    Container _c;
    Comp _comp;

public:
    void push(const T& value)
    {
        _c.push_back(value);
        std::push_heap(_c.begin(), _c.end(), _comp);
    }

    void push(T&& value)
    {
        _c.push_back(std::move(value));
        std::push_heap(_c.begin(), _c.end(), _comp);
    }

    void pop()
    {
        std::pop_heap(_c.begin(), _c.end(), _comp);
        _c.pop_back();
    }

    bool empty() const
    {
        return _c.empty();
    }

    const T& top() const
    {
        if (empty())
            throw std::runtime_error("Empty container");

        return _c.front();
    }

    size_t size() const
    {
        return _c.size();
    }
};
```

И тук, ако искаме да създадем minHeap, трябва да подадем `std::greater<>` като custom comparator.

### Пример с min-heap

```c++
#include <queue>
#include <vector>
#include <iostream>

int main() 
{
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq(v.begin(), v.end());
    
    while (!pq.empty()) 
    {
        std::cout << pq.top() << ' ';
        pq.pop(); 
    }
}
```

---
[**Линк към задачите**](https://leetcode.com/problem-list/aglkjy9v/)
