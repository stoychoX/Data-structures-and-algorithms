
# `std::unordered_map` и `std::unordered_set`

## Въведение в `std::unordered_set`

`std::unordered_set` е асоциативен контейнер, който съхранява уникални обекти в произволен ред. 
Обикновено е реализиран чрез хеш таблица използваща separate chaining.

При създаване на обект от тип `std::unordered_set`, могат да се зададат следните параметри:

```c++
template<
    class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
> class unordered_set;
```

- **Key**  
  Типът на обектите, които ще се съхраняват в множеството.

- **Hash**  
  Хешираща функция, която изчислява хеш стойности за обектите.  
  *По подразбиране:* Използва се `std::hash<Key>`.

- **KeyEqual**  
  Функция за сравнение, която проверява дали два обекта са равни.  
  *По подразбиране:* Използва се `std::equal_to<Key>`.

- **Allocator**  
  Механизъм за управление на паметта, който определя как ще се разпределя и освобождава паметта за елементите в множеството.  
  *По подразбиране:* Използва се стандартният алокатор `std::allocator<Key>`.

---

### Операции

- **Добавяне на елементи**: `unordered_set.insert(value)` - Θ(1) (average-case), O(N) (worst-case)
- **Премахване на елементи**: `unordered_set.erase(value)`- Θ(1) (average-case), O(N) (worst-case)
- **Търсене на елементи**: `unordered_set.find(value)` - Θ(1) (average-case), O(N) (worst-case)
- **Проверка на размера**: `unordered_set.size()` - O(1)

---

```c++
#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<int> mySet = {3, 1, 2, 5, 4, 8, 3};

    for (auto it = mySet.begin(); it != mySet.end();) {
        if (*it % 2 == 0) {
            it = mySet.erase(it);
        } else {
            ++it;
        }
    }

    for (auto& el : mySet) {
        std::cout << el << ' ';
    }

    return 0;
}
```

---

## Въведение в `std::unordered_map`

`std::unordered_map` е асоциативен контейнер, който съхранява двойки ключ-стойност в произволен ред. Ключовете са уникални, като всеки ключ съответства на една стойност. Обикновено е реализиран чрез хеш таблица иползващ separate chaining.

---

### Шаблон за декларация

```c++
template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
> class unordered_map;
```

- **Key**  
  Типът на ключовете.

- **T**  
  Типът на стойностите.

- **Hash**  
  Хешираща функция, която изчислява хеш стойности за ключовете.  
  *По подразбиране:* Използва се `std::hash<Key>`.

- **KeyEqual**  
  Функция за сравнение, която проверява дали два ключа са равни.  
  *По подразбиране:* Използва се `std::equal_to<Key>`.

- **Allocator**  
  Механизъм за управление на паметта, който определя как ще се разпределя и освобождава паметта за елементите в контейнера.  
  *По подразбиране:* Използва се `std::allocator<std::pair<const Key, T>>`.

---

### Операции

- **Добавяне на елементи**: `unordered_map[key] = value` - Θ(1) (average-case), O(N) (worst-case)
- **Достъп до елементи**: `unordered_map[key]` -           Θ(1) (average-case), O(N) (worst-case)
- **Премахване на елементи**: `unordered_map.erase(key)` - Θ(1) (average-case), O(N) (worst-case)
- **Търсене на елементи**: `unordered_map.find(key)` -     Θ(1) (average-case), O(N) (worst-case)
- **Проверка на размера**: `unordered_map.size()` -        O(1)

---

```c++
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<int, std::string> myMap = {
        {"Three", 3},
        {"One", 1},
        {"Two", 2}
    };

    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << '\n';
    }

    for (auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << '\n';
    }

    // C++ 17
    for (auto& [key, value] : myMap) {
        std::cout << "Key: " << key << ", Value: " << value << '\n';
    }

    return 0;
}
```
----
[Линк към задачите](https://leetcode.com/problem-list/asohzosr/)

В час : №3, №500, №3330

Вкъщи: №49, №859
