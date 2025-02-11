# Практикум №8 по Структури от данни, спец. ИС

На семинари вече сте разгледали балансирани дървета. Едни много известни балансирани дървета са именно т.нар. Red-Black Trees. Те работят по малко по-различен начил от AVL. 
Балансираността тук не е дефинирана чрез balance factor, а чрез редица свойства, които винаги трябва да са в сила (така наречения **инвариант**).

Инвариантът на Red-Black Tree гласи:
1) Всеки възел има цвят - черен или червен

2) Всеки NIL възел (празен възел) е черен

3) Червен възел не може да има червен наследник

4) Всеки път от произволен връх до всички NIL елементи в поддървото му трябва да преминава през равен брой черни върхове

5) Коренът винаги е черен (не е задължително, но често се прилага)

* Следствие: Ако произволен връх има точно 1 наследник, то той е червен

Балансирането отново се извършва по време на самите операции за добавяне и премахване. Отново се разчита на принципа на ротациите, но също така има случаи в които вместо ротация се предпочита обикновенно преоцветяване на върховете.

[Визуализация на RB tree](https://ds2-iiith.vlabs.ac.in/exp/red-black-tree/red-black-tree-oprations/simulation/redblack.html)

На базата на червено-черното дърво са имплеметирани 2 от най-използваните структури от данни - std::set и std::map.

## `std::set`
std::set представлява дърво от уникални стойности, наречени ключове. 
При създаване на обект от тип `std::set`, могат да се зададат три типа параметри:

```c++
template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> class set;
```
- **Key**  
  Типът на обектите, които ще се съхраняват в множеството.

- **Compare**  
  Функция или обект за сравнение, която определя критерия за сравнение между елементите. Това влияе върху начина, по който множеството подрежда елементите.  
  *По подразбиране:* Използва се стандартният оператор за сравнение за съответния тип (`std::less<Key>`).

- **Allocator**  
  Механизъм за управление на паметта, който определя как ще се разпределя и освобождава паметта за елементите в множеството.  
  *По подразбиране:* Използва се стандартният алокатор `std::allocator<Key>`.
  
Поддържа следните методи:
- **Добавяне на елементи**: `set.insert(value)` - O(logN) (връща pair<iterator, bool>);
- **Премахване на елементи**: `set.erase(value)`- O(logN) (връща колко елементи са били премахнати);
- **Премахване на елементи чрез итератор**: `set.erase(iterator)`- Θ(1) / O(logN) (връща итератор към следващия елемент);
- **Търсене на елементи**: `set.find(value);` - O(logN) (връща итератор или `set.end()`, ако не е намерен);
- **Проверка на размера**: `set.size()` - O(1)

```c++
template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>

> class map;
```

## `std::map`
std::map представлява дърво от двойки от ключ и стойност. Всеки ключ е уникален. 

- **Key**  
  Типът на обектите, които ще се съхраняват в множеството.

- **T**  
  Типът на обектите, които ще се съхраняват в множеството.

- **Compare**  
  Обект или функция за сравнение, която определя как ключовете се подреждат в контейнера.
  *По подразбиране:* Използва се стандартният оператор за сравнение за съответния тип на ключа (`std::less<Key>`).

- **Allocator**  
  Механизъм за управление на паметта, който определя как ще се разпределя и освобождава паметта за елементите в множеството.  
  *По подразбиране:* Използва се стандартният алокатор `std::allocator<std::pair<const Key, T>>`.

  Поддържа следните операции:
- **Добавяне на елементи**: `map[key] = value`- O(logN)
- **Достъп до елементи**: `map[key]` - O(logN)
- **Премахване на елементи**: `map.erase(key)` - O(logN) (връща колко елементи са били премахнати)
- **Премахване на елементи чрез итератор**: `map.erase(iterator)` - Θ(1) / O(logN) (връща итератор към следващия елемент)
- **Търсене на елементи**: `map.find(key)` - O(logN) (връща итератор или `map.end()`, ако не е намерен)
- **Проверка на размера**: `map.size()` - O(1)

---
[Линк към задачите](https://leetcode.com/problem-list/a6culvq1/)
