#include<iostream>
#include"../Seminar04/linked-list-utils.h"

using ListNode = LinkedListNode<int>;

ListNode* rearange(ListNode* head) {
    ListNode* oddStart = nullptr;
    ListNode* oddIter = nullptr;

    ListNode* evenStart = nullptr;
    ListNode* evenIter = nullptr;

    while(head != nullptr) {
        if(head->data % 2 == 1) {
            if(oddIter == nullptr) {
                oddStart = head;
                oddIter = head;
            }
            else {
                oddIter->next = head;
                oddIter = oddIter->next;
            }
        }
        else {
            if(evenIter == nullptr) {
                evenStart = head;
                evenIter = head;
            }
            else {
                evenIter->next = head;
                evenIter = evenIter->next;
            }
        }

        head = head->next;
    }

    if(evenStart == nullptr)
        return oddStart;

    evenIter->next = oddStart;
    
    if(oddIter != nullptr)
        oddIter->next = nullptr;
    
    return evenStart;
}

int main() {
    ListNode* ll = new ListNode(3, new ListNode(5, new ListNode(2, new ListNode(9, new ListNode(4)))));
    ListNode* res = rearange(ll);

    printLinkedList(res);
    freeList(res);
}