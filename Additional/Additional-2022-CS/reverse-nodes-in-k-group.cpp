#include<iostream>
#include"../Seminar04/linked-list-utils.h"

using ListNode = LinkedListNode<int>;

ListNode* getNext(ListNode* head, int k) {
    while(k && head) {
        head = head->next;
        --k;
    }

    return head;
}

ListNode* reverse(ListNode*& head) {
    ListNode* next = nullptr;
    ListNode* prev = nullptr;
    ListNode* it = head;
    ListNode* tmp = head;

    while(it) {
        next = it->next;
        it->next = prev;
        prev = it;
        it = next;
    }

    head = prev;
    return tmp;
}

ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* end = getNext(head, k - 1);

    if(end == nullptr)
        return head;

    ListNode* next = end->next;

    end->next = nullptr;
    
    ListNode* last = reverse(head);
    ListNode* res = reverseKGroup(next, k);

    last->next = res;
    return head;
}

int main() {
    ListNode* ll = fromList({1, 2, 3, 4, 5, 6, 7,8 ,9,10, 11, 12, 13, 14, 15, 16, 17});
    ll = reverseKGroup(ll, 4);
    printLinkedList(ll);
    freeList(ll);
}