SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {
    if(!llist)
        return nullptr;
        
    SinglyLinkedListNode* curr = llist;
    SinglyLinkedListNode* prev = nullptr;
    
    while(curr)
    {
        SinglyLinkedListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    return prev;
}
