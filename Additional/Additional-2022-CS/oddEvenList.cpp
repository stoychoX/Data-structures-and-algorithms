#include"../Seminar04/linked-list-utils.h"

using ListNode = LinkedListNode<int>;

ListNode* oddEvenList(ListNode* head) {
    if(head == nullptr || head->next == nullptr)
        return head;
    
    ListNode* oddStart = nullptr;
    ListNode* oddIter = nullptr;
    
    ListNode* evenStart = nullptr;
    ListNode* evenIter = nullptr;
    
    bool odd = true;
    
    while(head) {
        ListNode*& curr = odd ? oddIter : evenIter;
        
        if(curr == nullptr) {
            curr = head;
            if(odd) 
                oddStart = head; 
            else
                evenStart = head;
        }
        else {
            curr->next = head;
            curr = curr->next;
        }
        
        head = head->next;
        odd = !odd;
    }
    
    oddIter->next = evenStart;
    
    if(evenIter != nullptr)
        evenIter->next = nullptr;
    
    return oddStart;
}

int main() {
    ListNode* l = fromList({1, 2, 3, 4, 5});
    
    ListNode* result = oddEvenList(l);
    printLinkedList(result);
    freeList(result);

    ListNode* ls = fromList({2, 1, 3, 5, 6, 4, 7});
    result = oddEvenList(ls);
    printLinkedList(result);
    freeList(result);
}