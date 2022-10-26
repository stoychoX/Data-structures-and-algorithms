#include"linked-list-utils.h"

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

void example() {
    LinkedListNode<int>* ll = new LinkedListNode(1, new LinkedListNode(2, new LinkedListNode(3, new LinkedListNode(4))));
    LinkedListNode<int>* lls = new LinkedListNode(1, new LinkedListNode(2, new LinkedListNode(3, new LinkedListNode(4, new LinkedListNode(5)))));

    LinkedListNode<int>* firstMiddle = findMiddle(ll);
    LinkedListNode<int>* secondMiddle = findMiddle(lls);

    std::cout << firstMiddle->data << " " << secondMiddle->data;

    freeList(ll);
    freeList(lls);
}