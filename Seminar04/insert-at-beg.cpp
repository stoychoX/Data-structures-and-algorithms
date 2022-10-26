#include"linked-list-utils.h"

template<class T>
void insertAtBegin(LinkedListNode<T>*& ll, const T& elem) {
    LinkedListNode<T>* toInsert = new LinkedListNode(elem, ll);
    ll = toInsert;
}

void example() {
    LinkedListNode<int>* ll = new LinkedListNode(1, new LinkedListNode(2, new LinkedListNode(3)));
    printLinkedList(ll);
    insertAtBegin(ll, 0);
    printLinkedList(ll);
    freeList(ll);
}

int main() {
    

}