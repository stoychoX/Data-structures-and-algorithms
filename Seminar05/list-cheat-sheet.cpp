#include<list>
#include<iostream>
#include"../Seminar04/linked-list-utils.h"

// Пример как да напишем една и съща функция
// Чрез итератори и чрез пойнтър представянето

// Функцията map приема свързан списък и функция която приема int
// и прилага функцията върху всеки елемент от списъка
void mapOnSTLList(std::list<int>& ll, void (*f)(int&)) {
    for(int& elem : ll)
        f(elem);
}

void mapOnListRepresentedAsPointer(LinkedListNode<int>* ll, void (*f)(int&)) {
    while(ll) {
        f(ll->data);
        ll = ll->next;
    }
}

//.....

void printList(const std::list<int>& myList, const char* msg) {
    if(msg != "")
        std::cout << msg << std::endl;
    
    // range based for loop който извежда всички елементи на списъка
    for(const int& elementInList : myList) 
        std::cout << elementInList << " ";
    std::cout << std::endl;
}

int main() {
    std::list<int> myList;

    const auto f = myList.begin();

    // Добави елемент в края на листа
    for (int i = 0; i < 10; i++)
        myList.push_back(i);

    // Добави елемент в началото на листа
    for(int i = 10; i < 20; i++)
        myList.push_front(i);

    printList(myList, "Added the elements from [0..9] to the back and [10..19] to the front");

    // Можем да изтриваме елементи на позиция
    myList.erase(myList.begin());
    printList(myList, "Erased the first element");

    // Удобен начин да обърнем списък
    myList.reverse();
    printList(myList, "Reversed the linked list");

    // Можем да премахнем елемент
    myList.remove(10);
    printList(myList, "After removing 10 from the list");

    // Можем да премахнем всички елементи, които отговарят на някакъв предикат
    // Аргумента на remove_if е булева функция. Ще останат само тези за които условието е лъжа.
    myList.remove_if([](const int& currentElement) -> bool { return currentElement % 2; });
    printList(myList, "Filter all odd elements");
 
    // myList.begin(); begin iterator
    // myList.end();   end iterator

    // myList.cbegin(); constang begin iterator
    // myList.cend();   constant end iterator

    // Мога да създавам списъци така
    std::list<int> second{1, 2, 3, 4, 5};
    printList(second, "Create second list with initializer list");
    
    // Премества елементи от един лист в друг
    myList.splice(myList.begin(), second);
    printList(myList, "First list after splice");
    printList(second, "second list after splice");

    // Да си върнем малко елементи във втория списък
    second.assign({1, 2, 3, 4, 5});
    printList(second, "Second list after .assign({1, 2, 3, 4, 5})");

    // Можем да сортираме листа
    myList.sort();
    printList(myList, "First list after beigg sorted");

    // Можем и да го сортираме наобратно
    myList.sort([](const int& fst, const int& snd) -> bool { return fst > snd; });
    printList(myList, "First list after being sorted with >");

    LinkedListNode<int>* pointreLinkedlist = 
            new LinkedListNode<int>(1, 
            new LinkedListNode<int>(2,
            new LinkedListNode<int>(3,
            new LinkedListNode<int>(4,
            new LinkedListNode<int>(5)))));
    
    mapOnListRepresentedAsPointer(pointreLinkedlist, [](int& x) -> void {x = 2*x; });
    mapOnSTLList(second, [](int& x) -> void { x = 2*x; });

    printList(second, "Second list after mappint 2*");
    std::cout << "Pointer linked list after mappint 2* " << std::endl;
    printLinkedList(pointreLinkedlist);
    std::cout << std::endl;

    // Как да добавяме елементи на произволна позиция?

    // Итератор към началото
    std::list<int>::iterator it = myList.begin();

    // Отиваме на позицията
    for (size_t i = 0; i < 2; i++) {
        ++it;
    }

    // Добавяме
    myList.insert(it, 10000);
    // insert може да вмъква и цели рейнджове
    printList(myList, "My list after adding 10000 in third pos");
}