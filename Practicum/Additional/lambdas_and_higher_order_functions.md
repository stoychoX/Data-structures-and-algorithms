# Функции от по-висок ред и ламбда функции в C++

## Указатели към функции

![image](https://github.com/desiish/OOP_Pract_2023_2024/assets/115353472/ba159e4b-ec0b-4827-a498-ccd469ab60d1)

Всяка функция си има определено място в паметта. Съответно можем да насочим указател към нея. Този указател представлява всъщност адреса на изпълнимия код на дадена функция.
```c++
#include <iostream>

int add(int x, int y) {
    return x + y;
}

int main() {
    int(*addPtr)(int, int) = add; // pointer to function that accepts 2 integers as arguments and returns an integer as a result

    int resFromPtr = addPtr(2, 3);
    int resFromFunc = add(2, 3);

    std::cout << resFromFunc << " " << resFromPtr; // 5 5
}
```
❗Не можем да извършваме аритметични операции върху тези указатели.

## Функции от по-висок ред

Функциите от по-висок ред в C++ са функции, които могат да приемат други функции като аргументи или да връщат функции като резултат. Те позволяват писането на по-кратък и по-четим код, като в същото време се поддържа неговата функционалност.

Един от най-често срещаните начини за използване на функции от по-висок ред е подаването на функции като аргументи на други функции. Например, функциите `std::sort` и `std::find_if` от стандартната библиотека на C++ приемат функции като аргументи, които задават критерии съответно за сортиране и търсене на данните, които са им подадени.

## Ламбда функции

Ламбда функциите в C++ са безименни (анонимни) функции, които могат да се дефинират на място и да се използват там, където се очаква функция. Те са полезни за кратки и еднократни операции, където не е необходимо да се дефинира отделна функция.

Синтаксисът на ламбда функциите е:
```c++
[capture list] (parameters) -> return_type { function_body }
```
Стрелката (->) и типът на връщане не са задължителни при дефиниране на ламбда функции, когато компилаторът може автоматично да определи връщания тип на функцията. В този случай може да се използва следният синтаксис:
```c++
[capture list] (parameters) { function_body }
```
където:
- `capture list`: Списъкът с capture-нати променливи, които ламбда функцията ще използва. Те са външни (от външен scope) и обикновено не би трябвало да бъдат променяни от ламбдата;
- `parameters`: Списъкът с параметри на ламбда функцията;
- `return_type`: Типът на върнатата стойност от ламбда функцията (опционален);
- `function_body`: Тялото на ламбда функцията, което съдържа операциите, които тя трябва да изпълни.


## Можем ли да подаваме ламбда функции като параметър на други функции?
Отговорът е зависи. Една функция от по-висок ред приема указател към друга функция, която да използва някъде в тялото на кода си. 

Сега си представете една ламбда функция в паметта - тя представлява един обект - обвивка на функцията. Можем да мислим за него като за една кутийка. В нея запазваме както информацията за функцията, така и данните от *capture list*-a й. Когато нямаме нищо в *capture list*-а, тя може да се преобразува в пойнтър към функция от съответния тип, защото няма да изгубим никаква информация по време на това преобразуване. Така можем да я подадем като аргумент на друга функция, очакваща такъв тип указател. Но когато имаме capture-нати променливи, няма как просто да ги пренебрегнем. Съответно преобразуването става невъзможно.

![image](https://github.com/desiish/oop_tasks/assets/115353472/b50deece-aec9-4d55-848f-8f4dbc923181)

❗Затова ламбда функции ще подаваме като аргумент на други функции само когато в *capture list*-a им нямаме никакви данни.

## Пример
**Задача:** Търсим броя символи в даден стринг, отговарящи на някакво условие:
- да са цифри;
- да са малки латински букви;
- да са главни латински букви.

Примерно решение:
```c++
#include <iostream>

namespace Constants {
    constexpr int INVALID_COUNT = -1;
}

enum class Criteria {
    FIND_UPPERS, 
    FIND_LOWERS,
    FIND_DIGITS,
    UNKNOWN
};

int getCountOfSymbols(const char* str, bool (*pred) (char ch)) {
    if (!str)
        return Constants::INVALID_COUNT;

    int count = 0;
    while (*str) {
        if (pred(*str))
            count++;

        str++;
    }

    return count;
}

//with lambda expressions

int getCountOfSymbolsByCriteriaLambdas(const char* str, Criteria cr) {
    switch (cr) {
    case Criteria::FIND_DIGITS: return getCountOfSymbols(str, [](char ch) {return ch >= '0' && ch <= '9'; });
    case Criteria::FIND_LOWERS: return getCountOfSymbols(str, [](char ch) {return ch >= 'a' && ch <= 'z'; });
    case Criteria::FIND_UPPERS: return getCountOfSymbols(str, [](char ch) {return ch >= 'A' && ch <= 'Z'; });
    default: return Constants::INVALID_COUNT;
    }
}

//with already defined functions

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isLower(char ch) {
    return ch >= 'a' && ch <= 'z';
}

bool isUpper(char ch) {
    return ch >= 'A' && ch <= 'Z';
}

int getCountOfSymbolsByCriteriaDefinedFuncs(const char* str, Criteria cr) {
    switch (cr) {
    case Criteria::FIND_DIGITS: return getCountOfSymbols(str, isDigit);
    case Criteria::FIND_LOWERS: return getCountOfSymbols(str, isLower);
    case Criteria::FIND_UPPERS: return getCountOfSymbols(str, isUpper);
    default: return Constants::INVALID_COUNT;
    }
}
```
