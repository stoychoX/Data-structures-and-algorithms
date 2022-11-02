#include"linked-list-utils.h"
#include<deque>

// O(n) time
// O(n) complexity
void reorderWithDeque(LinkedListNode<int>* head) {
    if(!head || !head->next)
            return;
        
    std::deque<LinkedListNode<int>*> dq;
    
    LinkedListNode<int>* it = head;
    
    while(it) {
        dq.push_back(it);
        it = it->next;
    }

    // Винаги пазим края на вече готовия списък
    // Ако не е ясно как го използвам прочети обяснението над втория метод
    // идеята е същата.
    LinkedListNode<int>* backOfNewList = nullptr;

    while(!dq.empty()) {
        // Ако размерът е 1 то имаме нечетен брой елементи и просто добавяме последния в края
        if(dq.size() == 1) {
            backOfNewList->next = dq.front();
            backOfNewList = backOfNewList->next;
            break;
        }
        
        // Първия елемент останал в дека започва да сочи към последния.
        // Генерираме коректна двойка.
        dq.front()->next = dq.back();
        
        // Ако края на списъка не е nullptr следващите два елемента
        // в списъка са dq.front()->dq.front()->next (което е dq.back())
        if(backOfNewList)
            backOfNewList->next = dq.front();   // Сложи следващите два елемента накрая
        
        backOfNewList = dq.front()->next;       // Вече края на списъка е друг. Преместваме се там.

        dq.pop_back();
        dq.pop_front();
    }

    // next на последния елемент от списъка е nullptr, този ред е важен.
    backOfNewList->next = nullptr;
}

// Това ще ни помогне за второто решение
template<class T>
void reverseLinkedList(LinkedListNode<T>*& ll) {
    LinkedListNode<T>* previous = nullptr;
    LinkedListNode<T>* next = nullptr;
    LinkedListNode<T>* iterate = ll;

    while(iterate) {
        next = iterate->next;
        iterate->next = previous;
        previous = iterate;
        iterate = next;
    }

    ll = previous;
}

// Това също
template<class T>
LinkedListNode<T>* findMiddle(LinkedListNode<T>* ll) {
    LinkedListNode<T>* fast = ll;
    LinkedListNode<T>* slow = ll;

    while(fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    return slow;
}

/*
Тук идеята е да намерим средата и да я обърнем. Две неща, които вече знаем как да правим. Как ще протече алгоритъма:

Вход: 1 -> 2 -> 3 -> 4 -> 5
Среда: 3 -> 4 -> 5

Обърната среда: 5 -> 4 -> 3 -> nullptr
Как изглежда първоначалния масив: 1 -> 2 -> 3 -> nullptr

Дали е бъг, че и в двата списъка имаме еднакъв последен елемент? Малко неточно е, но за да го оправя трябва да променя функциите. 
С цел да са разбираеми нещата го оставям така.

В случая става нещо подобно:
1-> 2 -> 3 -> nullptr
        ^
5 -> 4 /

Виждаме, че последователно трябва да вземаме двойки (L_0 -> L_n) -> (L_1 -> L_{n-1}) -> (L_2 -> L_{n - 2}) -> ... и да ги поставяме една след друга.

* firstHalf -> първата половина от списъка
* mid       -> Втората половина от списъка
* currentPair -> текущата двойка (L_i -> L_{n - i})
* backOfList -> Края на коректния списък от двойки

Сега имаме този сценарий:
[някакъв коректен списък] [коректна двойка]
* Насочи края на този коректен списък да сочи към коректната двойка. Това става лесно понеже му пазя края!
[някакъв вече готов списък] -> [коректна двойка]
* Сега насочи указателя който пази края на коректния списък да сочи към края на този списък, понеже този списък е корекрен.
[стария коректен списък -> коректната двойка] - готов за още коректни двойки!

Така добавямe коректни двойки докато не стигна края на списъка съдържащ обърнатата дясна част.
*/
void reorderWithTwoPointers(LinkedListNode<int>* ll) {
    if(!ll || !ll->next)
        return;

    LinkedListNode<int>* mid = findMiddle(ll);
    reverseLinkedList(mid);

    LinkedListNode<int>* firstHalf = ll;
    LinkedListNode<int>* currentPair = nullptr;
    LinkedListNode<int>* backOfList = nullptr;

    while(mid) {
        currentPair = firstHalf;
        firstHalf = firstHalf->next;

        // Случая в който имаме нечетен брой елементи
        if(!firstHalf) {
            backOfList->next = currentPair;
            backOfList = backOfList->next;
            break;
        }

        currentPair->next = mid;
        mid = mid->next;

        if(backOfList)
            backOfList->next = currentPair; // Пренасочи края към коректната двойка. Ако е nullptr нямаме какво да пренасочваме.
        
        backOfList = currentPair->next;     // И един бърз ъпдейт на края - вече края на коректния лист е стария лист + новата двойка
    }

    backOfList->next = nullptr;
}

int main() {
    LinkedListNode<int>* ll = new LinkedListNode<int> 
    (1, new LinkedListNode<int>
    (2, new LinkedListNode<int>
    (3, new LinkedListNode<int>
    (4, new LinkedListNode<int>
    (5)))));

    reorderWithTwoPointers(ll);
    printLinkedList(ll);
    freeList(ll);
}