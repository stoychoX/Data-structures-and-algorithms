#include "linked-list-utils.h"

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

void example() {
    LinkedListNode<int>* ll = new LinkedListNode(1, new LinkedListNode(2, new LinkedListNode(3, new LinkedListNode(4))));
    printLinkedList(ll);
    reverseLinkedList(ll);
    printLinkedList(ll);
    freeList(ll);
}