#include<iostream>
#include"../Seminar04/linked-list-utils.h"

using ListNode = LinkedListNode<int>;

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if(list1 == nullptr)
        return list2;

    if(list2 == nullptr)
        return list1;

    ListNode* start = nullptr;
    ListNode* iter = nullptr;

    while(list1 != nullptr && list2 != nullptr) {
        ListNode*& toInsert = (list1->data > list2->data) ? list2 : list1;

        if(iter == nullptr) {
            start = toInsert;
            iter = toInsert;
        }
        else {
            iter->next = toInsert;
            iter = iter->next;
        }

        toInsert = toInsert->next;
    }

    ListNode* rest = (list1 == nullptr) ? list2 : list1;

    while(rest != nullptr) {
        iter->next = rest;
        iter = iter->next;
        rest = rest->next;
    }

    iter->next = nullptr;
    return start;
}

int main() {
    ListNode* l1 = new ListNode(1, new ListNode(2, new ListNode(4)));
    ListNode* l2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    
    ListNode* r = mergeTwoLists(l1, l2);
    
    printLinkedList(r);
    freeList(r);
}