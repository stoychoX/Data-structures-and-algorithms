#include<iostream>
#include<initializer_list>

template<class T>
struct LinkedListNode {
    T data;
    LinkedListNode<T>* next;

    LinkedListNode(const T& elem, LinkedListNode<T>* n = nullptr) : data{elem}, next {n} {} 
};

template<class T>
void printLinkedList(const LinkedListNode<T>* ll) {
    const LinkedListNode<T>* iterate = ll;

    while(iterate) {
        std::cout << iterate->data << " ";
        iterate = iterate->next;
    }

    std::cout << std::endl;
}

template<class T>
void printLinkedList(const LinkedListNode<T>* ll, void (*print)(T)) {
    const LinkedListNode<T>* iterate = ll;

    while(iterate) {
        print(iterate->data);
        iterate = iterate->next;
    }

    std::cout << std::endl;
}

template<class T>
void printLinkedList(const LinkedListNode<T>* ll, void (*print)(const T&)) {
    const LinkedListNode<T>* iterate = ll;

    while(iterate) {
        print(iterate->data);
        iterate = iterate->next;
    }

    std::cout << std::endl;
}

template<class T>
LinkedListNode<T>* fromList(const std::initializer_list<T>& l) {
    LinkedListNode<T>* toReturn = nullptr;
    LinkedListNode<T>* iter = nullptr;

    for(const auto& elem : l) {
        LinkedListNode<T>* toInsert = new LinkedListNode<T>(elem);
        if(iter == nullptr) {
            toReturn = toInsert;
            iter = toInsert;
        }
        else {
            iter->next = toInsert;
            iter = iter->next;
        }
    }
    return toReturn;
}

template<class T>
void freeList(LinkedListNode<T>* ll) {
    while(ll) {
        LinkedListNode<T>* toDelete = ll;
        ll = ll->next;
        delete toDelete;
    }
}