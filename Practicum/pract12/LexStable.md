# Lex Stable Формат за дата и време в C++

## Форматът `Lex Stable` - overview
Форматът **Lex Stable** следва следната структура:

```
YYYY-MM-DD HH:MM:SS
```

- `YYYY`: 4-цифрено число, обозначаващо година (напр. 2025)
- `MM`: 2-цифрено число, обозначаващо месец (01–12)
- `DD`: 2-цифрено число, обозначаващо ден (01–31)
- `HH`: 2-цифрено число, обозначаващо часа във формат 24 часа (00–23)
- `MM`: 2-цифрено число, обозначаващо минутите (00–59)
- `SS`: 2-цифрено число, обозначаващо секундите (00–59)

### Примерен Код
Следният код демонстрира как да форматирате `std::time_t` във формат Lex Stable и да го запазите в `std::string`:

```cpp
#include <iostream>
#include <string>
#include <ctime>

std::string formatTimeAsLexStable(std::time_t time) {
    // Конвертирайте std::time_t в структура std::tm (структура, която държи датата и часа във формат, разбит на компоненти - секунди, минути, час, ...)
    std::tm* localTime = std::localtime(&time);

    // Форматирайте времето като "YYYY-MM-DD HH:MM:SS" и го запазете в string
    char buffer[20];
    std::snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d",
                  localTime->tm_year + 1900,
                  localTime->tm_mon + 1,
                  localTime->tm_mday,
                  localTime->tm_hour,
                  localTime->tm_min,
                  localTime->tm_sec);
    return std::string(buffer);
}

int main() {
    // Вземете текущото време
    std::time_t now = std::time(nullptr);

    // Форматирайте текущото време като Lex Stable
    std::string formattedTime = formatTimeAsLexStable(now);

    // Отпечатайте форматираното време
    std::cout << "Текуща дата и време: " << formattedTime << std::endl;

    return 0;
}
```

### Обяснение на Кода
1. **`std::time_t` и `std::localtime`**:
   - `std::time_t` представлява текущото време като брой секунди от 1 януари 1970 г. (епохата).
   - `std::localtime` конвертира това време в структура `std::tm`, която съдържа компоненти като година, месец, ден и др.
2. **`std::snprintf`**:
   - Форматира компонентите на времето в стринг с формат Lex Stable.
3. **Гъвкавост**:
   - Функцията `formatTimeAsLexStable` може да бъде използвана с всяко време от тип `std::time_t`, не само с текущото.

### Примерен Резултат
Когато стартирате програмата, изходът ще изглежда по следния начин:

```
Текуща дата и време: 2025-01-07 15:45:12
```

## Приложения
- **Логове**: Гарантира, че логовете са подредени хронологично.
- **Организиране на данни**: Използвайте го като ключ за съхранение или извличане на данни.
- **Timestamps**: Добавете Timestamps към събития в приложенията.