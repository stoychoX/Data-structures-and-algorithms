#include"../Seminar04/linked-list-utils.h"

bool hasCycle(LinkedListNode<int>* head) {
    LinkedListNode<int> *fast = head;
    LinkedListNode<int> *slow = head;

    while (fast && fast->next && slow) {
        fast = (fast->next)->next;
        slow = slow->next;

        if (fast == slow)
            return true;
    }

    return false;
}

int main() {
    using Node = LinkedListNode<int>;

    Node* last = new Node(6);

    Node* list = new Node(1,
    new Node(2,
    new Node(3,
    new Node(4,
    new Node(5,  
    last)))));

    last->next = list->next->next;

    hasCycle(list);
}